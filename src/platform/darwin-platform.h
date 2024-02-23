#ifndef LRTZ_PLATFORM_DARWIN_H
#define LRTZ_PLATFORM_DARWIN_H

#include "lorentz.h"

typedef struct Window Window;

#ifdef __OBJC__

#undef internal
#    import <Cocoa/Cocoa.h>
#define internal static
/* =============================================================================
 * Interfaces 
 ============================================================================ */
@interface LrtzApplicationDelegate : NSObject<NSApplicationDelegate>
{
    
}
@end

// NOTE(rhuibjr) Container 
@interface LrtzWindow : NSWindow
{
    
}
@end

// NOTE(rhuibjr) Handles events
@interface LrtzWindowDelegate : NSObject<NSWindowDelegate> 
{
    Window* window;
}
@end

// NOTE(rhuibjr) Handles drawing 
@interface LrtzWindowView : NSView
{
}

- (instancetype) initialize_window:(Window*) init_window;

@end
#else

// NOTE(rhuibjr) Makes file compilable for non-objc compilers.
typedef void* id;

#endif // __OBJC__

/* =============================================================================
 * Types and compounds 
 ============================================================================ */
struct Window {
    id delegate; 
    id object; 
    id view;
    
    u32 width, height;
    b32 should_close;
    b32 resizeable;
};

#endif // LRTZ_PLATFORM_DARWIN_H
