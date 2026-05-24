#include "../../include/platform/PlatformWin32.hpp"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <hidusage.h>
#include <cstdlib>

struct PlatformWin32::Impl {
    HWND hwnd{nullptr};
    HDC hdc{nullptr};
    HDC memDC{nullptr};
    HBITMAP hBitmap{nullptr};
    void* bitmapBits{nullptr};
    int width{0};
    int height{0};
    HINSTANCE hInstance{nullptr};
    bool running{false};
    bool mouseCaptured{false};
    RAWINPUTDEVICE rid{};
};

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    auto* platform = reinterpret_cast<PlatformWin32*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    if (!platform && msg != WM_CREATE) {
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    InputState& input = platform ? platform->getInput() : *(InputState*)nullptr;

    switch (msg) {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        case WM_DESTROY:
            if (platform) platform->getInput();
            return 0;
        case WM_KEYDOWN:
            if (wParam < 256) {
                if (!input.keys[wParam]) {
                    input.keysPressed[wParam] = true;
                }
                input.keys[wParam] = true;
            }
            return 0;
        case WM_KEYUP:
            if (wParam < 256) {
                input.keys[wParam] = false;
                input.keysReleased[wParam] = true;
            }
            return 0;
        case WM_LBUTTONDOWN:
            input.mouseButtons[0] = true;
            input.mouseButtonsPressed[0] = true;
            SetCapture(hwnd);
            return 0;
        case WM_LBUTTONUP:
            input.mouseButtons[0] = false;
            input.mouseButtonsReleased[0] = true;
            ReleaseCapture();
            return 0;
        case WM_RBUTTONDOWN:
            input.mouseButtons[1] = true;
            input.mouseButtonsPressed[1] = true;
            return 0;
        case WM_RBUTTONUP:
            input.mouseButtons[1] = false;
            input.mouseButtonsReleased[1] = true;
            return 0;
        case WM_MBUTTONDOWN:
            input.mouseButtons[2] = true;
            input.mouseButtonsPressed[2] = true;
            return 0;
        case WM_MBUTTONUP:
            input.mouseButtons[2] = false;
            input.mouseButtonsReleased[2] = true;
            return 0;
        case WM_XBUTTONDOWN: {
            int btn = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4;
            input.mouseButtons[btn] = true;
            input.mouseButtonsPressed[btn] = true;
            return TRUE;
        }
        case WM_XBUTTONUP: {
            int btn = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4;
            input.mouseButtons[btn] = false;
            input.mouseButtonsReleased[btn] = true;
            return TRUE;
        }
        case WM_MOUSEWHEEL:
            input.mouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
            return 0;
        case WM_MOUSEMOVE: {
            int x = static_cast<int16_t>(LOWORD(lParam));
            int y = static_cast<int16_t>(HIWORD(lParam));
            input.mouseDX = x - input.mouseX;
            input.mouseDY = y - input.mouseY;
            input.mouseX = x;
            input.mouseY = y;
            return 0;
        }
        case WM_INPUT: {
            UINT dwSize = sizeof(RAWINPUT);
            static BYTE lpb[sizeof(RAWINPUT)];
            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
            RAWINPUT* raw = (RAWINPUT*)lpb;
            if (raw->header.dwType == RIM_TYPEMOUSE) {
                input.mouseDX += raw->data.mouse.lLastX;
                input.mouseDY += raw->data.mouse.lLastY;
            }
            return 0;
        }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

PlatformWin32::PlatformWin32() {
    timeBeginPeriod(1);
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    ticksPerMs = freq.QuadPart / 1000;
    LARGE_INTEGER tick;
    QueryPerformanceCounter(&tick);
    startTick = tick.QuadPart;
}

PlatformWin32::~PlatformWin32() {
    destroyWindow();
    timeEndPeriod(1);
}

bool PlatformWin32::createWindow(const char* title, int w, int h) {
    m = new Impl();
    m->width = w;
    m->height = h;
    m->hInstance = GetModuleHandleW(nullptr);

    WNDCLASSW wc{};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = m->hInstance;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = L"VOIDBREAKER_WINDOW";
    RegisterClassW(&wc);

    int titleLen = MultiByteToWideChar(CP_UTF8, 0, title, -1, nullptr, 0);
    wchar_t* wTitle = static_cast<wchar_t*>(_alloca(titleLen * sizeof(wchar_t)));
    MultiByteToWideChar(CP_UTF8, 0, title, -1, wTitle, titleLen);

    RECT rect = {0, 0, w, h};
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    m->hwnd = CreateWindowExW(0, L"VOIDBREAKER_WINDOW", wTitle,
                              WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT, CW_USEDEFAULT,
                              rect.right - rect.left,
                              rect.bottom - rect.top,
                              nullptr, nullptr, m->hInstance, nullptr);
    if (!m->hwnd) return false;

    SetWindowLongPtrW(m->hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    m->hdc = GetDC(m->hwnd);
    m->memDC = CreateCompatibleDC(m->hdc);

    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    m->hBitmap = CreateDIBSection(m->memDC, &bmi, DIB_RGB_COLORS, &m->bitmapBits, nullptr, 0);
    if (!m->hBitmap) return false;

    SelectObject(m->memDC, m->hBitmap);

    // Register raw input for mouse
    m->rid.usUsagePage = HID_USAGE_PAGE_GENERIC;
    m->rid.usUsage = HID_USAGE_GENERIC_MOUSE;
    m->rid.dwFlags = RIDEV_INPUTSINK;
    m->rid.hwndTarget = m->hwnd;
    RegisterRawInputDevices(&m->rid, 1, sizeof(RAWINPUTDEVICE));

    ShowWindow(m->hwnd, SW_SHOWDEFAULT);
    UpdateWindow(m->hwnd);
    m->running = true;
    return true;
}

void PlatformWin32::destroyWindow() {
    if (!m) return;
    if (m->hBitmap) {
        DeleteObject(m->hBitmap);
        m->hBitmap = nullptr;
    }
    if (m->memDC) {
        DeleteDC(m->memDC);
        m->memDC = nullptr;
    }
    if (m->hwnd) {
        if (m->hdc) ReleaseDC(m->hwnd, m->hdc);
        DestroyWindow(m->hwnd);
        m->hwnd = nullptr;
    }
    m->hdc = nullptr;
    m->running = false;
    delete m;
    m = nullptr;
}

bool PlatformWin32::pumpMessages() {
    if (!m || !m->running) return false;
    MSG msg;
    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
        if (msg.message == WM_QUIT) {
            m->running = false;
            return false;
        }
    }

    // Update held keys with GetAsyncKeyState
    for (int i = 0; i < 256; ++i) {
        SHORT state = GetAsyncKeyState(i);
        bool down = (state & 0x8000) != 0;
        if (down && !inputState.keys[i]) {
            inputState.keysPressed[i] = true;
        } else if (!down && inputState.keys[i]) {
            inputState.keysReleased[i] = true;
        }
        inputState.keys[i] = down;
    }
    return m->running;
}

void PlatformWin32::present(uint32_t* pixelBuffer, int w, int h) {
    if (!m || !m->running) return;
    memcpy(m->bitmapBits, pixelBuffer, static_cast<size_t>(w) * h * 4);
    BitBlt(m->hdc, 0, 0, w, h, m->memDC, 0, 0, SRCCOPY);
}

InputState PlatformWin32::getInput() {
    return inputState;
}

uint64_t PlatformWin32::getTicksMs() {
    LARGE_INTEGER tick;
    QueryPerformanceCounter(&tick);
    return (tick.QuadPart - startTick) / ticksPerMs;
}

void PlatformWin32::sleepMs(int ms) {
    Sleep(ms);
}
