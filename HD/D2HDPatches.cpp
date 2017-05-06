#include "D2HDPatches.h"
#include "../DLLmain.h"
#include "../D2Ptrs.h"

void HD::Replace640_ResizeWindow_Interception() {
    __asm {
        mov dword ptr ds : [eax], RESOLUTION_640_TO_HD_WIDTH; Requires registers due to the
            mov dword ptr ds : [ecx], RESOLUTION_640_TO_HD_HEIGHT; use of ESP to access memory
    }
}

void __declspec(naked) HD::Replace640_ResizeRenderResolution_Interception() {
    __asm {
        mov esi, (RESOLUTION_640_TO_HD_WIDTH - (RESOLUTION_640_TO_HD_WIDTH % 4))
            mov edx, RESOLUTION_640_TO_HD_HEIGHT
            ret
    }
}

void HD::Replace640_ResizeForgroundRenderWidth_Interception() {
    *D2GDI_ForegroundRenderWidth = RESOLUTION_640_TO_HD_WIDTH;
}

int HD::Replace640_ResizeGameLogicResolution_Interception() {
    *D2CLIENT_ScreenSizeX = RESOLUTION_640_TO_HD_WIDTH;
    *D2CLIENT_ScreenSizeY = RESOLUTION_640_TO_HD_HEIGHT;
    return *D2CLIENT_ScreenSizeX;
}

void __declspec(naked) HD::Replace640_ResizeD2DWindow_Interception() {
    __asm {
        mov ecx, D2DDRAW_GameWindowSizeY
            mov dword ptr ds : [ecx], RESOLUTION_640_TO_HD_HEIGHT;
        mov ecx, RESOLUTION_640_TO_HD_WIDTH;
        ret
    }
}

void __declspec(naked) HD::Replace640_ResizeD2D_Interception1() {
    __asm {
        mov edi, RESOLUTION_640_TO_HD_WIDTH
            mov esi, RESOLUTION_640_TO_HD_HEIGHT
            ret
    }
}

void HD::Replace640_ResizeGlideRenderResolution_Interception() {
    *D2GLIDE_ScreenSizeX = RESOLUTION_640_TO_HD_WIDTH;
    *D2GLIDE_ScreenSizeY = RESOLUTION_640_TO_HD_HEIGHT;
}

void HD::Replace640_ResizeGlideWindow_Interception() {
    DWORD* pWidth = *GLIDE3X_GameWindowSizeX;
    DWORD* pHeight = *GLIDE3X_GameWindowSizeY;
    __asm {
        mov edx, pWidth
            mov dword ptr ds : [edx], RESOLUTION_640_TO_HD_WIDTH
            mov ecx, pHeight
            mov dword ptr ds : [ecx], RESOLUTION_640_TO_HD_HEIGHT
    }
}

int HD::firstStart = 2;

int HD::SetupGlideRenderResolution_Interception() {
    int newResolutionMode, glideVideoMode;
    __asm mov newResolutionMode, esi
    __asm mov edx, 0

    switch (newResolutionMode) {
    case 0:
        if (*STORM_IsCinematic || firstStart) {
            firstStart--;
            glideVideoMode = 7;
            *D2GLIDE_ScreenSizeX = 640;
            *D2GLIDE_ScreenSizeY = 480;
        }
        else {
            glideVideoMode =  0xFF;
            *D2GLIDE_ScreenSizeX = RESOLUTION_640_TO_HD_WIDTH;
            *D2GLIDE_ScreenSizeY = RESOLUTION_640_TO_HD_HEIGHT;
        }
        
        break;

    case 1:
    case 2:
        glideVideoMode = 8;
        *D2GLIDE_ScreenSizeX = RESOLUTION_800_TO_HD_WIDTH;
        *D2GLIDE_ScreenSizeY = RESOLUTION_800_TO_HD_HEIGHT;
        break;
    }
    __asm mov ecx, glideVideoMode
    __asm mov esi, newResolutionMode
    return newResolutionMode;
}

// Repositions panels in the correct location, independent of resolution.
void HD::PanelPosition_Interception() {
    *D2CLIENT_PanelOffsetX = (*D2CLIENT_ScreenSizeX / 2) - 320;
    *D2CLIENT_PanelOffsetY = ((int)*D2CLIENT_ScreenSizeY - 480) / -2;
}

// Redraws the left side panel borders in the correct places, independent of resolution.
// In addition, also draws a background to cover up extra space.
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

            D2GFX_D2DrawImage(&frameNumber, backBasePositionX, backBasePositionY, 0xFFFFFFFF, 5, 0);
        }
    }

    frameNumber = 0;

    // Frame 0
    D2GFX_D2DrawImage(&frameNumber, basePositionX, basePositionY + 253, 0xFFFFFFFF, 5, 0);
    frameNumber++;

    // Frame 1
    D2GFX_D2DrawImage(&frameNumber, basePositionX + 256, basePositionY + 63, 0xFFFFFFFF, 5, 0);
    frameNumber++;

    // Frame 2
    D2GFX_D2DrawImage(&frameNumber, basePositionX, basePositionY + 484, 0xFFFFFFFF, 5, 0);
    frameNumber++;

    // Frame 3
    D2GFX_D2DrawImage(&frameNumber, basePositionX, basePositionY + 553, 0xFFFFFFFF, 5, 0);
    frameNumber++;

    // Frame 4
    D2GFX_D2DrawImage(&frameNumber, basePositionX + 256, basePositionY + 553, 0xFFFFFFFF, 5, 0);
    frameNumber++;
}

// Redraws the right side panel borders in the correct places, independent of resolution.
// In addition, also draws a background to cover up extra space.
void HD::RedrawUIRightPanelBorders_Interception() {
    __asm {
        xor eax, eax
            mov ecx, 18
            lea edi, [ebp + 0x0C]
            repe stosd
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

            D2GFX_D2DrawImage(&frameNumber, backBasePositionX, backBasePositionY, 0xFFFFFFFF, 5, 0);
        }
    }

    frameNumber = 5;

    // Frame 5
    D2GFX_D2DrawImage(&frameNumber, basePositionX, basePositionY + 63, 0xFFFFFFFF, 5, 0);
    frameNumber++;

    // Frame 6
    D2GFX_D2DrawImage(&frameNumber, basePositionX + 144, basePositionY + 253, 0xFFFFFFFF, 5, 0);
    frameNumber++;

    // Frame 7
    D2GFX_D2DrawImage(&frameNumber, basePositionX + 313, basePositionY + 484, 0xFFFFFFFF, 5, 0);
    frameNumber++;

    // Frame 8
    D2GFX_D2DrawImage(&frameNumber, basePositionX + 144, basePositionY + 553, 0xFFFFFFFF, 5, 0);
    frameNumber++;

    // Frame 9
    D2GFX_D2DrawImage(&frameNumber, basePositionX, basePositionY + 553, 0xFFFFFFFF, 5, 0);
    frameNumber++;
}

// This function is used to prevent running unwanted 640 code.
int __fastcall HD::GetResolutionMode_Interception() {
    return (*D2CLIENT_ScreenSizeX >= 800) ? 2 : 0;
}
