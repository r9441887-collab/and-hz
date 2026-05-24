#include "../../include/platform/PlatformMac.hpp"
#import <Cocoa/Cocoa.h>
#import <mach/mach_time.h>
#include <cstring>

// Forward declare the view class
@interface VoidbreakerView : NSView
@property (nonatomic, assign) PlatformMac* platform;
@end

struct PlatformMac::Impl {
    NSWindow* window{nullptr};
    VoidbreakerView* view{nullptr};
    uint32_t* pixelBuffer{nullptr};
    int width{0};
    int height{0};
    bool running{false};
    NSInteger windowNumber{0};
};

// Global pointer for input state from events
static InputState* gInputState = nullptr;

@implementation VoidbreakerView

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void)keyDown:(NSEvent*)event {
    if (!gInputState) return;
    unsigned short keyCode = [event keyCode];
    int vk = keyCode; // Use raw keyCode as virtual key
    if (vk < 256) {
        if (!gInputState->keys[vk]) gInputState->keysPressed[vk] = true;
        gInputState->keys[vk] = true;
    }
}

- (void)keyUp:(NSEvent*)event {
    if (!gInputState) return;
    unsigned short keyCode = [event keyCode];
    int vk = keyCode;
    if (vk < 256) {
        gInputState->keys[vk] = false;
        gInputState->keysReleased[vk] = true;
    }
}

- (void)flagsChanged:(NSEvent*)event {
    if (!gInputState) return;
    NSEventModifierFlags flags = [event modifierFlags];
    static const int keyMap[] = {56, 60, 55, 57, 58, 59};
    static const NSEventModifierFlags flagMap[] = {
        NSEventModifierFlagShift, NSEventModifierFlagOption,
        NSEventModifierFlagCommand, NSEventModifierFlagControl,
        NSEventModifierFlagCapsLock, NSEventModifierFlagFunction
    };
    for (int i = 0; i < 6; ++i) {
        bool down = (flags & flagMap[i]) != 0;
        int vk = keyMap[i];
        if (down && !gInputState->keys[vk]) gInputState->keysPressed[vk] = true;
        else if (!down && gInputState->keys[vk]) gInputState->keysReleased[vk] = true;
        gInputState->keys[vk] = down;
    }
}

- (void)mouseDown:(NSEvent*)event {
    if (!gInputState) return;
    gInputState->mouseButtons[0] = true;
    gInputState->mouseButtonsPressed[0] = true;
}

- (void)mouseUp:(NSEvent*)event {
    if (!gInputState) return;
    gInputState->mouseButtons[0] = false;
    gInputState->mouseButtonsReleased[0] = true;
}

- (void)rightMouseDown:(NSEvent*)event {
    if (!gInputState) return;
    gInputState->mouseButtons[1] = true;
    gInputState->mouseButtonsPressed[1] = true;
}

- (void)rightMouseUp:(NSEvent*)event {
    if (!gInputState) return;
    gInputState->mouseButtons[1] = false;
    gInputState->mouseButtonsReleased[1] = true;
}

- (void)otherMouseDown:(NSEvent*)event {
    if (!gInputState) return;
    int btn = (int)[event buttonNumber];
    if (btn >= 0 && btn < 5) {
        gInputState->mouseButtons[btn] = true;
        gInputState->mouseButtonsPressed[btn] = true;
    }
}

- (void)otherMouseUp:(NSEvent*)event {
    if (!gInputState) return;
    int btn = (int)[event buttonNumber];
    if (btn >= 0 && btn < 5) {
        gInputState->mouseButtons[btn] = false;
        gInputState->mouseButtonsReleased[btn] = true;
    }
}

- (void)mouseMoved:(NSEvent*)event {
    if (!gInputState) return;
    NSPoint loc = [event locationInWindow];
    gInputState->mouseDX = (int)loc.x - gInputState->mouseX;
    gInputState->mouseDY = (int)(self.bounds.size.height - loc.y) - gInputState->mouseY;
    gInputState->mouseX = (int)loc.x;
    gInputState->mouseY = (int)(self.bounds.size.height - loc.y);
}

- (void)mouseDragged:(NSEvent*)event {
    [self mouseMoved:event];
}

- (void)rightMouseDragged:(NSEvent*)event {
    [self mouseMoved:event];
}

- (void)scrollWheel:(NSEvent*)event {
    if (!gInputState) return;
    gInputState->mouseWheel += (int)[event deltaY];
}

@end

PlatformMac::PlatformMac() {}

PlatformMac::~PlatformMac() {
    destroyWindow();
}

bool PlatformMac::createWindow(const char* title, int w, int h) {
    m = new Impl();
    m->width = w;
    m->height = h;

    @autoreleasepool {
        [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

        NSRect rect = NSMakeRect(0, 0, w, h);
        m->window = [[NSWindow alloc] initWithContentRect:rect
                                               styleMask:NSWindowStyleMaskTitled |
                                                         NSWindowStyleMaskClosable |
                                                         NSWindowStyleMaskMiniaturizable |
                                                         NSWindowStyleMaskResizable
                                                 backing:NSBackingStoreBuffered
                                                   defer:NO];
        if (!m->window) return false;

        [m->window setTitle:[NSString stringWithUTF8String:title]];
        [m->window center];

        m->view = [[VoidbreakerView alloc] initWithFrame:rect];
        m->view.platform = this;
        [m->window setContentView:m->view];
        [m->window makeFirstResponder:m->view];

        // Enable mouse tracking
        [m->window setAcceptsMouseMovedEvents:YES];
        [m->window makeKeyAndOrderFront:nil];
        [NSApp activateIgnoringOtherApps:YES];

        m->windowNumber = [m->window windowNumber];
        gInputState = &inputState;

        m->pixelBuffer = new uint32_t[static_cast<size_t>(w) * h]();
        m->running = true;
    }
    return true;
}

void PlatformMac::destroyWindow() {
    if (!m) return;

    @autoreleasepool {
        if (gInputState == &inputState) gInputState = nullptr;
        if (m->view) {
            [m->view release];
            m->view = nullptr;
        }
        if (m->window) {
            [m->window close];
            [m->window release];
            m->window = nullptr;
        }
        delete[] m->pixelBuffer;
        m->pixelBuffer = nullptr;
    }
    m->running = false;
    delete m;
    m = nullptr;
}

bool PlatformMac::pumpMessages() {
    if (!m || !m->running) return false;

    inputState.mouseDX = 0;
    inputState.mouseDY = 0;
    inputState.mouseWheel = 0;

    @autoreleasepool {
        NSEvent* event;
        while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                        untilDate:[NSDate distantPast]
                                        inMode:NSDefaultRunLoopMode
                                        dequeue:YES]) != nil) {
            [NSApp sendEvent:event];
        }
    }
    return m->running;
}

void PlatformMac::present(uint32_t* pixelBuffer, int w, int h) {
    if (!m || !m->running || !m->view) return;

    @autoreleasepool {
        memcpy(m->pixelBuffer, pixelBuffer, static_cast<size_t>(w) * h * 4);

        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        CGContextRef ctx = CGBitmapContextCreate(m->pixelBuffer, w, h, 8, w * 4,
                                                 colorSpace,
                                                 kCGImageAlphaPremultipliedFirst |
                                                 kCGBitmapByteOrder32Little);
        if (ctx) {
            CGImageRef cgImage = CGBitmapContextCreateImage(ctx);
            if (cgImage) {
                NSGraphicsContext* nsCtx = [NSGraphicsContext currentContext];
                [NSGraphicsContext setCurrentContext:[NSGraphicsContext graphicsContextWithWindow:m->window]];

                [[m->view layer] setContents:(id)cgImage];
                [m->view setNeedsDisplay:YES];

                // Render via CGContext
                CGContextRef viewCtx = [[NSGraphicsContext currentContext] CGContext];
                if (viewCtx) {
                    CGRect rect = CGRectMake(0, 0, w, h);
                    CGContextDrawImage(viewCtx, rect, cgImage);
                }

                [NSGraphicsContext setCurrentContext:nsCtx];
                CGImageRelease(cgImage);
            }
            CGContextRelease(ctx);
        }
        CGColorSpaceRelease(colorSpace);
        [m->window flushWindow];
    }
}

InputState PlatformMac::getInput() {
    return inputState;
}

uint64_t PlatformMac::getTicksMs() {
    static mach_timebase_info_data_t timebase = {};
    static bool once = false;
    if (!once) {
        mach_timebase_info(&timebase);
        once = true;
    }
    uint64_t now = mach_absolute_time();
    uint64_t nanos = now * timebase.numer / timebase.denom;
    return nanos / 1000000ULL;
}

void PlatformMac::sleepMs(int ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000LL;
    nanosleep(&ts, nullptr);
}
