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
	{ D2DLL_D2CLIENT, 0xC39F6, 0, PATCH_CALL, FALSE },
	{ D2DLL_D2CLIENT, 0xC39F7, 38, (int)HD::PanelPosition_Interception, TRUE },

	// Enable Panel Borders Fix
	{ D2DLL_D2CLIENT, 0x29262, 0, PATCH_CALL, FALSE },
	{ D2DLL_D2CLIENT, 0x29263, 4, (int)HD::EnableUIPanelBorders_Interception, TRUE },

	// Redraw UI Panel Border Fix
	{ D2DLL_D2CLIENT, 0x271ED, 0, PATCH_CALL, FALSE },
	{ D2DLL_D2CLIENT, 0x271EE, 153, (int)HD::RedrawUILeftPanelBorders_Interception, TRUE },
	{ D2DLL_D2CLIENT, 0x270F2, 0, PATCH_CALL, FALSE },
	{ D2DLL_D2CLIENT, 0x270F3, 186, (int)HD::RedrawUIRightPanelBorders_Interception, TRUE },

    {D2DLL_INVALID} // this must be the last entry in the array!
};

// end of file --------------------------------------------------------------
#endif