#include "D2HDPatches.h"
#include "../DLLmain.h"
#include "../D2Ptrs.h"

void HD::PanelPosition_Interception() {
	*D2CLIENT_PanelOffsetX = (*D2CLIENT_ScreenSizeX / 2) - 320;
	*D2CLIENT_PanelOffsetX = ((int)*D2CLIENT_ScreenSizeY - 480) / -2;
}

void HD::RedrawUILeftPanelBorders_Interception() {
	__asm {
		mov dword ptr ds : [ebp + 0x30], eax
	}

	int basePositionX = (*D2CLIENT_ScreenSizeX / 2) - 400;
	int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;
	int frameNumber = 10;

	// Draw background pieces
	const DWORD backWidth = 256;
	const DWORD backHeight = 256;

	for (int row = 0; (row * backHeight) < *D2CLIENT_ScreenSizeY; row++) {
		DWORD backBasePositionY = ((row + 1) * backHeight);

		for (int col = 0; (int)((basePositionX + 80) - (col * backWidth)) >= 0; col++) {
			frameNumber = 10 + ((row % 2) * 2) + (col % 2);
			DWORD backBasePositionX = (basePositionX + 80) - ((col + 1) * backWidth);

			D2GFX_DrawUIPanelBorder(&frameNumber, backBasePositionX, backBasePositionY, 0xFFFFFFFF, 5, 0);
		}
	}

	frameNumber = 0;

	// Frame 0
	D2GFX_DrawUIPanelBorder(&frameNumber, basePositionX, basePositionY + 253, 0xFFFFFFFF, 5, 0);
	frameNumber++;

	// Frame 1
	D2GFX_DrawUIPanelBorder(&frameNumber, basePositionX + 256, basePositionY + 63, 0xFFFFFFFF, 5, 0);
	frameNumber++;

	// Frame 2
	D2GFX_DrawUIPanelBorder(&frameNumber, basePositionX, basePositionY + 484, 0xFFFFFFFF, 5, 0);
	frameNumber++;

	// Frame 3
	D2GFX_DrawUIPanelBorder(&frameNumber, basePositionX, basePositionY + 553, 0xFFFFFFFF, 5, 0);
	frameNumber++;

	// Frame 4
	D2GFX_DrawUIPanelBorder(&frameNumber, basePositionX + 256, basePositionY + 553, 0xFFFFFFFF, 5, 0);
	frameNumber++;
}

void HD::RedrawUIRightPanelBorders_Interception() {
	__asm {
		mov dword ptr ds : [ebp + 0x30], edx
	}

	int basePositionX = (*D2CLIENT_ScreenSizeX / 2);
	int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;
	int frameNumber = 10;


	// Draw background pieces
	const DWORD backWidth = 256;
	const DWORD backHeight = 256;

	for (int row = 0; (row * backHeight) < *D2CLIENT_ScreenSizeY; row++) {
		DWORD backBasePositionY = ((row + 1) * backHeight);
		for (int col = 0; (basePositionX + 320) + (col * backWidth) < *D2CLIENT_ScreenSizeX; col++) {
			frameNumber = 10 + ((row % 2) * 2) + (col % 2);
			DWORD backBasePositionX = (basePositionX + 320) + (col * backWidth);

			D2GFX_DrawUIPanelBorder(&frameNumber, backBasePositionX, backBasePositionY, 0xFFFFFFFF, 5, 0);
		}
	}

	frameNumber = 5;

	// Frame 5
	D2GFX_DrawUIPanelBorder(&frameNumber, basePositionX, basePositionY + 63, 0xFFFFFFFF, 5, 0);
	frameNumber++;

	// Frame 6
	D2GFX_DrawUIPanelBorder(&frameNumber, basePositionX + 144, basePositionY + 253, 0xFFFFFFFF, 5, 0);
	frameNumber++;

	// Frame 7
	D2GFX_DrawUIPanelBorder(&frameNumber, basePositionX + 313, basePositionY + 484, 0xFFFFFFFF, 5, 0);
	frameNumber++;

	// Frame 8
	D2GFX_DrawUIPanelBorder(&frameNumber, basePositionX + 144, basePositionY + 553, 0xFFFFFFFF, 5, 0);
	frameNumber++;

	// Frame 9
	D2GFX_DrawUIPanelBorder(&frameNumber, basePositionX, basePositionY + 553, 0xFFFFFFFF, 5, 0);
	frameNumber++;
}

// This enables the expansion panel borders when you open
// panels (char menu, skill menu...)
int __fastcall HD::EnableUIPanelBorders_Interception() {
	return (*D2CLIENT_ScreenSizeX >= 800) ? 2 : 0;
}
