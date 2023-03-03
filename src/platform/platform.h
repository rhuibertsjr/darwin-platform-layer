#ifndef LRTZ_PLATFORM_H
#define LRTZ_PLATFORM_H

#include "lorentz.h"

typedef struct Window Window;

void
LrtzPlatformInitialize(void);

Window
LrtzPlatformPollEvents(void);

Window
LrtzPlatformWindowCreate(String title, U32 width, U32 height);

void
LrtzPlatformWindowClose(void);

#ifdef LRTZ_PLATFORM_DARWIN
#    include "platform/darwin-platform.h"
#endif

#endif
