/*****************************************************************************
 *                                                                           *
 *   D2Patches.h                                                             *
 *   Copyright (C) Olivier Verville                                          *
 *   SlashDiablo-Tools Modifications: Copyright (C) 2017 Mir Drualga         *
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

#ifndef _D2PATCHES_H
#define _D2PATCHES_H

#include <vector>
#include "D2PatchConst.h"
#include "DLLmain.h"

static const std::vector<D2Patch> generalHDPatches = {
        // Panel Positioning Fix
        D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0xC39F6, 0x1D3F6 }), PATCH_NOPBLOCK, false, 39),
        D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0xC39F6, 0x1D3F6 }), PATCH_CALL, false, 0),
        D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0xC39F6 + 1, 0x1D3F6 + 1 }),
                (DWORD) D2HD::repositionPanelsInterception, true, 0),

        // Fix border panel click detection issue for HD mode.
        // Left panel click block
        D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0xBCB30 + 1, 0xBF2D0 + 1 }),
                (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

        // Right panel click block
        D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0x8F880 + 1, 0x94820 + 1 }),
                (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0) };

// end of file --------------------------------------------------------------
#endif
