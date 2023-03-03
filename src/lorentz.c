#include "lorentz.h"
#include "platform/platform.h"

int main(UNUSED int argc, UNUSED char *argv[])
{
    LrtzPlatformInitialize();

    Window window =
        LrtzPlatformWindowCreate("A Lorentz application", 1200, 720);

    DEBUG(TAG_WINDOW, "Window width: %u\n", window.width);
    DEBUG(TAG_WINDOW, "Window height: %u\n", window.height);

    while(true)
    {
        LrtzPlatformPollEvents();
    }

    return 0;
}
