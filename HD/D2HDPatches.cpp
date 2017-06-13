#include "D2HDPatches.h"
#include "../DLLmain.h"
#include "../D2Ptrs.h"

void __stdcall ResizeWindow(int mode, int* width, int* height);
int __stdcall GetNewResolutionId();

void __declspec(naked) HD::ResizeWindow_Interception() {
    __asm {
        PUSH [ESP + 0x10]
        PUSH [ESP + 0x10]
        PUSH [ESP + 0x10]
        CALL [ResizeWindow]
        RET
    }
}

void __stdcall ResizeWindow(int mode, int* width, int* height) {
    switch (mode) {
    case 0:
        *width = RESOLUTION_640_TO_HD_WIDTH;
        *height = RESOLUTION_640_TO_HD_HEIGHT;
        break;

    case 1:
        *width = 800;
        *height = 600;
        break;

    case 2:
        *width = 800;
        *height = 600;
        break;

    case 3:
        *width = 1344;
        *height = 700;
        break;

    default:
        break;
    }
}

void __declspec(naked) HD::ResizeRenderResolution_Interception() {
    __asm {
        SUB ESP, 0x8
        LEA ESI, [ESP+0x4]
        LEA EDX, [ESP]
        PUSH ESI
        PUSH EDX
        PUSH EAX
        CALL[ResizeWindow]
        MOV ESI, [ESP]
        MOV EDX, [ESP+0x4]
        ADD ESP, 0x8
        RET
    }
}

void HD::ResizeForgroundRenderWidth_Interception() {
    int mode, temp;
    __asm MOV mode, ESI

    ResizeWindow(mode, D2GDI_ForegroundRenderWidth, &temp);

    __asm MOV EAX, 0x1
}

void HD::ResizeGameLogicResolution_Interception() {
    int mode;
    __asm MOV mode, ESI

    ResizeWindow(mode, D2CLIENT_ScreenSizeX, D2CLIENT_ScreenSizeY);
    *D2CLIENT_InventoryArrangeMode = (mode > 0) ? 1 : 0;
}

void __declspec(naked) HD::SetResolutionModeId_Interception() {
    __asm {
        CALL[GetNewResolutionId]
        MOV ESI, EAX
        RET
    }
}

int __stdcall GetNewResolutionId() {
    int mode = D2GFX_GetResolutionMode();

    if (mode >= NUMBER_OF_CUSTOM_RESOLUTIONS) {
        mode = 0;
    } else if (mode == 0) {
        mode = 2;
    } else {
        mode++;
    }

    return mode;
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

int HD::SetupGlideRenderResolution() {
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
void HD::RepositionPanels() {
    *D2CLIENT_PanelOffsetX = (*D2CLIENT_ScreenSizeX / 2) - 320;
    *D2CLIENT_PanelOffsetY = (*D2CLIENT_ScreenSizeY - 480) / -2;
}

// This function is used to prevent running unwanted 640 code.
int HD::GetResolutionMode_Patch() {
    return (*D2CLIENT_ScreenSizeX >= 800) ? 2 : 0;
}
