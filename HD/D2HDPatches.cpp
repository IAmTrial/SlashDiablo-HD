#include "D2HDPatches.h"
#include "../DLLmain.h"
#include "../D2Ptrs.h"

void DrawUILeftPanelBackground();
void DrawUIRightPanelBackground();

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
        if (EnableCinematicsFix && (/*!*FOG_InGame && (*STORM_IsCinematic ||*/ firstStart)) {
            if (firstStart > 0) {
                firstStart--;
            }
            glideVideoMode = 7;
            *D2GLIDE_ScreenSizeX = 640;
            *D2GLIDE_ScreenSizeY = 480;
        }
        else {
            glideVideoMode = 0xFF;
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

__declspec(naked) void* __stdcall LoadCellFile(const char* szBuffer)
{
    __asm
    {
        PUSH ESI
            MOV ESI, [ESP + 8]
            CALL[D2CLIENT_LoadUIImage]
            POP ESI
            RETN 4
    }
}

// Redraws the left side panel borders in the correct places, independent of resolution.
void HD::RedrawUILeftPanelBorders_Interception() {
    __asm push edi

    if (D2MRFancyBorderInterfaceLeft == nullptr) {
        D2MRFancyBorderInterfaceLeft = LoadCellFile("Panel/D2MRFancyBorderInterfaceLeft");
    }
    if (D2MRFancyBorderBottom == nullptr) {
        D2MRFancyBorderBottom = LoadCellFile("Panel/D2MRFancyBorderBottom");
    }
    if (D2MRFancyBorderTop == nullptr) {
        D2MRFancyBorderTop = LoadCellFile("Panel/D2MRFancyBorderTop");
    }
    if (D2MRFancyBorderCorner == nullptr) {
        D2MRFancyBorderCorner = LoadCellFile("Panel/D2MRFancyBorderCorner");
    }

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2) - 400;
    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    // Draw left border pieces
    D2ImageDrawStrc borderLeft = { 0 };
    borderLeft.nFrame = 0;
    borderLeft.pCellFile = D2MRFancyBorderInterfaceLeft;

    D2GFX_DrawImage(&borderLeft, basePositionX, (basePositionY + 256), LeftPanelBorderColor, 5, nullptr);
    borderLeft.nFrame++;
    D2GFX_DrawImage(&borderLeft, basePositionX, (basePositionY + 256) + 256, LeftPanelBorderColor, 5, nullptr);
    borderLeft.nFrame++;
    D2GFX_DrawImage(&borderLeft, basePositionX, (basePositionY + 256) + (256 + 40), LeftPanelBorderColor, 5, nullptr);

    // Draw upper border pieces

    // Draw lower border pieces

    // Draw corner border pieces



    /*
    D2GFX_DrawImage(&image, basePositionX, basePositionY + 253, LeftPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 1
    D2GFX_DrawImage(&image, basePositionX + 256, basePositionY + 63, LeftPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 2
    D2GFX_DrawImage(&image, basePositionX, basePositionY + 484, LeftPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 3
    D2GFX_DrawImage(&image, basePositionX, basePositionY + 553, LeftPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 4
    D2GFX_DrawImage(&image, basePositionX + 256, basePositionY + 553, LeftPanelBorderColor, 5, 0);
    image.nFrame++;*/

    __asm pop edi
}

// Redraws the right side panel borders in the correct places, independent of resolution.
void HD::RedrawUIRightPanelBorders_Interception() {
    __asm push edi

    if (*D2CLIENT_PanelBorderImage == NULL) {
        *D2CLIENT_PanelBorderImage = LoadCellFile("Panel/800BorderFrame");
    }

    D2ImageDrawStrc image = { 0 };
    image.pCellFile = *D2CLIENT_PanelBorderImage;
    image.nFrame = 10;

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2);
    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    image.nFrame = 5;

    // Frame 5
    D2GFX_DrawImage(&image, basePositionX, basePositionY + 63, RightPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 6
    D2GFX_DrawImage(&image, basePositionX + 144, basePositionY + 253, RightPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 7
    D2GFX_DrawImage(&image, basePositionX + 313, basePositionY + 484, RightPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 8
    D2GFX_DrawImage(&image, basePositionX + 144, basePositionY + 553, RightPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 9
    D2GFX_DrawImage(&image, basePositionX, basePositionY + 553, RightPanelBorderColor, 5, 0);
    image.nFrame++;

    __asm pop edi
}

void HD::DrawUIPanelBackground() {
    switch (*D2CLIENT_PanelOpenMode) {
    case 1:
        DrawUIRightPanelBackground();
        break;

    case 2:
        DrawUILeftPanelBackground();
        break;

    case 3:
        DrawUILeftPanelBackground();
        DrawUIRightPanelBackground();
        break;

    default:
        break;
    }
}

// Draws a background on opened left panels to cover up extra space.
void DrawUILeftPanelBackground() {
    if (D2MRStoneBack == NULL) {
        D2MRStoneBack = LoadCellFile(/*"data/global/ui/*/"Panel/D2MRStoneBack");
    }

    D2ImageDrawStrc image = { 0 };
    image.pCellFile = D2MRStoneBack;
    image.nFrame = 0;

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2);

    // Draw background pieces
    const DWORD backWidth = 256;
    const DWORD backHeight = 256;

    for (int row = 0; (row * backHeight) < *D2CLIENT_ScreenSizeY; row++) {
        DWORD backBasePositionY = ((row + 1) * backHeight);

        for (int col = 0; (int)(basePositionX - (col * backWidth)) >= 0; col++) {
            image.nFrame = ((row % 2) * 2) + (col % 2);
            DWORD backBasePositionX = basePositionX - ((col + 1) * backWidth);

            D2GFX_DrawImage(&image, backBasePositionX, backBasePositionY, LeftPanelBackgroundColor, 5, 0);
        }
    }
}

// Draws a background on opened right panels to cover up extra space.
void DrawUIRightPanelBackground() {
    if (D2MRStoneBack == NULL) {
        D2MRStoneBack = LoadCellFile("Panel/D2MRStoneBack");
    }

    D2ImageDrawStrc image = { 0 };
    image.pCellFile = D2MRStoneBack;
    image.nFrame = 0;

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2);

    // Draw background pieces
    const DWORD backWidth = 256;
    const DWORD backHeight = 256;

    for (int row = 0; (row * backHeight) < *D2CLIENT_ScreenSizeY; row++) {
        DWORD backBasePositionY = ((row + 1) * backHeight);
        for (int col = 0; basePositionX + (col * backWidth) < *D2CLIENT_ScreenSizeX; col++) {
            image.nFrame = ((row % 2) * 2) + ((col + 1) % 2);
            DWORD backBasePositionX = basePositionX + (col * backWidth);

            D2GFX_DrawImage(&image, backBasePositionX, backBasePositionY, RightPanelBackgroundColor, 5, 0);
        }
    }
}

// This function is used to prevent running unwanted 640 code.
int __fastcall HD::GetResolutionMode_Interception() {
    return (*D2CLIENT_ScreenSizeX >= 800) ? 2 : 0;
}
