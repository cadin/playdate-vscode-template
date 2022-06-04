#include "_mocks_.h"
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>
#include <setjmp.h>
#include <cmocka.h>
#include <assert.h>

LCDFont *__mock_graphics_loadFont(const char *path, const char **outErr)
{
    function_called();
    check_expected(path);
    LCDFont *font = (LCDFont *)mock();
    return font;
}

void __mock_graphics_setFont(LCDFont *font)
{
    function_called();
    check_expected(font);
}

void __mock_graphics_clear(LCDColor color)
{
    function_called();
    check_expected(color);
}

int __mock_graphics_drawText(const void *text, size_t len, PDStringEncoding encoding, int x, int y)
{
    function_called();
    check_expected(text);
    check_expected(len);
    check_expected(encoding);
    check_expected(x);
    check_expected(y);
    int rv = (int)mock();
    return rv;
}

void __mock_system_drawFPS(int x, int y)
{
    function_called();
    check_expected(x);
    check_expected(y);
}

void __mock_system_setUpdateCallback(PDCallbackFunction *update, void *userdata)
{
    function_called();
    check_expected_ptr(update);
}

void __mock_system_error(const char *fmt, ...)
{
    function_called();
}

struct playdate_sys __mock_playdate_system = {
    .error = (void (*)(const char *, ...)) & __mock_system_error,
    .setUpdateCallback = &__mock_system_setUpdateCallback,
    .drawFPS = &__mock_system_drawFPS};

struct playdate_graphics __mock_playdate_graphics = {
    .loadFont = &__mock_graphics_loadFont,
    .setFont = &__mock_graphics_setFont,
    .clear = &__mock_graphics_clear,
    .drawText = &__mock_graphics_drawText,
};

PlaydateAPI __mock_PlaydateAPI = {
    .system = &__mock_playdate_system,
    .graphics = &__mock_playdate_graphics,
};

void _update_position_velocity_(void)
{
    function_called();
}