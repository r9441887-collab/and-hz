#include "../../include/platform/PlatformX11.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>
#include <chrono>
#include <cstring>

struct PlatformX11::Impl {
    Display* display{nullptr};
    Window window{0};
    GC gc{nullptr};
    XImage* image{nullptr};
    Atom wmDeleteMessage{0};
    int width{0};
    int height{0};
    bool running{false};
};

// Keysym to scancode mapping helper
static int keysymToVK(KeySym ks) {
    switch (ks) {
        case XK_a: case XK_A: return 'A';
        case XK_b: case XK_B: return 'B';
        case XK_c: case XK_C: return 'C';
        case XK_d: case XK_D: return 'D';
        case XK_e: case XK_E: return 'E';
        case XK_f: case XK_F: return 'F';
        case XK_g: case XK_G: return 'G';
        case XK_h: case XK_H: return 'H';
        case XK_i: case XK_I: return 'I';
        case XK_j: case XK_J: return 'J';
        case XK_k: case XK_K: return 'K';
        case XK_l: case XK_L: return 'L';
        case XK_m: case XK_M: return 'M';
        case XK_n: case XK_N: return 'N';
        case XK_o: case XK_O: return 'O';
        case XK_p: case XK_P: return 'P';
        case XK_q: case XK_Q: return 'Q';
        case XK_r: case XK_R: return 'R';
        case XK_s: case XK_S: return 'S';
        case XK_t: case XK_T: return 'T';
        case XK_u: case XK_U: return 'U';
        case XK_v: case XK_V: return 'V';
        case XK_w: case XK_W: return 'W';
        case XK_x: case XK_X: return 'X';
        case XK_y: case XK_Y: return 'Y';
        case XK_z: case XK_Z: return 'Z';
        case XK_0: return '0'; case XK_1: return '1';
        case XK_2: return '2'; case XK_3: return '3';
        case XK_4: return '4'; case XK_5: return '5';
        case XK_6: return '6'; case XK_7: return '7';
        case XK_8: return '8'; case XK_9: return '9';
        case XK_Escape:      return VK_ESCAPE;
        case XK_Tab:         return VK_TAB;
        case XK_Return:      return VK_RETURN;
        case XK_BackSpace:   return VK_BACK;
        case XK_Delete:      return VK_DELETE;
        case XK_Home:        return VK_HOME;
        case XK_End:         return VK_END;
        case XK_Page_Up:    return VK_PRIOR;
        case XK_Page_Down:  return VK_NEXT;
        case XK_Insert:      return VK_INSERT;
        case XK_Left:        return VK_LEFT;
        case XK_Right:       return VK_RIGHT;
        case XK_Up:          return VK_UP;
        case XK_Down:        return VK_DOWN;
        case XK_Shift_L: case XK_Shift_R: return VK_SHIFT;
        case XK_Control_L: case XK_Control_R: return VK_CONTROL;
        case XK_Alt_L: case XK_Alt_R: return VK_MENU;
        case XK_Super_L: case XK_Super_R: return VK_LWIN;
        case XK_Space:       return VK_SPACE;
        case XK_F1:  return VK_F1;  case XK_F2:  return VK_F2;
        case XK_F3:  return VK_F3;  case XK_F4:  return VK_F4;
        case XK_F5:  return VK_F5;  case XK_F6:  return VK_F6;
        case XK_F7:  return VK_F7;  case XK_F8:  return VK_F8;
        case XK_F9:  return VK_F9;  case XK_F10: return VK_F10;
        case XK_F11: return VK_F11; case XK_F12: return VK_F12;
        default: return 0;
    }
}

PlatformX11::PlatformX11() {}

PlatformX11::~PlatformX11() {
    destroyWindow();
}

bool PlatformX11::createWindow(const char* title, int w, int h) {
    m = new Impl();
    m->width = w;
    m->height = h;

    m->display = XOpenDisplay(nullptr);
    if (!m->display) return false;

    int screen = DefaultScreen(m->display);
    Window root = RootWindow(m->display, screen);

    XSetWindowAttributes swa{};
    swa.event_mask = KeyPressMask | KeyReleaseMask | ButtonPressMask |
                     ButtonReleaseMask | PointerMotionMask | ExposureMask |
                     StructureNotifyMask;

    m->window = XCreateWindow(m->display, root, 0, 0, w, h, 0,
                              DefaultDepth(m->display, screen),
                              InputOutput, DefaultVisual(m->display, screen),
                              CWEventMask, &swa);

    XStoreName(m->display, m->window, title);

    m->wmDeleteMessage = XInternAtom(m->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(m->display, m->window, &m->wmDeleteMessage, 1);

    // Disable key repeat for reliable key events
    XkbSetDetectableAutoRepeat(m->display, True, nullptr);

    m->gc = XCreateGC(m->display, m->window, 0, nullptr);

    m->image = XCreateImage(m->display, DefaultVisual(m->display, screen),
                            DefaultDepth(m->display, screen),
                            ZPixmap, 0, nullptr, w, h, 32, 0);
    if (!m->image) return false;
    m->image->data = new char[static_cast<size_t>(w) * h * 4]{};

    XMapWindow(m->display, m->window);
    XFlush(m->display);
    m->running = true;
    return true;
}

void PlatformX11::destroyWindow() {
    if (!m) return;
    if (m->image) {
        delete[] m->image->data;
        m->image->data = nullptr;
        XDestroyImage(m->image);
        m->image = nullptr;
    }
    if (m->gc && m->display) XFreeGC(m->display, m->gc);
    if (m->window && m->display) XDestroyWindow(m->display, m->window);
    if (m->display) XCloseDisplay(m->display);
    m->display = nullptr;
    m->running = false;
    delete m;
    m = nullptr;
}

bool PlatformX11::pumpMessages() {
    if (!m || !m->running) return false;
    inputState.mouseDX = 0;
    inputState.mouseDY = 0;
    inputState.mouseWheel = 0;

    while (XPending(m->display) > 0) {
        XEvent ev;
        XNextEvent(m->display, &ev);

        switch (ev.type) {
            case ClientMessage:
                if (static_cast<Atom>(ev.xclient.data.l[0]) == m->wmDeleteMessage) {
                    m->running = false;
                    return false;
                }
                break;
            case DestroyNotify:
                m->running = false;
                return false;
            case KeyPress: {
                KeySym ks = XLookupKeysym(&ev.xkey, 0);
                int vk = keysymToVK(ks);
                if (vk > 0 && vk < 256) {
                    if (!inputState.keys[vk]) inputState.keysPressed[vk] = true;
                    inputState.keys[vk] = true;
                }
                break;
            }
            case KeyRelease: {
                // Check if it's an automatic repeat
                if (XEventsQueued(m->display, QueuedAfterReading)) {
                    XEvent nev;
                    XPeekEvent(m->display, &nev);
                    if (nev.type == KeyPress && nev.xkey.time == ev.xkey.time &&
                        nev.xkey.keycode == ev.xkey.keycode) {
                        XNextEvent(m->display, &nev);
                        break;
                    }
                }
                KeySym ks = XLookupKeysym(&ev.xkey, 0);
                int vk = keysymToVK(ks);
                if (vk > 0 && vk < 256) {
                    inputState.keys[vk] = false;
                    inputState.keysReleased[vk] = true;
                }
                break;
            }
            case ButtonPress: {
                int btn = ev.xbutton.button - 1;
                if (btn >= 0 && btn < 5) {
                    inputState.mouseButtons[btn] = true;
                    inputState.mouseButtonsPressed[btn] = true;
                }
                if (ev.xbutton.button == 4) inputState.mouseWheel += 1;
                if (ev.xbutton.button == 5) inputState.mouseWheel -= 1;
                break;
            }
            case ButtonRelease: {
                int btn = ev.xbutton.button - 1;
                if (btn >= 0 && btn < 5) {
                    inputState.mouseButtons[btn] = false;
                    inputState.mouseButtonsReleased[btn] = true;
                }
                break;
            }
            case MotionNotify:
                inputState.mouseDX = ev.xmotion.x - inputState.mouseX;
                inputState.mouseDY = ev.xmotion.y - inputState.mouseY;
                inputState.mouseX = ev.xmotion.x;
                inputState.mouseY = ev.xmotion.y;
                break;
            case Expose:
                break;
        }
    }
    return m->running;
}

void PlatformX11::present(uint32_t* pixelBuffer, int w, int h) {
    if (!m || !m->image) return;
    memcpy(m->image->data, pixelBuffer, static_cast<size_t>(w) * h * 4);
    XPutImage(m->display, m->window, m->gc, m->image, 0, 0, 0, 0, w, h);
    XFlush(m->display);
}

InputState PlatformX11::getInput() {
    return inputState;
}

uint64_t PlatformX11::getTicksMs() {
    static auto start = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
}

void PlatformX11::sleepMs(int ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000LL;
    nanosleep(&ts, nullptr);
}
