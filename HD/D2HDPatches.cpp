/****************************************************************************
*                                                                           *
*   D2HDPatches.cpp                                                         *
*   Copyright (C) 2017 Mir Drualga                                          *
*                                                                           *
*   D2Ex: Copyright (c) 2011-2014 Bartosz Jankowski                         *
*                                                                           *
*   Licensed under the Apache License, Version 2.0 (the "License");         *
*   you may not use this file except in compliance with the License.        *
*   You may obtain a copy of the License at                                 *
*                                                                           *
*   http://www.apache.org/licenses/LICENSE-2.0                              *
*                                                                           *
*   Unless required by applicable law or agreed to in writing, software     *
*   distributed under the License is distributed on an "AS IS" BASIS,       *
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*
*   See the License for the specific language governing permissions and     *
*   limitations under the License.                                          *
*                                                                           *
*---------------------------------------------------------------------------*
*                                                                           *
*   Defines the functions that expands Diablo II's standard functions to    *
*   allow changing to and using custom resolutions.                         *
*                                                                           *
*****************************************************************************/

#include "D2HDPatches.h"
#include "../D2Ptrs.h"

int __stdcall GetNewResolutionId();
int __stdcall GetNewResolutionOnGameStart(int resolutionMode);
int __stdcall SetupGlideRenderResolution();

void __declspec(naked) HD::ResizeWindow_Interception() {
    __asm {
        PUSH [ESP + 0x10]
        PUSH [ESP + 0x10]
        PUSH [ESP + 0x10]
        CALL[HD::D2GFX_GetModeParams]
        RET
    }
}

/*
    General function to set width and height using mode value.
    Modify this function to define new resolutions.
*/
void __stdcall HD::D2GFX_GetModeParams(int mode, DWORD* width, DWORD* height) {
    switch (mode) {
    case 0:
        *width = 640;
        *height = 480;
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

    case 4:
        *width = CustomWidth;
        *height = CustomHeight;
        break;

    default:
        *width = 640;
        *height = 480;
        int response = MessageBoxA(nullptr, "It appears that you have specified a custom resolution, but you haven't defined its width and height.", "Missing Definition Case", MB_OK | MB_ICONSTOP);
        exit(0);
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
        CALL[HD::D2GFX_GetModeParams]
        MOV ESI, [ESP]
        MOV EDX, [ESP+0x4]
        ADD ESP, 0x8
        RET
    }
}

void __declspec(naked) HD::ResizeForgroundRenderWidth_Interception() {
    __asm {
        PUSHAD
        SUB ESP, 4
        PUSH ESP
        PUSH D2GDI_ForegroundRenderWidth
        PUSH ESI
        CALL [HD::D2GFX_GetModeParams]
        ADD ESP, 4
        POPAD
        MOV EAX, 1
        RET
    }
}

void HD::ResizeGameLogicResolution_Interception() {
    __asm PUSHAD

    int mode;
    __asm MOV mode, ESI

    HD::D2GFX_GetModeParams(mode, D2CLIENT_ScreenSizeX, D2CLIENT_ScreenSizeY);
    *D2CLIENT_InventoryArrangeMode = mode;

    __asm POPAD
}

void __declspec(naked) HD::SetResolutionModeId_Interception() {
    __asm {
        CALL[GetNewResolutionId]
        MOV ESI, EAX
        RET
    }
}

void __declspec(naked) HD::SetResolutionModeOnGameStart001_Interception() {
    __asm {
        PUSH EAX
        PUSH ECX
        ADD EAX, 01
        PUSH EAX
        CALL[GetNewResolutionOnGameStart]
        MOV ESI, EAX
        POP ECX
        POP EAX
        RET
    }
}

void __declspec(naked) HD::SetResolutionModeOnGameStart002_Interception() {
    __asm {
        PUSH EAX
        PUSH ECX
        PUSH EDI
        ADD EDI, 01
        PUSH EDI
        CALL[GetNewResolutionOnGameStart]
        POP EDI
        MOV ESI, EAX
        POP ECX
        POP EAX
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

int __stdcall GetNewResolutionOnGameStart(int resolutionMode) {
    int mode = resolutionMode;

    if (mode == 1) {
        return 2;
    } else {
        return mode;
    }
}

void __declspec(naked) HD::SetRegistryResolutionModeId_Interception() {
    __asm {
        PUSHAD
        
        ADD ECX, 0x124
        MOV [ECX], 0
        CMP ECX, D2CLIENT_CurrentRegistryResolutionMode
        JNE SetRegistryResolutionModeId_Interception_Jump1
        PUSH ECX
        CALL [GetNewResolutionId]
        POP ECX
        MOV [ECX], EAX
    SetRegistryResolutionModeId_Interception_Jump1:
        POPAD
        RET
    }
}

void __declspec(naked) HD::SaveRegistryResolution_Interception(int mode) {
    __asm {
        MOV ESI, [ESP + 0x4]
        PUSHAD
        PUSH ESI
        CALL [Config::WriteRegistryResolution]
        POPAD
        RET 0x4
    }
}

void __declspec(naked) HD::LoadRegistryResolution_Interception(int* mode) {
    __asm {
        MOV ESI, [ESP + 0x4]
        PUSHAD
        PUSH ESI
        CALL[Config::ReadRegistryResolution]
        POPAD
        RET 0x4
    }
}

void __declspec(naked) HD::SetupGlideRenderResolution_Interception() {
    __asm {
        PUSH EBX
        PUSH EDI
        CALL [SetupGlideRenderResolution]
        MOV ECX, EAX
        POP EDI
        POP EBX
        MOV ESI, 0
        MOV EDX, 0; Set EDX to 0
        RET
    }
}

void __declspec(naked) HD::ResizeDDrawWindow_Interception() {
    __asm {
        SUB ESP, 0x8
        LEA ECX, DWORD PTR DS:[ESP]
        LEA EDX, DWORD PTR DS:[ESP + 0x4]

        PUSHAD
        PUSH EDX
        PUSH ECX
        PUSH EAX
        CALL D2GFX_GetModeParams
        POPAD

        MOV EDX, DWORD PTR DS:[EDX]
        MOV EAX, DWORD PTR DS : [D2DDRAW_GameWindowSizeY]
        MOV DWORD PTR DS : [EAX], EDX
        MOV ECX, DWORD PTR DS:[ECX]

        ADD ESP, 0x8
        RET
    }
}

void __declspec(naked) HD::ResizeD3DWindow_Interception() {
    __asm {
        PUSHAD
        PUSH D2DIRECT3D_GameWindowSizeY
        PUSH D2DIRECT3D_GameWindowSizeX
        PUSH EAX
        CALL D2GFX_GetModeParams
        POPAD
        RET
    }
}

int __stdcall SetupGlideRenderResolution() {
    int newResolutionMode, glideVideoMode;
    __asm MOV newResolutionMode, ESI

    HD::D2GFX_GetModeParams(newResolutionMode, D2GLIDE_ScreenSizeX, D2GLIDE_ScreenSizeY);

    switch (newResolutionMode) {
    case 0:
        glideVideoMode = 7;
        break;

    case 1:
        glideVideoMode = 8;
        break;

    default:
        glideVideoMode = (glideVideoMode - 2) + 8;
        break;
    }

    // Apply special case for /r/Diablo2Resurgence
    if (D2Version::GetGlide3xVersionID() == D2Version::Glide3xVersionID::RESURGENCE && *D2GLIDE_ScreenSizeX == 1068 && *D2GLIDE_ScreenSizeY == 600) {
        glideVideoMode = 0xFF;
    }

    return glideVideoMode;
}

void __stdcall HD::SetupGlideWindowSize() {
    __asm PUSHAD

    int newGlideVideoMode;
    __asm MOV newGlideVideoMode, EAX

    int resolutionMode = (newGlideVideoMode == 7) ? 0 : ((newGlideVideoMode - 8) + 2);
    HD::D2GFX_GetModeParams(resolutionMode, *GLIDE3X_GameWindowSizeX, *GLIDE3X_GameWindowSizeY);

    __asm POPAD
}

// Repositions panels in the correct location, independent of resolution.
void __stdcall HD::RepositionPanels() {
    *D2CLIENT_PanelOffsetX = (*D2CLIENT_ScreenSizeX / 2) - 320;
    *D2CLIENT_PanelOffsetY = ((int)*D2CLIENT_ScreenSizeY - 480) / -2;
}

// This function is used to prevent running unwanted 640 code.
int __stdcall HD::GetResolutionMode_Patch() {
    return (*D2CLIENT_ScreenSizeX >= 800) ? 2 : 0;
}
