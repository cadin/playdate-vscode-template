#include "pd_api.h"

// mocked API
PlaydateAPI __mock_PlaydateAPI;

// Additional types spec
// no complete defintion is provided by the API, strangely
// Hence, this is not the real data structure but a mock
// in itself
struct LCDFont
{
};

// exposed mock functions
LCDFont *__mock_graphics_loadFont(const char *path, const char **outErr);
void __mock_system_error(const char *fmt, ...);
void __mock_system_setUpdateCallback(PDCallbackFunction *update, void *userdata);
void __mock_graphics_clear(LCDColor color);
void __mock_graphics_setFont(LCDFont *font);
int __mock_graphics_drawText(const void *text, size_t len, PDStringEncoding encoding, int x, int y);
void __mock_system_drawFPS(int x, int y);