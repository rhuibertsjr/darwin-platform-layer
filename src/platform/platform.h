#ifndef LRTZ_PLATFORM_H
#define LRTZ_PLATFORM_H

#include "lorentz.h"

typedef struct Window Window;

void
lrtz_platform_initialize(void);

Window
lrtz_platform_poll_events(void);

Window
lrtz_platform_window_create(string title, u32 width, u32 height);

void
lrtz_platform_window_close(void);

#ifdef LRTZ_PLATFORM_DARWIN
#    include "platform/darwin-platform.h"
#else
#    error "Platform has not been detected."
#endif

#endif
