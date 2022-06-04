#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "../_event_handler_.h"
#include "../_update_.h"

int main(void)
{

    int status = 0;

#define RUN_TEST(_t_) status += _t_();

    RUN_TEST(__test_event_handler);
    RUN_TEST(__test_update_position_velocity);
    RUN_TEST(__test_app_update);

#undef RUN_TEST

    return status;
}