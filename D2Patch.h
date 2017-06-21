#pragma once

#ifndef _D2PATCH_H
#define _D2PATCH_H

#include "D2PatchConst.h"

/****************************************************************************
*                                                                           *
*   D2Patch.h                                                               *
*   Copyright (C) Olivier Verville                                          *
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

static const DLLPatchStrc gptTemplatePatches[] =
{
    // Panel Positioning Fix
    { D2DLL_D2CLIENT, 0xC39F6, PATCH_NOPBLOCK, FALSE, 39 },
    { D2DLL_D2CLIENT, 0xC39F6, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0xC39F6 + 1, (int)HD::RepositionPanels, TRUE, 0 },

    // Enable Panel Borders Fix
    { D2DLL_D2CLIENT, 0x29262, PATCH_NOPBLOCK, FALSE, 5 },
    { D2DLL_D2CLIENT, 0x29262, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x29262 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Resize Game Window; D2GFX.Ordinal10025
    { D2DLL_D2GFX, 0x7FD4, 0x81, FALSE, 1 },
    { D2DLL_D2GFX, 0x7FD4 + 2, NUMBER_OF_CUSTOM_RESOLUTIONS, FALSE, 0 },
    { D2DLL_D2GFX, 0x7FDA, 0x4977, FALSE, 0 },
    { D2DLL_D2GFX, 0x7FDC, PATCH_NOPBLOCK, FALSE, 73 },
    { D2DLL_D2GFX, 0x7FDC, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2GFX, 0x7FDC + 1, (int)HD::ResizeWindow_Interception, TRUE, 0 },
    { D2DLL_D2GFX, 0x7FE1, PATCH_RETN0C | 0x90000000, FALSE, 0 },

    // Resize Rendering Resolution
    { D2DLL_D2GDI, 0x6D34, PATCH_NOPBLOCK, FALSE, 43 },
    { D2DLL_D2GDI, 0x6D34, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2GDI, 0x6D34 + 1, (int)HD::ResizeRenderResolution_Interception, TRUE, 0 },

    // Other Patches, Unsure what they do
    /* Unused?
    { D2DLL_D2GDI, 0x62C7 + 2 + 4, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GDI, 0x62B1 + 2 + 4, RESOLUTION_800_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GDI, 0x62BC + 2 + 4, RESOLUTION_1344_TO_HD_WIDTH, FALSE, 0 },
    */
    { D2DLL_D2GDI, 0x716E + 2 + 4, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GDI, 0x714D + 2 + 4, RESOLUTION_800_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GDI, 0x715D + 2 + 4, RESOLUTION_1344_TO_HD_WIDTH, FALSE, 0 },

    { D2DLL_D2CLIENT, 0x45219 + 1, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x45332 + 1, RESOLUTION_800_TO_HD_WIDTH, FALSE, 0 },
    // { D2DLL_D2CLIENT, UNKNOWN + 1, RESOLUTION_1344_TO_HD_WIDTH, FALSE, 0 },

    { D2DLL_D2CLIENT, 0x45224 + 2 + 4, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x4533E + 2 + 4, RESOLUTION_800_TO_HD_HEIGHT, FALSE, 0 },
    // { D2DLL_D2CLIENT, UNKNOWN + 2 + 4, RESOLUTION_1344_TO_HD_HEIGHT, FALSE, 0 },

    { D2DLL_D2CLIENT, 0x45239 + 2 + 4, RESOLUTION_640_TO_HD_HEIGHT - 40, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x45357 + 2 + 4, RESOLUTION_800_TO_HD_HEIGHT - 40, FALSE, 0 },
    // { D2DLL_D2CLIENT, UNKNOWN + 2 + 4, RESOLUTION_1344_TO_HD_HEIGHT - 40, FALSE, 0 },

    { D2DLL_D2GFX, 0x8141 + 1, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GFX, 0x8154 + 2, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },

    // Untested possibly suspect pointers: D2GFX+1FF8D,818d2 && D2Client.dll+232E8

    // Correct Resizing of Window from any resolution to a smaller one.
    { D2DLL_D2GFX, 0x83F0 + 1, INT_MAX, FALSE, 0 },
    { D2DLL_D2GFX, 0x8403 + 2, INT_MAX, FALSE, 0 },

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
    { D2DLL_D2GDI, 0x7044, PATCH_NOPBLOCK, FALSE, 51 },
    { D2DLL_D2GDI, 0x7044, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2GDI, 0x7044 + 1, (int)HD::ResizeForgroundRenderWidth_Interception, TRUE, 0 },
    { D2DLL_D2GDI, 0x7044 + 5, 0x90905E5F, FALSE, 0 },
    { D2DLL_D2GDI, 0x7044 + 7, PATCH_RETN | 0x90909000, FALSE, 0 },

    // Resize Game Logic Resolution and FOV
    { D2DLL_D2CLIENT, 0x10DFD, PATCH_NOPBLOCK, FALSE, 0x10E49 - 0x10DFD },
    { D2DLL_D2CLIENT, 0x10DFD, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x10DFD + 1, (int)HD::ResizeGameLogicResolution_Interception, TRUE, 0 },

    // Properly transfer back to a valid resolution
    { D2DLL_D2CLIENT, 0x6628F, PATCH_NOPBLOCK, FALSE, 7 },
    { D2DLL_D2CLIENT, 0x6628F, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x6628F + 1, (int)HD::SetResolutionModeOnGameStart_Interception, TRUE, 0 },

    // Add New Resolutions Without Replacement
    { D2DLL_D2CLIENT, 0x662C5, PATCH_NOPBLOCK, FALSE, 7 },
    { D2DLL_D2CLIENT, 0x662C5, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x662C5 + 1, (int)HD::SetResolutionModeId_Interception, TRUE, 0 },

    // Change Maximum Recognized Resolutions from Registry
    // { D2DLL_D2CLIENT, 0xEABD8, 2, FALSE, 0 },

    // Modify Resolution Display in Options
    { D2DLL_D2CLIENT, 0x653FF, PATCH_NOPBLOCK, FALSE, 7 },
    { D2DLL_D2CLIENT, 0x653FF, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x653FF + 1, (int)HD::DetermineText, TRUE, 0 },

    // Modify the value of the registry resolution ID
    { D2DLL_D2CLIENT, 0x651E0, PATCH_NOPBLOCK, FALSE, 0x651EA - 0x651E0 },
    { D2DLL_D2CLIENT, 0x651E0, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x651E0 + 1, (int)HD::SetRegistryResolutionModeId_Interception, TRUE, 0 },

    // Replace 640 with HD, Fix D2DDraw Fullscreen
    /* Highly unstable! Currently not functional!
    { D2DLL_D2DDRAW, 0x84CB + 1, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2DDRAW, 0x84D0 + 1, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },
    { D2DLL_D2DDRAW, 0x9343 + 2, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2DDRAW, 0x85C6 + 1, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2DDRAW, 0x85CB + 2 + 4, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },
    { D2DLL_D2DDRAW, 0x85C6, PATCH_NOPBLOCK, FALSE, 15 },
    { D2DLL_D2DDRAW, 0x85C6, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2DDRAW, 0x85C6 + 1, (int)HD::Replace640_ResizeD2DWindow_Interception, TRUE, 0 },
    */

    // Replace for HD, Resize Glide Render Logic Resolution
    { D2DLL_D2GLIDE, 0xDCC6, PATCH_NOPBLOCK, FALSE, 0xDD0A - 0xDCC6 },
    { D2DLL_D2GLIDE, 0xDCC6, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2GLIDE, 0xDCC6 + 1, (int)HD::SetupGlideRenderResolution_Interception, TRUE, 0 },

    { D2DLL_INVALID } // this must be the last entry in the array!
};

// Enables border backgrounds for opened panels.
static const DLLPatchStrc drawPatches[] = {
    // Redraw UI Panel Border Fix
    { D2DLL_D2CLIENT, 0x271C0, PATCH_NOPBLOCK, FALSE, 203 },
    { D2DLL_D2CLIENT, 0x271C0, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x271C0 + 1, (int)HD::RedrawUILeftPanelBorders, TRUE, 0 },
    { D2DLL_D2CLIENT, 0x270D0, PATCH_NOPBLOCK, FALSE, 225 },
    { D2DLL_D2CLIENT, 0x270D0, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x270D0 + 1, (int)HD::RedrawUIRightPanelBorders, TRUE, 0 },

    /* Assumption is that this patch is already enabled. Patches below will not work without this!
    { D2DLL_D2CLIENT, 0xC39F6, PATCH_NOPBLOCK, FALSE, 39 },
    { D2DLL_D2CLIENT, 0xC39F6, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0xC39F6 + 1, (int)HD::PanelPosition_Interception, TRUE, 0 },
    */

    // Draw background
    { D2DLL_D2CLIENT, 0xC39FB, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0xC39FB + 1, (int)HD::DrawUIPanelBackground, TRUE, 0 },

    // Draw bottom control panel
    { D2DLL_D2CLIENT, 0xC3A00, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0xC3A00 + 1, (int)HD::DrawUIControlPanel, TRUE, 0 },

    // Unload additional resources when game exits
    { D2DLL_D2CLIENT, 0x26F8D, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x26F8D + 1, (int)HD::UnloadCellFiles, TRUE, 0 },

    { D2DLL_INVALID }
};

// Fixes border panel click detection issue for HD mode. Shouldn't need to be disabled.
static const DLLPatchStrc borderPanelClickDetectionPatches[] = {
    // Left panel click block
    { D2DLL_D2CLIENT, 0xBCB30 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Right panel click block
    { D2DLL_D2CLIENT, 0x8F880 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    { D2DLL_INVALID }
};

// Replace for HD, Resize Glide Game Window, but not used if using custom glide3x.dll
static const DLLPatchStrc glide3xPatches[] = {
    { D2DLL_GLIDE3X, 0xCA97, PATCH_NOPBLOCK, FALSE, 0xCBA7 - 0xCA97 },
    { D2DLL_GLIDE3X, 0xCA97, PATCH_CALL, FALSE, 0 },
    { D2DLL_GLIDE3X, 0xCA97 + 1, (int)HD::SetupGlideWindowSize, TRUE, 0 },
    
    { D2DLL_INVALID }
};

static const DLLPatchStrc controlPanel800Patches[] = {
    // Unknown
    { D2DLL_D2CLIENT, 0x506AF + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Skill button animation click detection
    { D2DLL_D2CLIENT, 0x506C9 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Unknown
    { D2DLL_D2CLIENT, 0x5075F + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Stat button animation click detection
    { D2DLL_D2CLIENT, 0x5077D + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Unknown
    { D2DLL_D2CLIENT, 0x50810 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Skill button click detection
    { D2DLL_D2CLIENT, 0x5082E + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Unknown
    { D2DLL_D2CLIENT, 0x50B70 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Stat button click detection
    { D2DLL_D2CLIENT, 0x50B8E + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Control panel to 800 control panel.
    { D2DLL_D2CLIENT, 0x272A2 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Stats button fix (greyed out)
    { D2DLL_D2CLIENT, 0x50103 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Stats level up button fix
    { D2DLL_D2CLIENT, 0x50447 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    { D2DLL_D2CLIENT, 0x504EC + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    { D2DLL_D2CLIENT, 0x50563 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    { D2DLL_D2CLIENT, 0x505C8 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    
    // Skill button fix (greyed out)
    { D2DLL_D2CLIENT, 0x50023 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    // Skill level up button fix
    { D2DLL_D2CLIENT, 0x50207 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    { D2DLL_D2CLIENT, 0x502A5 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    { D2DLL_D2CLIENT, 0x5031C + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    { D2DLL_D2CLIENT, 0x50380 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },
    { D2DLL_D2CLIENT, 0x503A1 + 1, (int)HD::GetResolutionMode_Patch, TRUE, 0 },

    { D2DLL_INVALID }
};

// end of file --------------------------------------------------------------
#endif