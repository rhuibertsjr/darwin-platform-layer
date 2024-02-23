#import "platform/darwin-platform.h"
#import "lorentz.h"

@implementation LrtzApplicationDelegate

- (void) applicationDidFinishLaunching:(NSNotification*) notification
{
    lrtz_log(INFO, TAG_PLATFORM, "Initializing platform completed");
    [NSApp stop:nil];
}

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
lrtz_platform_initialize(void)
{
    lrtz_log(INFO, TAG_PLATFORM, "Initializing platform");

    NSApplication* application =
        [NSApplication sharedApplication];

    LrtzApplicationDelegate* application_delegate =
        [[LrtzApplicationDelegate alloc] init]; 

    [application setDelegate:application_delegate];
    [application setActivationPolicy:NSApplicationActivationPolicyRegular];
    [application activateIgnoringOtherApps:YES];
}

Window
lrtz_platform_window_create(string title, u32 width, u32 height)
{
    lrtz_assert(width > 0);
    lrtz_assert(height > 0);

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

    //NSView *contentView = [[NSView alloc] initWithFrame:frame];
 
 
    //[window setContentView:contentView];

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

    lrtz_log(INFO, TAG_WINDOW, " - Created window");
    return window;
}

void
lrtz_platform_poll_events(void)
{
    while(true)
    {
        NSEvent* event =
            [NSApp nextEventMatchingMask:NSEventMaskAny
                               untilDate:[NSDate distantPast]
                                  inMode:NSDefaultRunLoopMode
                                 dequeue:YES];

        // NOTE(rhuibjr) Do nothing when there are no events.
        if (event == nil)
            return;

        [NSApp sendEvent:event];
    }
}

void
lrtz_platform_window_close(void)
{
    lrtz_log(INFO, TAG_WINDOW, "Platform closing window.");
    [NSApp terminate:nil];
}
