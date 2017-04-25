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
	{ D2DLL_D2CLIENT, 0x29262 + 1, (int)HD::EnableUIPanelBorders_Interception, TRUE, 0 },

	// Redraw UI Panel Border Fix
	{ D2DLL_D2CLIENT, 0x271ED, PATCH_NOPBLOCK, FALSE, 154 },
	{ D2DLL_D2CLIENT, 0x271ED, PATCH_CALL, FALSE, 0 },
	{ D2DLL_D2CLIENT, 0x271ED + 1, (int)HD::RedrawUILeftPanelBorders_Interception, TRUE, 0 },
	{ D2DLL_D2CLIENT, 0x270F2, PATCH_NOPBLOCK, FALSE, 187 },
	{ D2DLL_D2CLIENT, 0x270F2, PATCH_CALL, FALSE, 0 },
	{ D2DLL_D2CLIENT, 0x270F2 + 1, (int)HD::RedrawUIRightPanelBorders_Interception, TRUE, 0 },

	// Replace 640 with HD, Resize Game Window
	{ D2DLL_D2GFX, 0x7FE8, PATCH_NOPBLOCK, FALSE, 12 },
	{ D2DLL_D2GFX, 0x7FE8, PATCH_CALL, FALSE, 0 },
	{ D2DLL_D2GFX, 0x7FE8 + 1, (int)HD::Replace640_ResizeWindow_Interception, TRUE, 0 },

	// Replace 640 with HD, Resize Rendering Resolution
	{ D2DLL_D2GDI, 0x6D55, PATCH_NOPBLOCK, FALSE, 10 },
	{ D2DLL_D2GDI, 0x6D55, PATCH_CALL, FALSE, 0 },
	{ D2DLL_D2GDI, 0x6D55 + 1, (int)HD::Replace640_ResizeRenderResolution_Interception, TRUE, 0 },

	// Replace 640 with HD, Resize Foreground Rendering Width
	{ D2DLL_D2GDI, 0x706B, PATCH_NOPBLOCK, FALSE, 10 },
	{ D2DLL_D2GDI, 0x706B, PATCH_CALL, FALSE, 0 },
	{ D2DLL_D2GDI, 0x706B + 1, (int)HD::Replace640_ResizeForgroundRenderWidth_Interception, TRUE, 0 },

	// Replace 640 with HD, Resize Game Logic Resolution and FOV
	{ D2DLL_D2CLIENT, 0x10E29, PATCH_NOPBLOCK, FALSE, 20 },
	{ D2DLL_D2CLIENT, 0x10E29, PATCH_CALL, FALSE, 0 },
	{ D2DLL_D2CLIENT, 0x10E29 + 1, (int)HD::Replace640_ResizeGameLogicResolution_Interception, TRUE, 0 },

	// Replace 640 with HD, Resize Glide Render Logic Resolution
	{ D2DLL_D2GLIDE, 0xDCD5, PATCH_NOPBLOCK, FALSE, 20 },
	{ D2DLL_D2GLIDE, 0xDCD5, PATCH_CALL, FALSE, 0 },
	{ D2DLL_D2GLIDE, 0xDCD5 + 1, (int)HD::Replace640_ResizeGlideRenderResolution_Interception, TRUE, 0 },

	// Replace 640 with HD, Resize Glide Game Window
	{ D2DLL_GLIDE3X, 0xCAD5, PATCH_NOPBLOCK, FALSE, 24 },
	{ D2DLL_GLIDE3X, 0xCAD5, PATCH_CALL, FALSE, 0 },
	{ D2DLL_GLIDE3X, 0xCAD5 + 1, (int)HD::Replace640_ResizeGlideWindow_Interception, TRUE, 0 },
	

    {D2DLL_INVALID} // this must be the last entry in the array!
};

// end of file --------------------------------------------------------------
#endif