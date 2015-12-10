#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <Windows.h>
#include <stdlib.h>
#include "hook.h"
#include "watcall.h"

namespace {

int call_4CE0B4(uint64_t * val, char * cmd_args) {
    static const void * dst = (void*) 0x4CE0B4;
    int rval = 0;
    __asm MOV EAX, val
    __asm MOV EDX, cmd_args
    __asm CALL dst
    __asm MOV rval, EAX
    return rval;
}

void call_4CE420(int _eax, int _edx, void * _ebx) {
    static const void * dst = (void*) 0x4CE420;
    __asm MOV EAX, _eax
    __asm MOV EDX, _edx
    __asm MOV EBX, _ebx
    __asm CALL dst
}

void call_4725E8(uint64_t * arg) {
    static const void * dst = (void*) 0x4725E8;
    __asm MOV EAX, arg
    __asm MOV EDX, [EAX+4]
    __asm MOV EAX, [EAX]
    __asm CALL dst
}

void call_4CE24C(uint64_t * arg) {
    static const void * dst = (void*) 0x4CE24C;
    __asm MOV EAX, arg
    __asm CALL dst
}

void call_4C9F18() {
    static const void * dst = (void*) 0x4C9F18;
    __asm CALL dst;
}

void call_4CD0F1(void * cb) {
    static const void * dst = (void*) 0x4CD0F1;
    __asm MOV EAX, cb
    __asm CALL dst;
}

void call_init_debug_log() {
    static const void * dst = (void*) 0x4B2E50;
    __asm CALL dst
}

void call_4B43FC(int arg) {
    static const void * dst = (void*) 0x4B43FC;
    __asm MOV eax, arg
    __asm CALL dst
}

void call_4C3654(int arg) {
    static const void * dst = (void*) 0x4C3654;
    __asm MOV eax, arg
    __asm CALL dst
}

void call_4CF800(int arg) {
    static const void * dst = (void*) 0x4CF800;
    __asm CALL dst
}

// Create autorun mutex
int call_413450(uint64_t * arg) {
    static const void * dst = (void*) 0x413450;
    int ret_val = 0;
    __asm MOV eax, arg
    __asm CALL dst
    __asm MOV ret_val, eax
    return ret_val;
}

int call_4728CC(uint64_t * arg) {
    static const void * dst = (void*) 0x4728CC;
    int ret_val = 0;
    __asm MOV eax, arg
    __asm CALL dst
    __asm MOV ret_val, eax
    return ret_val;
}

int call_4460C0(int a, int b) { 
    static const void * dst = (void*) 0x4460C0;
    int ret_val = 0;
    __asm MOV eax, a
    __asm MOV edx, b
    __asm CALL dst
    __asm MOV ret_val, eax
    return ret_val;
}

int call_472F80() {
    static const void * dst = (void*) 0x472F80;
    int ret_val = 0;
    __asm CALL dst
    __asm MOV ret_val, eax
    return ret_val;
}

// Call fallouts debug log function
__declspec(naked)
void call_debug_log(const char * fmt, ...) {
    static const void * dst = (void*) 0x4B3008;
    __asm JMP dst
}

// Winmain Globals
const char  * gWN95Mutex    = (const char*)     0x4FE214;
HANDLE      * gMutex        = (HANDLE*)         0x53A294;
HINSTANCE   * gHInstance    = (HINSTANCE*)      0x53A284;
int         * gCmdShow      = (int*)            0x53A28C;
const char ** gCmdArgs      = (const char**)    0x53A288;
int *         g53A290       = (int*)            0x53A290;

// DirectX Modules
HMODULE     * gHModDDraw    = (HMODULE*)        0x53A298;
HMODULE     * gHModDInput   = (HMODULE*)        0x53A29C;
HMODULE     * gHModDSound   = (HMODULE*)        0x53A2A0;

// DirectX Instances
void       ** gHDDraw       = (void**)          0x53A274;
void       ** gHDInput      = (void**)          0x53A278;
void       ** gHDSound      = (void**)          0x53A27C;

// Window Instance
HWND        * gWindow       = (HWND*)           0x53A280;

} // namespace {}

// original @ 0x4725E8
int impl_4725E8(uint64_t * arg) {

    // Create autorun mutex
    if (watcall<0x413450, int>(arg) == 0) {
        return 1;
    }

    if (watcall<0x4728CC, int>(arg) != 1) {
        return 1;
    }

    watcall<0x4460C0, int>(1, 1);
    watcall<0x4460C0, int>(2, 0);

    // Load color.pal ?
    if (watcall<0x472F80, int>() == 0) {
        
    }

    return 0;
}

// original @ 0x4C9F8C
LRESULT __stdcall window_proc(HWND hwnd,
                              UINT uMsg,
                              WPARAM wParam,
                              LPARAM lParam) {

    /*
    // Fall through to original fallout winproc handler
    const WNDPROC old_proc = (WNDPROC) 0x4C9F8C;
    return old_proc(hwnd, uMsg, wParam, lParam);
    */

    switch (uMsg) {
    case (WM_ACTIVATEAPP): {
        int * dw_53A290 = (int*) 0x53A290;
        *dw_53A290 = wParam;

        // Window is being activated
        if (wParam == TRUE) {
            watcall<0x4B43FC, int>(1);
            int * dw_672170 = (int*) 0x672170;
            watcall<0x4C3654, int>(*dw_672170);
        }
        // Window is being deactivated
        else {
            watcall<0x4B43FC, int>(0);
        }
        return 0;
        }

    case (WM_PAINT): {
        RECT wndRect;
        if (GetUpdateRect(hwnd, &wndRect, 0) == TRUE) {
            int32_t size[] = {
                wndRect.left,
                wndRect.top,
                wndRect.right-1,
                wndRect.bottom-1
            };
            watcall<0x4C3654, int>((int) &size);
        }
        }
        break;

    case (WM_SETCURSOR):
        if (hwnd == *gWindow) {
            SetCursor(0);
            return 1;
        }
        break;

    case (WM_DESTROY):
        watcall<0x4CF800, int>(0);
        break;

    case (WM_SYSCOMMAND):
        if (wParam == SC_SCREENSAVE ||
            wParam == SC_MONITORPOWER) {
            return 0;
        }
    }

    // Pass message to default message handler
    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

// original @ 0x4C9DF4
int check_win_version() {

    // Get os info
    OSVERSIONINFOA info;
    ZeroMemory(&info, sizeof(info));
    if (GetVersionExA(&info) != TRUE) {
        return 1;
    }

    do {
        // 1 = Windows 95
        if (info.dwPlatformId < 1)
            break;

        // 4 = Major version
        if (info.dwMajorVersion < 4)
            break;

        // All is well
        return 1;
    }
    while (false);

    // Display error message
    const char * capt = (const char *) 0x4FE22C;
    const char * text = (const char *) 0x4FE244;
    MessageBoxA(nullptr, text, capt, 0x10);

    // Fail
    return 0;
}

// original @ 0x4C9D84
int init_wndclass(HINSTANCE hinst) {

    // Create window class structure
    WNDCLASSA wndClass;
    ZeroMemory(&wndClass, sizeof(wndClass));

    // Fill window class properties
    wndClass.hIcon          = LoadIconA(hinst, (const char *) 0x63);
    wndClass.lpszClassName  = "GNW95 Class";
    wndClass.lpfnWndProc    = window_proc;
    wndClass.hInstance      = hinst;
    wndClass.style          = CS_HREDRAW | CS_VREDRAW;
    wndClass.hbrBackground  = (HBRUSH) GetStockObject(BLACK_BRUSH);

    // Register the window class
    int res = RegisterClassA(&wndClass);
    return res & 0xffff;
}

// original @ 0x4B5738
int create_window() {

    // Early exit if the window already exists
    if (*gWindow != nullptr) {
        return 0;
    }

#if 1
    // Fullscreen (Original)
    const DWORD style1 = WS_EX_TOPMOST;
    const DWORD style2 = WS_SYSMENU | WS_VISIBLE | WS_POPUP;
    const DWORD width  = GetSystemMetrics(SM_CXSCREEN);
    const DWORD height = GetSystemMetrics(SM_CYSCREEN);
    const DWORD x      = 0;
    const DWORD y      = 0;
#else
    // Windowed mode (Forced to full screen later...)
    const DWORD style1 = WS_EX_CLIENTEDGE;
    const DWORD style2 = WS_SYSMENU | WS_OVERLAPPEDWINDOW | WS_VISIBLE;
    const DWORD width  = 640;
    const DWORD height = 480;
    const DWORD x      = CW_USEDEFAULT;
    const DWORD y      = CW_USEDEFAULT;
#endif

    // Get the window name
    const char * wnd_name = (const char *) 0x6B0760;

    // Create the main app window
    *gWindow = CreateWindowExA(style1,
                               "GNW95 Class",
                               wnd_name,
                               style2,
                               x,
                               y,
                               width,
                               height,
                               nullptr,
                               nullptr,
                               *gHInstance,
                               nullptr);

    if (*gWindow == nullptr) {
        // Fail
        return -1;
    }

    // Run winproc and bring into focus
    UpdateWindow(*gWindow);
    SetFocus(*gWindow);

    // Success
    return 0;
}

__declspec(naked)
int hook_create_window() {
    // callee save
    __asm PUSH EDX
    __asm PUSH ECX
    __asm PUSH EBX
    __asm PUSH ESI
    __asm PUSH EDI
    // Bounce into our create window
    __asm CALL create_window
    // restore callee save
    __asm POP EDI
    __asm POP ESI
    __asm POP EBX
    __asm POP ECX
    __asm POP EDX
    // return with EAX
    __asm RET
}

// original @ 0x4C9E60
int init_directx() {

    do {
        // Load direct draw library
        *gHModDDraw = LoadLibraryA("DDRAW.DLL");
        if (! *gHModDDraw)
            break;
        *gHDDraw = GetProcAddress(*gHModDDraw, "DirectDrawCreate");
        if (! *gHDDraw)
            break;

        // Load direct input library
        *gHModDInput = LoadLibraryA("DINPUT.DLL");
        if (! *gHModDInput)
            break;
        *gHDInput = GetProcAddress(*gHModDInput, "DirectInputCreateA");
        if (! *gHDInput)
            break;

        // Load direct sound library
        *gHModDSound = LoadLibraryA("DSOUND.DLL");
        if (! *gHModDSound)
            break;
        *gHDSound = GetProcAddress(*gHModDSound, "DirectSoundCreate");
        if (! *gHDSound)
            break;

        // Unknown?
        void * callback = (void*) 0x4C9F18;
        watcall<0x4CD0F1, int>(callback);

        // Success
        return 1;
    }
    while (false);

    // Free any loaded modules
    watcall<0x4C9F18, int>();

    // Show error message
    const char * capt = (const char *) 0x4FE2EC;
    const char * text = (const char *) 0x4FE304;
    MessageBoxA(0, capt, text, MB_ICONHAND);

    // Fail
    return 0;
}

void place_hooks() {

    // Hook the create window function
    hook((void*)0x4B5738, (void*)hook_create_window);

    // Enable the debug log (debug.log)
    // note: must export env var $DEBUGACTIVE="log"
    if (getenv("DEBUGACTIVE")) {
        call_init_debug_log();
        call_debug_log("Fallout is hooked!");
    }
}

// original @ 0x4C9C90
int CALLBACK fo_WinMain(_In_ HINSTANCE hInstance,
                        _In_ HINSTANCE hPrevInstance,
                        _In_ LPSTR     lpCmdLine,
                        _In_ int       nCmdShow){

    // Place additional hooks
    place_hooks();

    // Create global mutex
    *gMutex = CreateMutexA(nullptr, TRUE, gWN95Mutex);
    if (GetLastError == 0) {
        return 0;
    }

    // Hide mouse pointer
    ShowCursor(false);

    // Register window class
    if (init_wndclass(hInstance) == 0) {
        CloseHandle(*gMutex);
        return 0;
    }

    // Check for compatable windows version
    if (check_win_version() == 0) {
        CloseHandle(*gMutex);
        return 0;
    }

    // Load directx modules and exported create functions
    if (init_directx() != 1) {
        CloseHandle(*gMutex);
        return 0;
    }

    // Save global winmain params
    *gHInstance = hInstance;
    *gCmdArgs   = lpCmdLine;
    *gCmdShow   = nCmdShow;

    // Unknown?
    uint64_t local = 0;
    if (watcall<0x4CE0B4, int>(&local, lpCmdLine) == 0) {
        CloseHandle(*gMutex);
        return 1;
    }

    // Unknown?
    watcall<0x4CE420, int>(1, 0x4C9F84, hInstance);
    watcall<0x4CE420, int>(3, 0x4C9F84, hInstance);
    watcall<0x4CE420, int>(5, 0x4C9F84, (void*) 1);

    // Unknown?
    *g53A290 = 1;

    // Main game jumpoff point
    watcall<0x4725E8, int>(&local);

    // Cleanup
    watcall<0x4CE24C, int>(&local);

    return 0;
}
