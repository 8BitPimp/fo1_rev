#include <Windows.h>
#include "hook.h"

int CALLBACK fo_WinMain(_In_ HINSTANCE hInstance,
                        _In_ HINSTANCE hPrevInstance,
                        _In_ LPSTR     lpCmdLine,
                        _In_ int       nCmdShow);

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL,
                    _In_ DWORD     fdwReason,
                    _In_ LPVOID    lpvReserved) {

    // Redirect the old winmain
    hook((void*)0x4C9C90, fo_WinMain);
    return TRUE;
}

// Dummy export, which is added to fallouts import table
extern "C" __declspec(dllexport) void dummy() {}
