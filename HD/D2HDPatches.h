#include "../DLLmain.h"

namespace HD {
    void __stdcall D2GFX_GetModeParams(int mode, DWORD* width, DWORD* height);

    void ResizeWindow_Interception();
    void ResizeRenderResolution_Interception();
    void ResizeForgroundRenderWidth_Interception();
    void ResizeGameLogicResolution_Interception();
    void SetResolutionModeId_Interception();
    void SetResolutionModeOnGameStart001_Interception();
    void SetResolutionModeOnGameStart002_Interception();
    void SetRegistryResolutionModeId_Interception();
    void SaveRegistryResolution_Interception(int mode);
    void LoadRegistryResolution_Interception(int* mode);

    void Replace640_ResizeD2DWindow_Interception();
    void Replace640_ResizeD2D_Interception1();

    void SetupGlideRenderResolution_Interception();
    void __stdcall SetupGlideWindowSize();

    void __stdcall RepositionPanels();

    int __stdcall GetResolutionMode_Patch();
}
