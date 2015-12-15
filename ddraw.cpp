#include <stdint.h>
#define DIRECTDRAW_VERSION  0x300
#include <ddraw.h>
#include <intrin.h>

struct IDirectDrawSurface_imp_t
    : public IDirectDrawSurface {

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
    AddAttachedSurface(IDirectDrawSurface *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    AddOverlayDirtyRect(LPRECT) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Blt(LPRECT, IDirectDrawSurface*, LPRECT, DWORD, LPDDBLTFX) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    BltBatch(LPDDBLTBATCH, DWORD, DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    BltFast(DWORD, DWORD, IDirectDrawSurface*, LPRECT, DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    DeleteAttachedSurface(DWORD, IDirectDrawSurface*) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    EnumAttachedSurfaces(LPVOID, LPDDENUMSURFACESCALLBACK) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    EnumOverlayZOrders(DWORD, LPVOID, LPDDENUMSURFACESCALLBACK) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Flip(IDirectDrawSurface *, DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetAttachedSurface(LPDDSCAPS, IDirectDrawSurface **) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetBltStatus(DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetCaps(LPDDSCAPS) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetClipper(IDirectDrawClipper **) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetColorKey(DWORD, LPDDCOLORKEY) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetDC(HDC *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetFlipStatus(DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetOverlayPosition(LPLONG, LPLONG) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetPalette(IDirectDrawPalette **) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetPixelFormat(LPDDPIXELFORMAT) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetSurfaceDesc(LPDDSURFACEDESC) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Initialize(IDirectDraw *, LPDDSURFACEDESC) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    IsLost() {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Lock(LPRECT, LPDDSURFACEDESC, DWORD, HANDLE) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    ReleaseDC(HDC) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Restore() {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetClipper(IDirectDrawClipper *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetColorKey(DWORD, LPDDCOLORKEY) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetOverlayPosition(LONG, LONG) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetPalette(LPDIRECTDRAWPALETTE) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Unlock(LPVOID) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    UpdateOverlay(LPRECT, IDirectDrawSurface *, LPRECT, DWORD, LPDDOVERLAYFX) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    UpdateOverlayDisplay(DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    UpdateOverlayZOrder(DWORD, IDirectDrawSurface *) {
        __debugbreak();
        return 0;
    }
};

struct IDirectDrawClipper_imp_t
    : public IDirectDrawClipper {

    virtual HRESULT __stdcall
    GetClipList(LPRECT, LPRGNDATA, DWORD *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetHWnd(HWND *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Initialize(IDirectDraw *, DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    IsClipListChanged(int *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetClipList(LPRGNDATA, DWORD) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetHWnd(DWORD, HWND) {
        __debugbreak();
        return 0;
    }
};

struct IDirectDrawPalette_imp_t
    : public IDirectDrawPalette {

    virtual HRESULT __stdcall
    GetCaps(DWORD *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetEntries(DWORD, DWORD, DWORD, PALETTEENTRY *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Initialize(IDirectDraw *, DWORD, PALETTEENTRY *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetEntries(DWORD, DWORD, DWORD, PALETTEENTRY *) {
        __debugbreak();
        return 0;
    }
};

struct IDirectDraw_imp_t
    : public IDirectDraw {

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
    Compact() {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    CreateClipper(DWORD,
                  LPDIRECTDRAWCLIPPER *,
                  IUnknown *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    CreatePalette(DWORD dwFlags,
                  LPPALETTEENTRY        lpDDColorArray,
                  LPDIRECTDRAWPALETTE * lplpDDPalette,
                  IUnknown *            pUnkOuter) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    CreateSurface(LPDDSURFACEDESC       desc,
                  LPDIRECTDRAWSURFACE * surf,
                  IUnknown            * pUnkOuter) {
        __debugbreak();
        *surf = new IDirectDrawSurface_imp_t;
        return 0;
    }

    virtual HRESULT __stdcall
    DuplicateSurface(LPDIRECTDRAWSURFACE,
                     LPDIRECTDRAWSURFACE *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    EnumDisplayModes(DWORD,
                     LPDDSURFACEDESC,
                     LPVOID,
                     LPDDENUMMODESCALLBACK) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    EnumSurfaces(DWORD,
                 LPDDSURFACEDESC,
                 LPVOID,
                 LPDDENUMSURFACESCALLBACK) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    FlipToGDISurface() {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetCaps(LPDDCAPS,
            LPDDCAPS) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetDisplayMode(LPDDSURFACEDESC) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetFourCCCodes(DWORD *, DWORD *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetGDISurface(LPDIRECTDRAWSURFACE *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetMonitorFrequency(DWORD *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetScanLine(DWORD *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    GetVerticalBlankStatus(LPBOOL) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    Initialize(GUID *) {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    RestoreDisplayMode() {
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetCooperativeLevel(HWND window,
                        DWORD level) {
        // 1
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    SetDisplayMode(DWORD width,
                   DWORD height,
                   DWORD bpp) {
        // 2
        __debugbreak();
        return 0;
    }

    virtual HRESULT __stdcall
    WaitForVerticalBlank(DWORD,
                         HANDLE) {
        __debugbreak();
        return 0;
    }
};

// DirectDraw implementation factory
extern HRESULT __stdcall CreateDirectDraw_Imp(
    GUID            *lpGUID,
    LPDIRECTDRAW    *lplpDD,
    IUnknown        *pUnkOuter) {

    // Create custom DirectDraw implementation
    *lplpDD = new IDirectDraw_imp_t;
    return S_OK;
}
