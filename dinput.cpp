#define DIRECTINPUT_VERSION 0x300
#include <dinput.h>

enum DeviceType_t {
    KEYBOARD,
    MOUSE
};

struct IDirectInputDevice_imp_t
    : public IDirectInputDeviceA {

    DeviceType_t type_;

    IDirectInputDevice_imp_t(DeviceType_t type)
        : type_(type)
    {
    }

    virtual HRESULT __stdcall
    QueryInterface(REFIID riid,
                   void ** ppvObject) {
        __debugbreak();
        return 0;
    };

    virtual ULONG __stdcall
    AddRef(void) {
        __debugbreak();
        return 0;
    };

    virtual ULONG __stdcall
    Release(void) {
        __debugbreak();
        return 0;
    };

    virtual HRESULT __stdcall
    GetCapabilities(LPDIDEVCAPS) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA,
                LPVOID,
                DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetProperty(REFGUID,
                LPDIPROPHEADER) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetProperty(REFGUID,
                LPCDIPROPHEADER) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Acquire() {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Unacquire() {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetDeviceState(DWORD,
                   LPVOID) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetDeviceData(DWORD,
                  LPDIDEVICEOBJECTDATA,
                  LPDWORD,
                  DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetDataFormat(LPCDIDATAFORMAT) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetEventNotification(HANDLE) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetCooperativeLevel(HWND,DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA,
                  DWORD,
                  DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetDeviceInfo(LPDIDEVICEINSTANCEA) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    RunControlPanel(HWND,
                    DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Initialize(HINSTANCE,
               DWORD,
               REFGUID) {
        __debugbreak();
        return 0;
    }
};

struct IDirectInput_imp_t
    : public IDirectInputA {

    virtual HRESULT __stdcall
    QueryInterface(REFIID riid,
                   void ** ppvObject) {
        __debugbreak();
        return 0;
    };

    virtual ULONG __stdcall
    AddRef(void) {
        __debugbreak();
        return 0;
    };

    virtual ULONG __stdcall
    Release(void) {
        __debugbreak();
        return 0;
    };

    virtual HRESULT __stdcall
    CreateDevice(REFGUID guid,
                 LPDIRECTINPUTDEVICEA * device,
                 LPUNKNOWN) {

        // System mouse
        GUID mouse = {
            0x6F1D2B60,
            0xD5A0,
            0x11CF,
            0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00
        };

        // System keyboard
        GUID keyboard = {
            0x6F1D2B61,
            0xD5A0,
            0x11CF,
            0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00
        };

        if (guid == mouse) {
            *device = new IDirectInputDevice_imp_t(MOUSE);
            return DI_OK;
        }

        if (guid == keyboard) {
            *device = new IDirectInputDevice_imp_t;
            return DI_OK;
        }

        return DIERR_GENERIC;
    }

    virtual HRESULT __stdcall
    EnumDevices(DWORD,
                LPDIENUMDEVICESCALLBACKA,
                LPVOID,
                DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetDeviceStatus(REFGUID) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    RunControlPanel(HWND,
                    DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Initialize(HINSTANCE,
               DWORD) {
        __debugbreak();
        return 0;
    }
};

// DirectDraw implementation factory
extern HRESULT __stdcall CreateDirectInput_Imp(
    HINSTANCE hinst,
    DWORD dwVersion,
    LPDIRECTINPUTA *ppDI,
    LPUNKNOWN punkOuter) {

    // Create custom DirectInput implementation
    *ppDI = new IDirectInput_imp_t;
    return S_OK;
}
