#include <stdint.h>
#include <Windows.h>

namespace {

int call_checkWinVersion() {
    static const void * dst = (void*) 0x4C9DF4;
    int rval = 0;
    __asm CALL dst
    __asm MOV rval, EAX
    return rval;
}

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

} // namespace {}

int init_wndclass( HINSTANCE hinst ) {

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

int CALLBACK fo_WinMain(_In_ HINSTANCE hInstance,
                        _In_ HINSTANCE hPrevInstance,
                        _In_ LPSTR     lpCmdLine,
                        _In_ int       nCmdShow){

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
    if (call_checkWinVersion() == 0) {
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
