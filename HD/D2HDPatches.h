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
