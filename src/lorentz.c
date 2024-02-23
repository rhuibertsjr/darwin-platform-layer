#include "lorentz.h"
#include "platform/platform.h"

int main(UNUSED int argc, UNUSED char* argv[])
{
    lrtz_log(INFO, TAG_LORENTZ, "Starting...");

    lrtz_platform_initialize();

    Window window =
        lrtz_platform_window_create("A Lorentz application", 1200, 768);

    lrtz_debug( "Window sizes: { width: %u, height: %u}", window.width,
        window.height);

    while(true)
    {
        lrtz_platform_poll_events();
    }

    return 0;
}
