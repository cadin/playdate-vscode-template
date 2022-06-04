#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "_mocks_.h"

#include "../_app_const_.h"
#include "../_event_handler_.h"
#include "../_update_.h"
#include "../_state_.h"

#define PD_API (&__mock_PlaydateAPI)

typedef struct
{
    LCDFont *font_to_load;
} __Test_State_;

int _setup_event_handler_tests_(void **state)
{
    __Test_State_ *_state_ = (__Test_State_ *)state;
    static LCDFont _font_to_load;
    _state_->font_to_load = &_font_to_load;
    return 0;
}

void _event_handler_test_init(void **state)
{
    __Test_State_ _state_ = *((__Test_State_ *)state);

    expect_function_call(__mock_graphics_loadFont);
    expect_string(__mock_graphics_loadFont, path, FONT);
    will_return(__mock_graphics_loadFont, _state_.font_to_load);

    expect_function_call(__mock_system_setUpdateCallback);
    expect_value(__mock_system_setUpdateCallback, update, &_app_update_);

    _event_handler_(PD_API, kEventInit, 0);
}

void _event_handler_test_init_font_error(void **state)
{
    expect_function_call(__mock_graphics_loadFont);
    expect_string(__mock_graphics_loadFont, path, FONT);
    will_return(__mock_graphics_loadFont, NULL);

    expect_function_call(__mock_system_error);

    expect_function_call(__mock_system_setUpdateCallback);
    expect_value(__mock_system_setUpdateCallback, update, &_app_update_);

    _event_handler_(PD_API, kEventInit, 0);
}

int _setup_update_test_(void **state)
{
    __Test_State_ *_state_ = (__Test_State_ *)state;
    static LCDFont _font_to_load;
    _state_->font_to_load = &_font_to_load;
    font = _state_->font_to_load;
    return 0;
}

void _app_update_test_normal(void **state)
{
    __Test_State_ _state_ = *((__Test_State_ *)state);

    expect_function_call(__mock_graphics_clear);
    expect_value(__mock_graphics_clear, color, kColorWhite);

    expect_function_call(__mock_graphics_setFont);
    expect_value(__mock_graphics_setFont, font, _state_.font_to_load);

    expect_function_call(__mock_graphics_drawText);
    expect_string(__mock_graphics_drawText, text, "Hello World!");
    expect_value(__mock_graphics_drawText, len, strlen("Hello World!"));
    expect_value(__mock_graphics_drawText, encoding, kASCIIEncoding);
    expect_value(__mock_graphics_drawText, x, x);
    expect_value(__mock_graphics_drawText, y, y);
    will_return(__mock_graphics_drawText, 0);

    expect_function_call(_update_position_velocity_);

    expect_function_call(__mock_system_drawFPS);
    expect_value(__mock_system_drawFPS, x, 0);
    expect_value(__mock_system_drawFPS, y, 0);

    _app_update_(PD_API);
}

void _update_position_velocity_test_normal(void **state)
{
    x = X0;
    y = Y0;
    __real_update_position_velocity_();
    assert_int_equal(x, X0 + DX);
    assert_int_equal(y, Y0 + DY);
    assert_int_equal(dx, DX);
    assert_int_equal(dy, DY);
}

void _update_position_velocity_test_right_edge(void **state)
{
    x = LCD_COLUMNS - TEXT_WIDTH;
    dx = DX;
    y = LCD_ROWS / 2;
    dy = 0;
    __real_update_position_velocity_();
    assert_int_equal(x, LCD_COLUMNS - TEXT_WIDTH + DX);
    assert_int_equal(y, LCD_ROWS / 2);
    assert_int_equal(dx, -DX);
    assert_int_equal(dy, 0);
}

void _update_position_velocity_test_left_edge(void **state)
{
    x = 0;
    dx = -DX;
    y = LCD_ROWS / 2;
    dy = 0;
    __real_update_position_velocity_();
    assert_int_equal(x, -DX);
    assert_int_equal(y, LCD_ROWS / 2);
    assert_int_equal(dx, DX);
    assert_int_equal(dy, 0);
}

void _update_position_velocity_test_bottom_edge(void **state)
{
    x = LCD_COLUMNS / 2;
    dx = 0;
    y = LCD_ROWS - TEXT_HEIGHT;
    dy = DY;
    __real_update_position_velocity_();
    assert_int_equal(x, LCD_COLUMNS / 2);
    assert_int_equal(y, LCD_ROWS - TEXT_HEIGHT + DY);
    assert_int_equal(dx, 0);
    assert_int_equal(dy, -DY);
}

void _update_position_velocity_test_top_edge(void **state)
{
    x = LCD_COLUMNS / 2;
    dx = 0;
    y = 0;
    dy = -DY;
    __real_update_position_velocity_();
    assert_int_equal(x, LCD_COLUMNS / 2);
    assert_int_equal(y, -DY);
    assert_int_equal(dx, 0);
    assert_int_equal(dy, DY);
}

int main(void)
{

    int status = 0;

    const struct CMUnitTest _event_handler_tests[] = {
        cmocka_unit_test(_event_handler_test_init),
        cmocka_unit_test(_event_handler_test_init_font_error),
    };
    status += cmocka_run_group_tests_name("_event_handler_", _event_handler_tests, _setup_event_handler_tests_, NULL);

    const struct CMUnitTest _app_update_tests[] = {
        cmocka_unit_test_setup(_app_update_test_normal, _setup_update_test_),
    };
    status += cmocka_run_group_tests_name("_app_update_", _app_update_tests, NULL, NULL);

    const struct CMUnitTest _update_position_velocity_tests[] = {
        cmocka_unit_test(_update_position_velocity_test_normal),
        cmocka_unit_test(_update_position_velocity_test_right_edge),
        cmocka_unit_test(_update_position_velocity_test_left_edge),
        cmocka_unit_test(_update_position_velocity_test_bottom_edge),
        cmocka_unit_test(_update_position_velocity_test_top_edge),
    };
    status += cmocka_run_group_tests_name("_update_position_velocity_", _update_position_velocity_tests, NULL, NULL);

    return status;
}