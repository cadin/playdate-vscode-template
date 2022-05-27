#include "pd_api.h"

#include "_app_const_.h"
#include "_state_.h"

int _app_update_(void *userdata)
{
    PlaydateAPI *pd = userdata;

    pd->graphics->clear(kColorWhite);
    pd->graphics->setFont(font);
    pd->graphics->drawText("Hello World!", strlen("Hello World!"), kASCIIEncoding, x, y);

    x += dx;
    y += dy;

    if (x < 0 || x > LCD_COLUMNS - TEXT_WIDTH)
        dx = -dx;

    if (y < 0 || y > LCD_ROWS - TEXT_HEIGHT)
        dy = -dy;

    pd->system->drawFPS(0, 0);

    return 1;
}