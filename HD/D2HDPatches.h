/*
To define your own custom replacement for 640x480, simply
change the values of the definition below.

I highly do NOT recommend changing the 800x600 values. The
values you place are overriden in the D2GDI code and messes
everything up.
*/

#define RESOLUTION_640_TO_HD_WIDTH 1068
#define RESOLUTION_640_TO_HD_HEIGHT 600

#define RESOLUTION_800_TO_HD_WIDTH 800
#define RESOLUTION_800_TO_HD_HEIGHT 600

#define RESOLUTION_1344_TO_HD_WIDTH 800
#define RESOLUTION_1344_TO_HD_HEIGHT 600

namespace HD {
    extern int firstStart;

    void Replace640_ResizeWindow_Interception();
    void Replace640_ResizeRenderResolution_Interception();
    void Replace640_ResizeForgroundRenderWidth_Interception();
    int Replace640_ResizeGameLogicResolution_Interception();
    void Replace640_ResizeD2DWindow_Interception();
    void Replace640_ResizeD2D_Interception1();
    void Replace640_ResizeGlideRenderResolution_Interception();
    void Replace640_ResizeGlideWindow_Interception();
    int SetupGlideRenderResolution_Interception();

    void PanelPosition_Interception();

    int __fastcall GetResolutionMode_Interception();
}


