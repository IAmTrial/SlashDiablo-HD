/****************************************************************************
*                                                                           *
*   D2Patch.h                                                               *
*   Copyright (C) Olivier Verville                                          *
*                                                                           *
*   D2Ex: Copyright (c) 2011-2014 Bartosz Jankowski                         *
*   /r/SlashDiablo HD Modifications: Copyright (C) 2017 Mir Drualga         *
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
*   https://github.com/olivier-verville/D2Template                          *
*                                                                           *
*   This file is where you declare all your patches, in order to inject     *
*   your own code into the game. Each patch should be declared in the       *
*   array, in order to be handled by D2Template's patcher                   *
*                                                                           *
*****************************************************************************/

#pragma once

#ifndef _D2PATCH_H
#define _D2PATCH_H

#include "D2PatchConst.h"
#include "DLLmain.h"

static const DLLPatchStrc gptTemplatePatches[] =
{
    // Panel Positioning Fix
    { D2DLL_D2CLIENT, { 0xC39F6, 0x1D3F6 }, PATCH_NOPBLOCK, FALSE, 39 },
    { D2DLL_D2CLIENT, { 0xC39F6, 0x1D3F6 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0xC39F6 + 1, 0x1D3F6 + 1 }, (int)HD::RepositionPanels, TRUE, 0 },

    // Enable Panel Borders Fix
    { D2DLL_D2CLIENT, { 0x29262, 0x6F312 }, PATCH_NOPBLOCK, FALSE, 5 },
    { D2DLL_D2CLIENT, { 0x29262, 0x6F312 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x29262 + 1, 0x6F312 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Resize Game Window; D2GFX.Ordinal10025, D2GFX.Ordinal10064
    { D2DLL_D2GFX, { 0x7FD0, 0xB0E0 }, PATCH_NOPBLOCK, FALSE, 0x8022 - 0x7FD0 },
    { D2DLL_D2GFX, { 0x7FD0, 0xB0E0 }, PATCH_JMP, FALSE, 0 },
    { D2DLL_D2GFX, { 0x7FD0 + 1, 0xB0E0 + 1 }, (int)HD::D2GFX_GetModeParams, TRUE, 0 },

    // Resize Rendering Resolution
    { D2DLL_D2GDI, { 0x6D34, 0x7B84 }, PATCH_NOPBLOCK, FALSE, 43 },
    { D2DLL_D2GDI, { 0x6D34, 0x7B84 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2GDI, { 0x6D34 + 1, 0x7B84 + 1 }, (int)HD::ResizeRenderResolution_Interception, TRUE, 0 },

    // Correct Resizing of Window from any resolution to a smaller one.
    { D2DLL_D2GFX, { 0x83F0 + 1, 0xB42F + 1 }, INT_MAX, FALSE, 0 },
    { D2DLL_D2GFX, { 0x8403 + 2, 0xB43E + 2 }, INT_MAX, FALSE, 0 },

    /* This is called on startup and is irrelevant. D2GFX.Ordinal10072
    { D2DLL_D2GFX, 0x8747 + 1, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GFX, 0x8750 + 1, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GFX, 0x8759 + 1, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },
    { D2DLL_D2GFX, 0x8762 + 1, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },
    { D2DLL_D2GFX, 0x876B + 1, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GFX, 0x8797 + 3 + 4, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GFX, 0x87A2 + 3 + 4, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },
    */
    // Resize Foreground Rendering Width
    { D2DLL_D2GDI, { 0x7044, 0x7E94 }, PATCH_NOPBLOCK, FALSE, 51 },
    { D2DLL_D2GDI, { 0x7044, 0x7E94 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2GDI, { 0x7044 + 1, 0x7E94 + 1 }, (int)HD::ResizeForgroundRenderWidth_Interception, TRUE, 0 },
    { D2DLL_D2GDI, { 0x7044 + 5, 0x7E94 + 5 }, 0x90905E5F, FALSE, 0 },
    { D2DLL_D2GDI, { 0x7044 + 7, 0x7E94 + 7 }, PATCH_RETN | 0x90909000, FALSE, 0 },

    // Resize Game Logic Resolution and FOV
    { D2DLL_D2CLIENT, { 0x10DFD, 0x2C22D }, PATCH_NOPBLOCK, FALSE, 0x10E49 - 0x10DFD },
    { D2DLL_D2CLIENT, { 0x10DFD, 0x2C22D }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x10DFD + 1, 0x2C22D + 1 }, (int)HD::ResizeGameLogicResolution_Interception, TRUE, 0 },

    // Read From D2HD.ini Instead of Registry
    { D2DLL_D2CLIENT, { 0x44454, 0x454A4 }, PATCH_NOPBLOCK, FALSE, 0x44464 - 0x44454 },
    { D2DLL_D2CLIENT, { 0x44454, 0x454A4 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x44454 + 1, 0x454A4 + 1 }, (int)HD::LoadRegistryResolution_Interception, TRUE, 0 },

    { D2DLL_D2CLIENT, { 0x65E47, 0xC40E7 }, PATCH_NOPBLOCK, FALSE, 0x662BC - 0x662AB },
    { D2DLL_D2CLIENT, { 0x65E47, 0xC40E7 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x65E47 + 1, 0xC40E7 + 1 }, (int)HD::LoadRegistryResolution_Interception, TRUE, 0 },

    { D2DLL_D2CLIENT, { 0x66279, 0xC4519 }, PATCH_NOPBLOCK, FALSE, 0x6628A - 0x66279 },
    { D2DLL_D2CLIENT, { 0x66279, 0xC4519 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x66279 + 1, 0xC4519 + 1 }, (int)HD::LoadRegistryResolution_Interception, TRUE, 0 },

    { D2DLL_D2CLIENT, { 0xAF951, 0x85F61 }, PATCH_NOPBLOCK, FALSE, 0x6628A - 0x66279 },
    { D2DLL_D2CLIENT, { 0xAF951, 0x85F61 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0xAF951 + 1, 0x85F61 + 1 }, (int)HD::LoadRegistryResolution_Interception, TRUE, 0 },

    // Properly transfer back to a valid resolution
    { D2DLL_D2CLIENT, { 0x4446B, 0x454BB }, PATCH_NOPBLOCK, FALSE, 7 },
    { D2DLL_D2CLIENT, { 0x4446B, 0x454BB }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x4446B + 1, 0x454BB + 1 }, (int)HD::SetResolutionModeOnGameStart001_Interception, TRUE, 0 },

    { D2DLL_D2CLIENT, { 0x65E5F, 0xC40FF }, PATCH_NOPBLOCK, FALSE, 7 },
    { D2DLL_D2CLIENT, { 0x65E5F, 0xC40FF }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x65E5F + 1, 0xC40FF + 1 }, (int)HD::SetResolutionModeOnGameStart001_Interception, TRUE, 0 },

    { D2DLL_D2CLIENT, { 0x6628F, 0xC452F }, PATCH_NOPBLOCK, FALSE, 7 },
    { D2DLL_D2CLIENT, { 0x6628F, 0xC452F }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x6628F + 1, 0xC452F + 1 }, (int)HD::SetResolutionModeOnGameStart002_Interception, TRUE, 0 },

    { D2DLL_D2CLIENT, { 0xAF969, 0x85F79 }, PATCH_NOPBLOCK, FALSE, 7 },
    { D2DLL_D2CLIENT, { 0xAF969, 0x85F79 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0xAF969 + 1, 0x85F79 + 1 }, (int)HD::SetResolutionModeOnGameStart001_Interception, TRUE, 0 },

    // Write to D2HD.ini Instead of Registry
    { D2DLL_D2CLIENT, { 0x662AB, 0xC454B }, PATCH_NOPBLOCK, FALSE, 0x662BC - 0x662AB },
    { D2DLL_D2CLIENT, { 0x662AB, 0xC454B }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x662AB + 1, 0xC454B + 1 }, (int)HD::SaveRegistryResolution_Interception, TRUE, 0 },

    // Add New Resolutions Without Replacement
    { D2DLL_D2CLIENT, { 0x662C5, 0xC4565 }, PATCH_NOPBLOCK, FALSE, 7 },
    { D2DLL_D2CLIENT, { 0x662C5, 0xC4565 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x662C5 + 1, 0xC4565 + 1 }, (int)HD::SetResolutionModeId_Interception, TRUE, 0 },

    // Modify Resolution Display in Options
    { D2DLL_D2CLIENT, { 0x653FF, 0xC369F }, PATCH_NOPBLOCK, FALSE, 7 },
    { D2DLL_D2CLIENT, { 0x653FF, 0xC369F }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x653FF + 1, 0xC369F + 1 }, (int)HD::STUB_DetermineText, TRUE, 0 },

    // Modify the value of the registry resolution ID
    { D2DLL_D2CLIENT, { 0x651E0, 0xC33A0 }, PATCH_NOPBLOCK, FALSE, 0x651EA - 0x651E0 },
    { D2DLL_D2CLIENT, { 0x651E0, 0xC33A0 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x651E0 + 1, 0xC33A0 + 1 }, (int)HD::SetRegistryResolutionModeId_Interception, TRUE, 0 },

    // Fix D2DDraw Fullscreen
    { D2DLL_D2DDRAW, { 0x85C2, 0x8202 }, PATCH_NOPBLOCK, FALSE, 0x85ED - 0x85C2 },
    { D2DLL_D2DDRAW, { 0x85C2, 0x8202 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2DDRAW, { 0x85C2 + 1, 0x8202 + 1 }, (DWORD)HD::ResizeDDrawWindow_Interception, TRUE, 0 },

    { D2DLL_D2DDRAW, { 0x85F9, 0x8239 }, PATCH_NOPBLOCK, FALSE, 0x8600 - 0x85F9 },

    // Fix Direct3D Fullscreen
    { D2DLL_D2DIRECT3D, { 0xB9A4, 0xBE64 }, PATCH_NOPBLOCK, FALSE, /*0xB9D0*/ 0xB9DF - 0xB9A4 },
    { D2DLL_D2DIRECT3D, { 0xB9A4, 0xBE64 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2DIRECT3D, { 0xB9A4 + 1, 0xBE64 + 1 }, (DWORD)HD::ResizeD3DWindow_Interception, TRUE, 0 },

    // Replace for HD, Resize Glide Render Logic Resolution
    { D2DLL_D2GLIDE, { 0xDCC6, 0xD5D6 }, PATCH_NOPBLOCK, FALSE, 0xDD0A - 0xDCC6 },
    { D2DLL_D2GLIDE, { 0xDCC6, 0xD5D6 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2GLIDE, { 0xDCC6 + 1, 0xD5D6 + 1 }, (int)HD::SetupGlideRenderResolution_Interception, TRUE, 0 },

    { D2DLL_INVALID } // this must be the last entry in the array!
};

// Enables border backgrounds for opened panels.
static const DLLPatchStrc drawPatches[] = {
    // Disable Blizzard's UI Panel Borders
    { D2DLL_D2CLIENT, { 0x271C0, 0x6D2B0 }, PATCH_NOPBLOCK, FALSE, 6 },
    { D2DLL_D2CLIENT, { 0x271CB, 0x6D2BB }, PATCH_NOPBLOCK, FALSE, 0x2728A - 0x271CA },

    { D2DLL_D2CLIENT, { 0x270D0, 0x6D1C0 }, PATCH_NOPBLOCK, FALSE, 225 },

    // Draw background and Redraw UI Panel Border Fix
    { D2DLL_D2CLIENT, { 0xBF361, 0x190B1 }, PATCH_JMP, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0xBF361 + 1, 0x190B1 + 1 }, (int)HD::STUB_DrawUIPanelBackground, TRUE, 0 },

    // Draw bottom control panel
    { D2DLL_D2CLIENT, { 0x272A7, 0x6D397 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x272A7 + 1, 0x6D397 + 1 }, (int)HD::STUB_DrawUIControlPanel, TRUE, 0 },

    // Unload additional resources when game exits
    { D2DLL_D2CLIENT, { 0x26E1C, 0x6CF0C }, PATCH_NOPBLOCK, FALSE, 6 },
    { D2DLL_D2CLIENT, { 0x26E1C, 0x6CF0C }, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, { 0x26E1C + 1, 0x6CF0C + 1 }, (int)HD::STUB_UnloadCellFiles, TRUE, 0 },

    { D2DLL_INVALID }
};

// Fixes border panel click detection issue for HD mode. Shouldn't need to be disabled.
static const DLLPatchStrc borderPanelClickDetectionPatches[] = {
    // Left panel click block
    { D2DLL_D2CLIENT, { 0xBCB30 + 1, 0xBF2D0 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Right panel click block
    { D2DLL_D2CLIENT, { 0x8F880 + 1, 0x94820 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    { D2DLL_INVALID }
};

// Replace for HD, Resize Glide Game Window, but not used if using custom glide3x.dll
static const DLLPatchStrc glide3xPatches[] = {
    { D2DLL_GLIDE3X, { 0xCA97, 0xCA97 }, PATCH_NOPBLOCK, FALSE, 0xCBA7 - 0xCA97 },
    { D2DLL_GLIDE3X, { 0xCA97, 0xCA97 }, PATCH_CALL, FALSE, 0 },
    { D2DLL_GLIDE3X, { 0xCA97 + 1, 0xCA97 + 1 }, (int)HD::SetupGlideWindowSize, TRUE, 0 },

    { D2DLL_INVALID }
};

static const DLLPatchStrc controlPanel800Patches[] = {
    // Unknown
    { D2DLL_D2CLIENT, { 0x506AF + 1, 0x211DF + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Skill button animation click detection
    { D2DLL_D2CLIENT, { 0x506C9 + 1, 0x211F9 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Unknown
    { D2DLL_D2CLIENT, { 0x5075F + 1, 0x2128F + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Stat button animation click detection
    { D2DLL_D2CLIENT, { 0x5077D + 1, 0x212AD + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Unknown
    { D2DLL_D2CLIENT, { 0x50810 + 1, 0x21340 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Skill button click detection
    { D2DLL_D2CLIENT, { 0x5082E + 1, 0x2135E + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Unknown
    { D2DLL_D2CLIENT, { 0x50B70 + 1, 0x216A0 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Stat button click detection
    { D2DLL_D2CLIENT, { 0x50B8E + 1, 0x216BE + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Control panel to 800 control panel.
    { D2DLL_D2CLIENT, { 0x272A2 + 1, 0x6D392 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Stats button fix (greyed out)
    { D2DLL_D2CLIENT, { 0x50103 + 1, 0x21093 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Stats level up button fix
    { D2DLL_D2CLIENT, { 0x50447 + 1, 0x20E67 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    { D2DLL_D2CLIENT, { 0x504EC + 1, 0x20F0C + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    { D2DLL_D2CLIENT, { 0x50563 + 1, 0x20F83 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    { D2DLL_D2CLIENT, { 0x505C8 + 1, 0x20FE8 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Skill button fix (greyed out)
    { D2DLL_D2CLIENT, { 0x50023 + 1, 0x20DA3 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Skill level up button fix
    { D2DLL_D2CLIENT, { 0x50207 + 1, 0x20B77 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    { D2DLL_D2CLIENT, { 0x502A5 + 1, 0x20C15 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    { D2DLL_D2CLIENT, { 0x5031C + 1, 0x20C8C + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    { D2DLL_D2CLIENT, { 0x50380 + 1, 0x20CF0 + 1 }, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    { D2DLL_INVALID }
};

// Patches inventory positions to be in the correct location. Credits to D2Ex.
static const DLLPatchStrc inventoryPatches[] = {
    // D2Common.Ordinal10333
    { D2DLL_D2COMMON, { 0x13340, 0x70780 }, PATCH_NOPBLOCK, FALSE, 7 },
    { D2DLL_D2COMMON, { 0x13340, 0x70780 }, PATCH_JMP, FALSE, 0 },
    { D2DLL_D2COMMON, { 0x13340 + 1, 0x70780 + 1 }, (int)Inventory::GetBeltPos, TRUE, 0 },

    // D2Common.Ordinal10991
    { D2DLL_D2COMMON, { 0x132A0, 0x706A0 }, PATCH_NOPBLOCK, FALSE, 10 },
    { D2DLL_D2COMMON, { 0x132A0, 0x706A0 }, PATCH_JMP, FALSE, 0 },
    { D2DLL_D2COMMON, { 0x132A0 + 1, 0x706A0 + 1 }, (int)Inventory::GetBeltsTxtRecord, TRUE, 0 },

    // D2Common.Ordinal11012
    { D2DLL_D2COMMON, { 0x82030, 0x6BFB0 }, PATCH_NOPBLOCK, FALSE, 8 },
    { D2DLL_D2COMMON, { 0x82030, 0x6BFB0 }, PATCH_JMP, FALSE, 0 },
    { D2DLL_D2COMMON, { 0x82030 + 1, 0x6BFB0 + 1 }, (int)Inventory::GetInventorySize, TRUE, 0 },

    // D2Common.Ordinal10760
    { D2DLL_D2COMMON, { 0x81FB0, 0x6BF30 }, PATCH_NOPBLOCK, FALSE, 8 },
    { D2DLL_D2COMMON, { 0x81FB0, 0x6BF30 }, PATCH_JMP, FALSE, 0 },
    { D2DLL_D2COMMON, { 0x81FB0 + 1, 0x6BF30 + 1 }, (int)Inventory::GetInventoryGrid, TRUE, 0 },

    // D2Common.Ordinal10701
    { D2DLL_D2COMMON, { 0x81F20, 0x6BEA0 }, PATCH_NOPBLOCK, FALSE, 8 },
    { D2DLL_D2COMMON, { 0x81F20, 0x6BEA0 }, PATCH_JMP, FALSE, 0 },
    { D2DLL_D2COMMON, { 0x81F20 + 1, 0x6BEA0 + 1 }, (int)Inventory::GetInventoryField, TRUE, 0 },

    { D2DLL_INVALID }
};

// end of file --------------------------------------------------------------
#endif