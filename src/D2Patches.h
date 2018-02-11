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
        0x8BA5F, 0x86BCF, 0, 0, 0, 0x865C4,
        0x81B8F, 0xA3606, 0x66A06, 0x90166, 0xC39F6, 0x1D3F6,
        0x65DDB, 0x5259B, 0x5259B, 0x56EFD
    }), PATCH_NOPBLOCK, false, 0xC3A1D - 0xC39F6),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0x8BA5F, 0x86BCF, 0, 0, 0, 0x865C4,
        0x81B8F, 0xA3606, 0x66A06, 0x90166, 0xC39F6, 0x1D3F6,
        0x65DDB, 0x5259B, 0x5259B, 0x56EFD
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0x8BA5F + 1, 0x86BCF + 1, 0, 0, 0, 0x865C4 + 1,
        0x81B8F + 1, 0xA3606 + 1, 0x66A06 + 1, 0x90166 + 1, 0xC39F6 + 1, 0x1D3F6 + 1,
        0x65DDB + 1, 0x5259B + 1, 0x5259B + 1, 0x56EFD + 1
    }), (DWORD) D2HD::repositionPanelsInterception, true, 0),

    // Fix border panel click detection issue for HD mode.
    // Left panel click block
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x6AF10 + 1, 0xBCB30 + 1, 0xBF2D0 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Right panel click block
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0xA7040 + 1, 0x8F880 + 1, 0x94820 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Resize Game Logic Resolution and FOV
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x1263D, 0x10DFD, 0x2C22D,
        0, 0, 0, 0x4BA30
    }), PATCH_NOPBLOCK, false, 0x10E49 - 0x10DFD),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x1263D, 0x10DFD, 0x2C22D,
        0, 0, 0, 0x4BA30
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x1263D + 1, 0x10DFD + 1, 0x2C22D + 1,
        0, 0, 0, 0x4BA30 + 1
    }), (DWORD) D2HD::resizeGameLogicResolutionInterception, true, 0),

    // Read From D2HD.ini Instead of Registry
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x7CC34, 0x44454, 0x454A4,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x44464 - 0x44454),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x7CC34, 0x44454, 0x454A4,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x7CC34 + 1, 0x44454 + 1, 0x454A4 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getConfigResolutionInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x55CF7, 0x65E47, 0xC40E7,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x662BC - 0x662AB),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x55CF7, 0x65E47, 0xC40E7,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x55CF7 + 1, 0x65E47 + 1, 0xC40E7 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getConfigResolutionInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x56129, 0x66279, 0xC4519,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x6628A - 0x66279),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x56129, 0x66279, 0xC4519,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x56129 + 1, 0x66279 + 1, 0xC4519 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getConfigResolutionInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x67EC1, 0xAF951, 0x85F61,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x6628A - 0x66279),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x67EC1, 0xAF951, 0x85F61,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x67EC1 + 1, 0xAF951 + 1, 0x85F61 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getConfigResolutionInterception, true, 0),

    // Interpret Config Resolution Mode and Remove Limit on Config Resolution Mode
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x7CC4A, 0x4446A, 0x454BA,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x44472 - 0x4446A),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x7CC4A, 0x4446A, 0x454BA,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x7CC4A + 1, 0x4446A + 1, 0x454BA + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::setResolutionModeEAXInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x55D0E, 0x65E5E, 0xC40FE,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x44472 - 0x4446A),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x55D0E, 0x65E5E, 0xC40FE,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x55D0E + 1, 0x65E5E + 1, 0xC40FE + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::setResolutionModeEAXInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x5613E, 0x6628E, 0xC452E,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x44472 - 0x4446A),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x5613E, 0x6628E, 0xC452E,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x5613E + 1, 0x6628E + 1, 0xC452E + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::setResolutionModeEDIInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x67ED8, 0xAF968, 0x85F78,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x44472 - 0x4446A),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x67ED8, 0xAF968, 0x85F78,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x67ED8 + 1, 0xAF968 + 1, 0x85F78 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::setResolutionModeEAXInterception, true, 0),

    // Write to D2HD.ini Instead of Registry
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x5615B, 0x662AB, 0xC454B,
        0, 0, 0, 0x7D0AA
    }), PATCH_NOPBLOCK, false, 0x662BC - 0x662AB),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x5615B, 0x662AB, 0xC454B,
        0, 0, 0, 0x7D0AA
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x5615B + 1, 0x662AB + 1, 0xC454B + 1,
        0, 0, 0, 0x7D0AA + 1
    }), (DWORD) D2HD::setConfigResolutionInterception, true, 0),

    // Increase Number of Resolutions in Video Options
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x56174, 0x662C4, 0xC4564,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x662CC - 0x662C4),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x56174, 0x662C4, 0xC4564,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x56174 + 1, 0x662C4 + 1, 0xC4564 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::setResolutionModeEDIInterception, true, 0),

    // Modify Resolution Display in Options
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x552AF, 0x653FF, 0xC369F,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 7),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x552AF, 0x653FF, 0xC369F,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x552AF + 1, 0x653FF + 1, 0xC369F + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::Draw::determineVideoOptionTextInterception, true, 0),

    // Modify the value of the registry resolution ID
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x54DA0, 0x651E0, 0xC33A0,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x651EA - 0x651E0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x54DA0, 0x651E0, 0xC33A0,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x54DA0 + 1, 0x651E0 + 1, 0xC33A0 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::setResolutionModeFromMenuInterception, true, 0),

    // Resize Game Window; D2GFX.Ordinal10025, D2GFX.Ordinal10064
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0x4B60, 0, 0, 0, 0, 0,
        0, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH
    }), PATCH_NOPBLOCK, false, 0x4B98 - 0x4B60),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0x4B60, 0, 0, 0, 0, 0,
        0, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0x4B60 + 1, 0, 0, 0, 0, 0,
        0, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH
    }), (DWORD) D2HD::getModeParamsInterception107, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, 0x8110, 0x80F0, 0x8590, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH
    }), PATCH_NOPBLOCK, false, 0x8143 - 0x8110),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, 0x8110, 0x80F0, 0x8590, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH
    }), PATCH_JMP, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, 0x8110 + 1, 0x80F0 + 1, 0x8590 + 1, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH
    }), (DWORD) D2HD::getModeParamsInterception111, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, 0x7FD0, 0xB0E0,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH
    }), PATCH_NOPBLOCK, false, 0x8022 - 0x7FD0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, 0x7FD0, 0xB0E0,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH
    }), PATCH_JMP, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, 0x7FD0 + 1, 0xB0E0 + 1,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH
    }), (DWORD) D2HD::getModeParams, true, 0),

    // Correct Resizing of Window from any resolution to a smaller one.
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, D2Patch::NO_PATCH, 0x83F0, 0xB42F,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x83F5 - 0x83F0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, D2Patch::NO_PATCH, 0x83F0, 0xB42F,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, D2Patch::NO_PATCH, 0x83F0 + 1, 0xB42F + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::resizeGameWindowResizeWidthInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, D2Patch::NO_PATCH, 0x8403, 0xB43E,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x8409 - 0x8403),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, D2Patch::NO_PATCH, 0x8403, 0xB43E,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, D2Patch::NO_PATCH, 0x8403 + 1, 0xB43E + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::resizeGameWindowResizeHeightInterception, true, 0),

    // Resize GDI Rendering Resolution
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x6284, 0x6D34, 0x7B84,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x6D5F - 0x6D34),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x6284, 0x6D34, 0x7B84,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x6284 + 1, 0x6D34 + 1, 0x7B84 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::setGDIRenderResolutionInterception, true, 0),

    // Resize Foreground Rendering Width
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x6599, 0x7049, 0x7E99,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x706A - 0x7049),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x65BB, 0x706B, 0x7EBB,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x7075 - 0x706B),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x6599, 0x7049, 0x7E99,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x6599 + 1, 0x7049 + 1, 0x7E99 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::setGDIForegroundRenderWidthInterception, true, 0),

    // Fix D2DDraw Fullscreen
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2DDRAW, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x8CE2, 0x85C2, 0x8202,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x85ED - 0x85C2),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2DDRAW, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x8CE2, 0x85C2, 0x8202,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2DDRAW, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x8CE2 + 1, 0x85C2 + 1, 0x8202 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::setDirectDrawRenderResolutionInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2DDRAW, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x8D19, 0x85F9, 0x8239,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x8600 - 0x85F9),

    // Fix Direct3D Fullscreen
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2DIRECT3D, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0xFCD4, 0xB9A4, 0xBE64,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, /*0xB9D0*/ 0xB9DF - 0xB9A4),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2DIRECT3D, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0xFCD4, 0xB9A4, 0xBE64,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2DIRECT3D, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0xFCD4 + 1, 0xB9A4 + 1, 0xBE64 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::setDirect3DRenderResolutionInterception, true, 0),

    // Resize Glide Rendering Resolution
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GLIDE, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0xBD26, 0xDCC6, 0xD5D6,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0xDD26 - 0xDCC6),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GLIDE, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0xBD26, 0xDCC6, 0xD5D6,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GLIDE, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0xBD26 + 1, 0xDCC6 + 1, 0xD5D6 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::setGlideRenderResolutionInterception, true, 0),
};

static const std::vector<D2Patch> requiredDrawPatches = {
    // Disable Blizzard's UI Panel Borders
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x82160, 0x271C0, 0x6D2B0,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x271C6 - 0x271C0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x8216B, 0x271CB, 0x6D2BB,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x2728A - 0x271CA),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x82070, 0x270D0, 0x6D1C0,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x271B1 - 0x270D0),

    // Draw background and Redraw UI Panel Border Fix
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x8C031, 0xBF361, 0x190B1,
        0, 0, 0, 0
    }), PATCH_JMP, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x8C031 + 1, 0xBF361 + 1, 0x190B1 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::Draw::drawPanelBackgroundInterception, true, 0),

    // Draw bottom control panel background
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x82237, 0x27297, 0x6D387,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x82237 + 1, 0x27297 + 1, 0x6D387 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::Draw::drawControlPanelBackgroundInterception, true, 0),

    // Draw bottom control panel foreground
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x823C2, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 0x824B3 - 0x823C2),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x823C2, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x823C2 + 1, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH, D2Patch::NO_PATCH
    }), (DWORD) D2HD::Draw::drawControlPanel800ForegroundInterception, true, 0),

    // Unload additional resources when game exits
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x8141C, 0x26E1C, 0x6CF0C,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 6),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x8141C, 0x26E1C, 0x6CF0C,
        0, 0, 0, 0
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x8141C + 1, 0x26E1C + 1, 0x6CF0C + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::Draw::unloadCellFilesInterception, true, 0)
};

static const std::vector<D2Patch> controlPanel800Patches = {
    // Mouse over skill button detection patch ; Additional Pre-1.13c Patch
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3BED0, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) PATCH_JMP, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3BED0 + 1, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) D2HD::isMouseOverSkillButtonInterception, true, 0),

    // Mouse over stats button detection patch; Additional Pre-1.13c Patch
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3BF10, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) PATCH_JMP, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3BF10 + 1, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) D2HD::isMouseOverStatsButtonInterception, true, 0),

    // Unknown
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C59F + 1, 0x506AF + 1, 0x211DF + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Skill button animation click detection; Additional Pre-1.13c Patch
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C622, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) PATCH_NOPBLOCK, false, 0x3C64E - 0x3C622),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C622, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C622 + 1, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) D2HD::isMouseOverSkillButtonInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C627, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) PATCH_JMP, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C627 + 1, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) D2CLIENT_ClickSkillButton, true, 0),

    // Skill button animation click detection
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C5BD + 1, 0x506C9 + 1, 0x211F9 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Unknown
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C66F + 1, 0x5075F + 1, 0x2128F + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Stats button animation click detection; Additional Pre-1.13c Patch
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C6FD, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) PATCH_NOPBLOCK, false, 0x3C72D - 0x3C6FD),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C6FD, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C6FD + 1, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) D2HD::isMouseOverStatsButtonInterception, true, 0),

    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C702, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) PATCH_JMP, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C702 + 1, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) D2CLIENT_ClickStatsButton, true, 0),

    // Stat button animation click detection
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C68D + 1, 0x5077D + 1, 0x212AD + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Unknown
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C780 + 1, 0x50810 + 1, 0x21340 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Skill button click detection
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C79E + 1, 0x5082E + 1, 0x2135E + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Unknown
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3CAE0 + 1, 0x50B70 + 1, 0x216A0 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Stat button click detection
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3CAFE + 1, 0x50B8E + 1, 0x216BE + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Control panel to 800 control panel.
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x82242 + 1, 0x272A2 + 1, 0x6D392 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Stats button position fix; Additional Pre-1.13c Patch
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C4BC, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) PATCH_NOPBLOCK, false, 0x3C4D4 - 0x3C4BC),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C4BC, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C4BC + 1, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) D2HD::Draw::drawStatsButtonInterception, true, 0),

    // Stats button fix (greyed out)
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C4E3 + 1, 0x50103 + 1, 0x21093 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Stats level up button fix
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C2B7 + 1, 0x50447 + 1, 0x20E67 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C35C + 1, 0x504EC + 1, 0x20F0C + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C3D3 + 1, 0x50563 + 1, 0x20F83 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C438 + 1, 0x505C8 + 1, 0x20FE8 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Skill button position fix; Additional Pre-1.13c Patch
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C279, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) PATCH_NOPBLOCK, false, 0x3C297 - 0x3C279),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C279, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C279 + 1, D2Patch::NO_PATCH, D2Patch::NO_PATCH,
        0, 0, 0, 0
    }), (DWORD) D2HD::Draw::drawSkillButtonInterception, true, 0),

    // Skill button fix (greyed out)
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C1F3 + 1, 0x50023 + 1, 0x20DA3 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),

    // Skill level up button fix
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3BFC7 + 1, 0x50207 + 1, 0x20B77 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C065 + 1, 0x502A5 + 1, 0x20C15 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C0DC + 1, 0x5031C + 1, 0x20C8C + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x3C140 + 1, 0x50380 + 1, 0x20CF0 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::getPatchedResolutionModeInterception, true, 0)
};

// Patches inventory positions to be in the correct location. Credits to D2Ex.
static const std::vector<D2Patch> inventoryPatches = {
    // D2Common.Ordinal10333
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x4BB10, 0x13340, 0x70780,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 7),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x4BB10, 0x13340, 0x70780,
        0, 0, 0, 0
    }), PATCH_JMP, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x4BB10 + 1, 0x13340 + 1, 0x70780 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::Inventory::getBeltPos, true, 0),

    // D2Common.Ordinal10991
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x4BA30, 0x132A0, 0x706A0,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 10),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x4BA30, 0x132A0, 0x706A0,
        0, 0, 0, 0
    }), PATCH_JMP, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x4BA30 + 1, 0x132A0 + 1, 0x706A0 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::Inventory::getBeltsTxtRecord, true, 0),

    // D2Common.Ordinal11012
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x1B100, 0x82030, 0x6BFB0,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 8),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x1B100, 0x82030, 0x6BFB0,
        0, 0, 0, 0
    }), PATCH_JMP, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x1B100 + 1, 0x82030 + 1, 0x6BFB0 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::Inventory::getInventorySize, true, 0),

    // D2Common.Ordinal10760
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x1B080, 0x81FB0, 0x6BF30,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 8),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x1B080, 0x81FB0, 0x6BF30,
        0, 0, 0, 0
    }), PATCH_JMP, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x1B080 + 1, 0x81FB0 + 1, 0x6BF30 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::Inventory::getInventoryGrid, true, 0),

    // D2Common.Ordinal10701
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x1AFF0, 0x81F20, 0x6BEA0,
        0, 0, 0, 0
    }), PATCH_NOPBLOCK, false, 8),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x1AFF0, 0x81F20, 0x6BEA0,
        0, 0, 0, 0
    }), PATCH_JMP, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0x1AFF0 + 1, 0x81F20 + 1, 0x6BEA0 + 1,
        0, 0, 0, 0
    }), (DWORD) D2HD::Inventory::getInventoryField, true, 0)
};

// Replace for HD, Resize Glide Game Window, but not used if using custom glide3x.dll
static const std::vector<D2Patch> glide3xPatches = {
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_GLIDE3X, {
        0xCA97, 0xCA97, 0xCA97, 0xCA97, 0xCA97, 0xCA97,
        0xCA97, 0xCA97, 0xCA97, 0xCA97, 0xCA97, 0xCA97,
        0xCA97, 0xCA97, 0xCA97, 0xCA97
    }), PATCH_NOPBLOCK, false, 0xCBA7 - 0xCA97),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_GLIDE3X, {
        0xCA97, 0xCA97, 0xCA97, 0xCA97, 0xCA97, 0xCA97,
        0xCA97, 0xCA97, 0xCA97, 0xCA97, 0xCA97, 0xCA97,
        0xCA97, 0xCA97, 0xCA97, 0xCA97
    }), PATCH_CALL, false, 0),
    D2Patch(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_GLIDE3X, {
        0xCA97 + 1, 0xCA97 + 1, 0xCA97 + 1, 0xCA97 + 1, 0xCA97 + 1, 0xCA97 + 1,
        0xCA97 + 1, 0xCA97 + 1, 0xCA97 + 1, 0xCA97 + 1, 0xCA97 + 1, 0xCA97 + 1,
        0xCA97 + 1, 0xCA97 + 1, 0xCA97 + 1, 0xCA97 + 1
    }), (DWORD) D2HD::setupGlideWindowSizeInterception, true, 0)
};

// end of file --------------------------------------------------------------
#endif
