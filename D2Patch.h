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
    { D2DLL_D2CLIENT, 0xC39F6 + 1, (int)HD::PanelPosition_Interception, TRUE, 0 },

    // Enable Panel Borders Fix
    { D2DLL_D2CLIENT, 0x29262, PATCH_NOPBLOCK, FALSE, 5 },
    { D2DLL_D2CLIENT, 0x29262, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x29262 + 1, (int)HD::GetResolutionMode_Interception, TRUE, 0 },

    // Redraw UI Panel Border Fix
    { D2DLL_D2CLIENT, 0x271ED, PATCH_NOPBLOCK, FALSE, 154 },
    { D2DLL_D2CLIENT, 0x271ED, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x271ED + 1, (int)HD::RedrawUILeftPanelBorders_Interception, TRUE, 0 },
    { D2DLL_D2CLIENT, 0x270F2, PATCH_NOPBLOCK, FALSE, 187 },
    { D2DLL_D2CLIENT, 0x270F2, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x270F2 + 1, (int)HD::RedrawUIRightPanelBorders_Interception, TRUE, 0 },

    // Replace for HD, Resize Game Window
    { D2DLL_D2GFX, 0x7FE8 + 2, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GFX, 0x7FEE + 2, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },
    { D2DLL_D2GFX, 0x7FFF + 2, RESOLUTION_800_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GFX, 0x8005 + 2, RESOLUTION_800_TO_HD_HEIGHT, FALSE, 0 },
    { D2DLL_D2GFX, 0x8016 + 2, RESOLUTION_1344_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GFX, 0x801C + 2, RESOLUTION_1344_TO_HD_HEIGHT, FALSE, 0 },

    // Replace for HD, Resize Rendering Resolution
    { D2DLL_D2GDI, 0x6D55 + 1, (RESOLUTION_640_TO_HD_WIDTH - (RESOLUTION_640_TO_HD_WIDTH % 4)), FALSE, 0 },
    { D2DLL_D2GDI, 0x6D5A + 1, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },
    { D2DLL_D2GDI, 0x6D3D + 1, (RESOLUTION_800_TO_HD_WIDTH - (RESOLUTION_800_TO_HD_WIDTH % 4)), FALSE, 0 }, // Doesn't work
    { D2DLL_D2GDI, 0x6D42 + 1, RESOLUTION_800_TO_HD_HEIGHT, FALSE, 0 }, // Doesn't work
    { D2DLL_D2GDI, 0x6D3D + 1, (RESOLUTION_1344_TO_HD_WIDTH - (RESOLUTION_1344_TO_HD_WIDTH % 4)), FALSE, 0 },
    { D2DLL_D2GDI, 0x6D42 + 1, RESOLUTION_1344_TO_HD_HEIGHT, FALSE, 0 },

    // Other Patches, Unsure what they do
    { D2DLL_D2GDI, 0x62C7 + 2 + 4, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GDI, 0x62B1 + 2 + 4, RESOLUTION_800_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GDI, 0x62BC + 2 + 4, RESOLUTION_1344_TO_HD_WIDTH, FALSE, 0 },

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

    // Replace for HD, Correct Resizing of Window from HD back to 800 mode.
    { D2DLL_D2GFX, 0x83F0 + 1, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GFX, 0x8403 + 2, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },
    { D2DLL_D2GFX, 0x8747 + 1, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GFX, 0x8750 + 1, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GFX, 0x8759 + 1, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },
    { D2DLL_D2GFX, 0x8762 + 1, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },
    { D2DLL_D2GFX, 0x876B + 1, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GFX, 0x8797 + 3 + 4, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GFX, 0x87A2 + 3 + 4, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },

    // Replace for HD, Resize Foreground Rendering Width
    { D2DLL_D2GDI, 0x706B + 2 + 4, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GDI, 0x7051 + 2 + 4, RESOLUTION_800_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2GDI, 0x705E + 2 + 4, RESOLUTION_1344_TO_HD_WIDTH, FALSE, 0 },

    // Replace for HD, Resize Game Logic Resolution and FOV
    { D2DLL_D2CLIENT, 0x10E29 + 1, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x10E33 + 2 + 4, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x10E09 + 1, RESOLUTION_800_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_D2CLIENT, 0x10E13 + 2 + 4, RESOLUTION_800_TO_HD_HEIGHT, FALSE, 0 },
    // { D2DLL_D2CLIENT, UKNOWN + 1, RESOLUTION_1344_TO_HD_WIDTH, FALSE, 0 },
    // { D2DLL_D2CLIENT, UKNOWN + 2 + 4, RESOLUTION_1344_TO_HD_HEIGHT, FALSE, 0 },

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
    { D2DLL_D2GLIDE, 0xDCC6, PATCH_NOPBLOCK, FALSE, 70 },
    { D2DLL_D2GLIDE, 0xDCC6, PATCH_CALL, FALSE, 0 },
    { D2DLL_D2GLIDE, 0xDCC6 + 1, (int)HD::SetupGlideRenderResolution_Interception, TRUE, 0 },

    { D2DLL_INVALID } // this must be the last entry in the array!
};

// Fixes border panel click detection issue for HD mode. Shouldn't need to be disabled.
static const DLLPatchStrc borderPanelClickDetectionPatches[] = {
    // Left panel click block
    { D2DLL_D2CLIENT, 0xBCB30 + 1, (int)HD::GetResolutionMode_Interception, TRUE, 0 },

    // Right panel click block
    { D2DLL_D2CLIENT, 0x8F880 + 1, (int)HD::GetResolutionMode_Interception, TRUE, 0 },

    { D2DLL_INVALID }
};

// Replace for HD, Resize Glide Game Window, but not used if using custom glide3x.dll
static const DLLPatchStrc glide3xPatches[] = {
    { D2DLL_GLIDE3X, 0xCADB + 2, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_GLIDE3X, 0xCAE7 + 2, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },
    { D2DLL_GLIDE3X, 0xCAF7 + 2, RESOLUTION_800_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_GLIDE3X, 0xCB03 + 2, RESOLUTION_800_TO_HD_HEIGHT, FALSE, 0 },
    
    { D2DLL_INVALID }
};

static const DLLPatchStrc levelButtonClickDetectionPatches[] = {
    // Unknown
    { D2DLL_D2CLIENT, 0x506AF + 1, (int)HD::GetResolutionMode_Interception, TRUE, 0 },

    // Skill button animation click detection
    { D2DLL_D2CLIENT, 0x506C9 + 1, (int)HD::GetResolutionMode_Interception, TRUE, 0 },

    // Unknown
    { D2DLL_D2CLIENT, 0x5075F + 1, (int)HD::GetResolutionMode_Interception, TRUE, 0 },

    // Stat button animation click detection
    { D2DLL_D2CLIENT, 0x5077D + 1, (int)HD::GetResolutionMode_Interception, TRUE, 0 },

    // Unknown
    { D2DLL_D2CLIENT, 0x50810 + 1, (int)HD::GetResolutionMode_Interception, TRUE, 0 },

    // Skill button click detection
    { D2DLL_D2CLIENT, 0x5082E + 1, (int)HD::GetResolutionMode_Interception, TRUE, 0 },

    // Unknown
    { D2DLL_D2CLIENT, 0x50B70 + 1, (int)HD::GetResolutionMode_Interception, TRUE, 0 },

    // Stat button click detection
    { D2DLL_D2CLIENT, 0x50B8E + 1, (int)HD::GetResolutionMode_Interception, TRUE, 0 },

    { D2DLL_INVALID }
};

static const DLLPatchStrc moviePatches[] = {
    { D2DLL_SMACKW32, 0x3DFF + 4, RESOLUTION_640_TO_HD_WIDTH, FALSE, 0 },
    { D2DLL_SMACKW32, 0x3E07 + 4, RESOLUTION_640_TO_HD_HEIGHT, FALSE, 0 },

    { D2DLL_INVALID }
};

// end of file --------------------------------------------------------------
#endif