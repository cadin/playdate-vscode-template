//
// main.c
//

#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"

#include "lib/_event_handler_.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif
	int eventHandler(PlaydateAPI *pd, PDSystemEvent event, uint32_t arg)
{
	return _event_handler_(pd, event, arg);
}
