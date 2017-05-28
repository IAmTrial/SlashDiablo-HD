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
        if (EnableCinematicsFix && (/*!*FOG_InGame && (*STORM_IsCinematic ||*/ firstStart)) {
            if (firstStart > 0) {
                firstStart--;
            }
            glideVideoMode = 7;
            *D2GLIDE_ScreenSizeX = 640;
            *D2GLIDE_ScreenSizeY = 480;
        } else {
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

// This function is used to prevent running unwanted 640 code.
int __fastcall HD::GetResolutionMode_Interception() {
    return (*D2CLIENT_ScreenSizeX >= 800) ? 2 : 0;
}
