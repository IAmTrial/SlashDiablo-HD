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

#include <limits>
#include <vector>
#include "D2PatchConst.h"
#include "DLLmain.h"

// Required patches to enable new resolutions and prevent buggy behavior and
// crashes.
static const std::vector<D2Patch> requiredHDPatches = {
    // Panel Positioning Fix
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC39F6, 0x1D3F6
    }), PATCH_NOPBLOCK, false, 39),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC39F6, 0x1D3F6
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC39F6 + 1, 0x1D3F6 + 1
    }), (DWORD) D2HD::repositionPanelsInterception, true, 0),

    // Fix border panel click detection issue for HD mode.
    // Left panel click block
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xBCB30 + 1, 0xBF2D0 + 1
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Right panel click block
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x8F880 + 1, 0x94820 + 1
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Resize Game Logic Resolution and FOV
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x10DFD, 0x2C22D
    }), PATCH_NOPBLOCK, false, 0x10E49 - 0x10DFD),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x10DFD, 0x2C22D
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x10DFD + 1, 0x2C22D + 1
    }), (DWORD) D2HD::resizeGameLogicResolutionInterception, true, 0),

    // Read From D2HD.ini Instead of Registry
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x44454, 0x454A4
    }), PATCH_NOPBLOCK, false, 0x44464 - 0x44454),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x44454, 0x454A4
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x44454 + 1, 0x454A4 + 1
    }), (DWORD) D2HD::Config::getConfigResolutionInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x65E47, 0xC40E7
    }), PATCH_NOPBLOCK, false, 0x662BC - 0x662AB),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x65E47, 0xC40E7
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x65E47 + 1, 0xC40E7 + 1
    }), (DWORD) D2HD::Config::getConfigResolutionInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x66279, 0xC4519
    }), PATCH_NOPBLOCK, false, 0x6628A - 0x66279),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x66279, 0xC4519
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x66279 + 1, 0xC4519 + 1
    }), (DWORD) D2HD::Config::getConfigResolutionInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xAF951, 0x85F61
    }), PATCH_NOPBLOCK, false, 0x6628A - 0x66279),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xAF951, 0x85F61
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xAF951 + 1, 0x85F61 + 1
    }), (DWORD) D2HD::Config::getConfigResolutionInterception, true, 0),

    // Interpret Config Resolution Mode and Remove Limit on Config Resolution Mode
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x4446A, 0x454BA
    }), PATCH_NOPBLOCK, false, 0x44472 - 0x4446A),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x4446A, 0x454BA
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x4446A + 1, 0x454BA + 1
    }), (DWORD) D2HD::setResolutionModeEAXInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x65E5E, 0xC40FE
    }), PATCH_NOPBLOCK, false, 0x44472 - 0x4446A),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x65E5E, 0xC40FE
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x65E5E + 1, 0xC40FE + 1
    }), (DWORD) D2HD::setResolutionModeEAXInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x6628E, 0xC452E
    }), PATCH_NOPBLOCK, false, 0x44472 - 0x4446A),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x6628E, 0xC452E
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x6628E + 1, 0xC452E + 1
    }), (DWORD) D2HD::setResolutionModeEDIInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xAF968, 0x85F78
    }), PATCH_NOPBLOCK, false, 0x44472 - 0x4446A),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xAF968, 0x85F78
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xAF968 + 1, 0x85F78 + 1
    }), (DWORD) D2HD::setResolutionModeEAXInterception, true, 0),

    // Write to D2HD.ini Instead of Registry
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x662AB, 0xC454B
    }), PATCH_NOPBLOCK, false, 0x662BC - 0x662AB),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x662AB, 0xC454B
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x662AB + 1, 0xC454B + 1
    }), (DWORD) D2HD::Config::setConfigResolutionInterception, true, 0),

    // Increase Number of Resolutions in Video Options
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x662C4, 0xC4564
    }), PATCH_NOPBLOCK, false, 0x662BC - 0x662AA),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x662C4, 0xC4564
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x662C4 + 1, 0xC4564 + 1
    }), (DWORD) D2HD::setResolutionModeEDIInterception, true, 0),

    // Modify Resolution Display in Options
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x653FF, 0xC369F
    }), PATCH_NOPBLOCK, false, 7),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x653FF, 0xC369F
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x653FF + 1, 0xC369F + 1
    }), (DWORD) /*D2HD::STUB_DetermineText*/0, true, 0),

    // Modify the value of the registry resolution ID
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x651E0, 0xC33A0
    }), PATCH_NOPBLOCK, false, 0x651EA - 0x651E0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x651E0, 0xC33A0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x651E0 + 1, 0xC33A0 + 1
    }), (DWORD) D2HD::setResolutionModeFromMenuInterception, true, 0),

    // Resize GDI Rendering Resolution
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x6D34, 0x7B84
    }), PATCH_NOPBLOCK, false, 0x6D5F - 0x6D34),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x6D34, 0x7B84
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x6D34 + 1, 0x7B84 + 1
    }), (DWORD) D2HD::setGDIRenderResolutionInterception, true, 0),


    // Resize Foreground Rendering Width
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7049, 0x7E99
    }), PATCH_NOPBLOCK, false, 0x706A - 0x7049),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x706B, 0x7EBB
    }), PATCH_NOPBLOCK, false, 0x7075 - 0x706B),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7049, 0x7E99
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7049 + 1, 0x7E99 + 1
    }), (DWORD) D2HD::setGDIForegroundRenderWidthInterception, true, 0),

    // Resize Game Window; D2GFX.Ordinal10025, D2GFX.Ordinal10064
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7FD0, 0xB0E0
    }), PATCH_NOPBLOCK, false, 0x8022 - 0x7FD0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7FD0, 0xB0E0
    }), PATCH_JMP, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7FD0 + 1, 0xB0E0 + 1
    }), (DWORD) D2HD::getModeParams, true, 0),

    // Correct Resizing of Window from any resolution to a smaller one.
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x83F0 + 1, 0xB42F + 1
    }), std::numeric_limits<int>::max(), false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x8403 + 2, 0xB43E + 2
    }), std::numeric_limits<int>::max(), false, 0),
};

// end of file --------------------------------------------------------------
#endif
