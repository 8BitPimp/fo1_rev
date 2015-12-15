#define DIRECTSOUND_VERSION 0x300
#include <dsound.h>

struct IDirectSound_imp_t
    : public IDirectSound {

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
    CreateSoundBuffer(__in LPCDSBUFFERDESC pcDSBufferDesc,
                      __deref_out LPDIRECTSOUNDBUFFER *ppDSBuffer,
                      __null LPUNKNOWN pUnkOuter) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetCaps(__out LPDSCAPS pDSCaps) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    DuplicateSoundBuffer(__in LPDIRECTSOUNDBUFFER pDSBufferOriginal,
                         __deref_out LPDIRECTSOUNDBUFFER *ppDSBufferDuplicate) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetCooperativeLevel(HWND hwnd,
                        DWORD dwLevel) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Compact() {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetSpeakerConfig(__out LPDWORD pdwSpeakerConfig) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetSpeakerConfig(DWORD dwSpeakerConfig) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Initialize(__in_opt LPCGUID pcGuidDevice) {
        __debugbreak();
        return 0;
    }
};

// DirectSound implementation factory
extern HRESULT __stdcall CreateDirectSound_Imp(
    GUID            *lpGUID,
    LPDIRECTSOUND   *lplpDS,
    IUnknown        *pUnkOuter) {

    // Create custom DirectSound implementation
    *lplpDS = new IDirectSound_imp_t;
    return S_OK;
}