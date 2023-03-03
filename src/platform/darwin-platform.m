#import "platform/darwin-platform.h"
#import "lorentz.h"

/* =============================================================================
 * Lorentz application 
 ============================================================================ */
@interface LrtzApplicationDelegate : NSObject<NSApplicationDelegate> {}
@end

@implementation LrtzApplicationDelegate

- (void) applicationDidFinishLaunching:(NSNotification*) notification
{
    Log(INFO, TAG_PLATFORM, "Initializing platform completed");
    [NSApp stop:nil];
}

@end

/* =============================================================================
 * Lorentz window
 ============================================================================ */
@interface LrtzWindow : NSWindow {}
@end

@implementation LrtzWindow

- (BOOL) canBecomeKeyWindow
{
    return YES;
}

- (BOOL)canBecomeMainWindow
{
    return YES;
}

@end

/* =============================================================================
 * Lorentz window delegate
 ============================================================================ */
@interface LrtzWindowDelegate : NSObject<NSWindowDelegate>
{
    Window* window;
}

- (instancetype) initialize_window:(Window*) init_window;

@end

@implementation LrtzWindowDelegate

- (instancetype) initialize_window:(Window*) init_window 
{
    self = [super init];
    if (self != nil)
        window = init_window;
    return self;
}

- (void) windowWillClose:(NSNotification*) notification
{
    [NSApp terminate:nil];
}

@end

/* =============================================================================
 * 
 ============================================================================ */
void
LrtzPlatformInitialize(void)
{
    Log(INFO, TAG_PLATFORM, "Initializing platform");

    NSApplication* application =
        [NSApplication sharedApplication];

    LrtzApplicationDelegate* application_delegate =
        [[LrtzApplicationDelegate alloc] init]; 

    [application setDelegate:application_delegate];
    [application setActivationPolicy:NSApplicationActivationPolicyRegular];
    [application activateIgnoringOtherApps:YES];
}

Window
LrtzPlatformWindowCreate(String title, U32 width, U32 height)
{
    Log(INFO, TAG_WINDOW, " - Creating window");

    Window window;
    window.width  = width;
    window.height = height;

    window.delegate =
        [[LrtzWindowDelegate alloc] initialize_window:&window];

    NSRect window_surface = NSMakeRect(0, 0, window.width, window.height); 

    NSWindowStyleMask window_style = NSWindowStyleMaskTitled;
    window_style |=
        (NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable);

    window.object =
        [[LrtzWindow alloc] initWithContentRect:window_surface
                                      styleMask:window_style
                                        backing:NSBackingStoreBuffered
                                          defer:NO];

    [window.object setTitle:@(title)];
    [window.object setDelegate:window.delegate];
    [window.object setContentView:window.view];

    // Note(rhuibjr) Prevent multiple properties with the same name. 
    [(NSWindow*) window.object center];
    [window.object setLevel:NSNormalWindowLevel];
    [window.object makeKeyAndOrderFront:nil];

    // NOTE(rhuibjr) [application run] should only be run once. 
    if (![[NSRunningApplication currentApplication] isFinishedLaunching])
        [NSApp run];

    return window;
}

void
LrtzPlatformPollEvents(void)
{
    while(true)
    {
        NSEvent* event =
            [NSApp nextEventMatchingMask:NSEventMaskAny
                               untilDate:[NSDate distantPast]
                                  inMode:NSDefaultRunLoopMode
                                 dequeue:YES];

        // Do nothing when there are no events.
        if (event == nil)
            return;

        [NSApp sendEvent:event];
    }
}

void
LrtzPlatformWindowClose(void)
{
    Log(INFO, TAG_WINDOW, "Platform closing window.");
    [NSApp terminate:nil];
}
