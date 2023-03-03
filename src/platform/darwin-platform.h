#ifndef LRTZ_PLATFORM_DARWIN_H
#define LRTZ_PLATFORM_DARWIN_H

#include "lorentz.h"

#ifdef __OBJC__
#    import <Cocoa/Cocoa.h>
#else

typedef void* id;

#endif

/* =============================================================================
 * Types and compounds 
 ============================================================================ */
typedef struct Window {
    id  delegate; 
    id  object; 
    id  view;
    
    U32 width, height;
    B32 should_close;
    B32 resizeable;
} Window;

#endif
