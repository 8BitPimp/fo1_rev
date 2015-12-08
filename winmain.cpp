#include <stdint.h>
#include <Windows.h>

namespace {

int call_registerWndClass( HINSTANCE arg ) {
    static const void * dst = (void*) 0x004C9D84;
    int rval = 0;
    __asm MOV EAX, arg
    __asm CALL dst
    __asm MOV rval, EAX
    return rval;
}

int call_checkWinVersion() {
    static const void * dst = (void*) 0x004C9DF4;
    int rval = 0;
    __asm CALL dst
    __asm MOV rval, EAX
    return rval;
}

int call_initDirectX() {
    static const void * dst = (void*) 0x004C9E60;
    int rval = 0;
    __asm CALL dst
    __asm MOV rval, EAX
    return rval;
}

int call_4CE0B4(uint64_t * val, char * cmd_args) {
    static const void * dst = (void*) 0x004CE0B4;
    int rval = 0;
    __asm MOV EAX, val
    __asm MOV EDX, cmd_args
    __asm CALL dst
    __asm MOV rval, EAX
    return rval;
}

void call_4CE420( int _eax, int _edx, void * _ebx ) {
    static const void * dst = (void*) 0x004CE420;
    __asm MOV EAX, _eax
    __asm MOV EDX, _edx
    __asm MOV EBX, _ebx
    __asm CALL dst
}

void call_4725E8( uint64_t arg ) {
    static const void * dst = (void*) 0x004725E8;
    __asm LEA EAX, arg
    __asm MOV EDX, [EAX+4]
    __asm MOV EAX, [EAX]
    __asm CALL dst
}

void call_4CE24C( uint64_t arg ) {
    static const void * dst = (void*) 0x004CE24C;
    __asm LEA EAX, arg
    __asm MOV EAX, [EAX]
    __asm CALL dst
}

void create_wnd_class() {
}

// hook the window class creation function
__declspec(naked)
void trampoline_4C9D84() {
    __asm CALL create_wnd_class
}

const char  * gWN95Mutex = (const char *)   0x004FE214;
HANDLE      * gMutex     = (HANDLE*)        0x0053A294;
HINSTANCE   * gHInstance = (HINSTANCE*)     0x0053A284;
int         * gCmdShow   = (int*)           0x0053A28C;
const char ** gCmdArgs   = (const char **)  0x0053A288;
int *         g53A290    = (int*)           0x0053A290;
} // namespace {}

// eax = hinstance
// edx = 0
// ebx = 0x22
// edx = 0
extern "C"
int CALLBACK fo_WinMain(_In_ HINSTANCE hInstance,
                        _In_ HINSTANCE hPrevInstance,
                        _In_ LPSTR     lpCmdLine,
                        _In_ int       nCmdShow){

    *gMutex = CreateMutexA(0, 1, gWN95Mutex);
    if (GetLastError == 0 ) {
        return 0;
    }

    ShowCursor(false);

    if (call_registerWndClass(hInstance) == 0) {
        CloseHandle(*gMutex);
        return 0;
    }

    if (call_checkWinVersion() == 0) {
        CloseHandle(*gMutex);
        return 0;
    }

    if (call_initDirectX() != 1) {
        CloseHandle(*gMutex);
        return 0;
    }

    *gHInstance  = hInstance;
    *gCmdArgs    = lpCmdLine;
    *gCmdShow    = nCmdShow;

    // eax=&local, edx=0xF0761 ebx=hInstance
    uint64_t local = 0;
    if (call_4CE0B4(&local, lpCmdLine) == 0) {
        CloseHandle(*gMutex);
        return 0;
    }

    // eax=1 edx=0x4c9f84 ebx=hInstance ecx=0x627F0000
    call_4CE420(1, 0x4C9F84, hInstance);
    call_4CE420(3, 0x4C9F84, hInstance);
    call_4CE420(5, 0x4C9F84, (void*) 1);

    *g53A290 = 1;

    call_4725E8(local);

    call_4CE24C(local);

    return 1;
}
