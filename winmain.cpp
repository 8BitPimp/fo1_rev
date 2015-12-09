#include <stdint.h>
#include <Windows.h>
#include <stdlib.h>
#include "hook.h"

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

// Enable debug log
void call_4B2E50() {
    static const void * dst = (void*) 0x4B2E50;
    __asm CALL dst
}

__declspec(naked)
void debug_log(const char * fmt, ...) {
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

int init_wndclass(HINSTANCE hinst) {

    // Create window class structure
    WNDCLASSA wndClass;
    ZeroMemory(&wndClass, sizeof(wndClass));

    // Fill window class properties
    wndClass.hIcon          = LoadIconA(hinst, (const char *) 0x63);
    wndClass.lpszClassName  = "GNW95 Class";
    wndClass.lpfnWndProc    = (WNDPROC) 0x4C9F8C;
    wndClass.hInstance      = hinst;
    wndClass.style          = CS_HREDRAW | CS_VREDRAW;
    wndClass.hbrBackground  = (HBRUSH) GetStockObject(BLACK_BRUSH);

    // Register the window class
    int res = RegisterClassA(&wndClass);
    return res & 0xffff;
}

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
        call_4CD0F1(callback);

        // Success
        return 1;
    }
    while (false);

    // Free any loaded modules
    call_4C9F18();

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
        call_4B2E50();
        debug_log( "Fallout is hooked! %d %d %s", 1, 2, "Hi" );
    }
}

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
    if (call_4CE0B4(&local, lpCmdLine) == 0) {
        CloseHandle(*gMutex);
        return 1;
    }

    // Unknown?
    call_4CE420(1, 0x4C9F84, hInstance);
    call_4CE420(3, 0x4C9F84, hInstance);
    call_4CE420(5, 0x4C9F84, (void*) 1);

    // Unknown?
    *g53A290 = 1;

    // Main game jumpoff point
    call_4725E8(&local);

    // Cleanup
    call_4CE24C(&local);

    return 0;
}
