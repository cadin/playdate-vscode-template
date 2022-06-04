#include "pd_api.h"

#include "_app_const_.h"
#include "_state_.h"
#include "_update_.h"

#ifndef TEST
void _update_position_velocity_(void)
#else
void __real_update_position_velocity_(void)
#endif
{
    // _update_position_
    x += dx;
    y += dy;
    // _update_velocity_
    if (x < 0 || x > LCD_COLUMNS - TEXT_WIDTH)
        dx = -dx;

    if (y < 0 || y > LCD_ROWS - TEXT_HEIGHT)
        dy = -dy;
}

int _app_update_(void *userdata)
{
    PlaydateAPI *pd = userdata;

    pd->graphics->clear(kColorWhite);
    pd->graphics->setFont(font);
    pd->graphics->drawText("Hello World!", strlen("Hello World!"), kASCIIEncoding, x, y);

    _update_position_velocity_();

    pd->system->drawFPS(0, 0);

    return 1;
}