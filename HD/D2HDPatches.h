#define RESOLUTION_HD_WIDTH 1066
#define RESOLUTION_HD_HEIGHT 600

namespace HD {
	void Replace640_ResizeWindow_Interception();
	void Replace640_ResizeRenderResolution_Interception();
	void Replace640_ResizeForgroundRenderWidth_Interception();
	int Replace640_ResizeGameLogicResolution_Interception();
	void Replace640_ResizeGlideRenderResolution_Interception();
	void Replace640_ResizeGlideWindow_Interception();
	
	void PanelPosition_Interception();
	void RedrawUILeftPanelBorders_Interception();
	void RedrawUIRightPanelBorders_Interception();
	int __fastcall EnableUIPanelBorders_Interception();
}


