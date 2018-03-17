/*****************************************************************************
 *                                                                           *
 *  SlashDiablo HD                                                           *
 *  Copyright (C) 2017  Mir Drualga                                          *
 *                                                                           *
 *  This program is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU Affero General Public License as published *
 *  by the Free Software Foundation, either version 3 of the License, or     *
 *  (at your option) any later version.                                      *
 *                                                                           *
 *  This program is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU Affero General Public License for more details.                      *
 *                                                                           *
 *  You should have received a copy of the GNU Affero General Public License *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
 *                                                                           *
 *****************************************************************************/

/*****************************************************************************
 *                                                                           *
 *   D2Patches.h                                                             *
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

#pragma once

#ifndef _D2PATCHES_H
#define _D2PATCHES_H

#include <limits>
#include <memory>
#include <vector>

#include "D2Patch.h"
#include "DLLmain.h"

// Required patches to enable new resolutions and prevent buggy behavior and
// crashes.
static const std::vector<std::shared_ptr<D2BasePatch>> requiredHDPatches = {
    // Fix panel positioning
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_107, 0x8BA5F },
        { GameVersion::VERSION_108, 0x86BCF },
        { GameVersion::VERSION_109, 0 },
        { GameVersion::VERSION_109b, 0 },
        { GameVersion::VERSION_109c, 0 },
        { GameVersion::VERSION_109d, 0x865C4 },
        { GameVersion::VERSION_110, 0x81B8F },
        { GameVersion::VERSION_111, 0xA3606 },
        { GameVersion::VERSION_111b, 0x66A06 },
        { GameVersion::VERSION_112, 0x90166 },
        { GameVersion::VERSION_113c, 0xC39F6 },
        { GameVersion::VERSION_113d, 0x1D3F6 },
        { GameVersion::VERSION_114a, 0x65DDB },
        { GameVersion::VERSION_114b, 0x5259B },
        { GameVersion::VERSION_114c, 0x5259B },
        { GameVersion::VERSION_114d, 0x56EFD }
    }), OpCode::CALL, (void*) D2HD::repositionPanelsInterception, 0xC3A1D - 0xC39F6),

    // Fix border panel click detection issue for HD mode.
    // Block click for left panel
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x6AF10 },
        { GameVersion::VERSION_113c, 0xBCB30 },
        { GameVersion::VERSION_113d, 0xBF2D0 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // Block click for right panel
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0xA7040 },
        { GameVersion::VERSION_113c, 0x8F880 },
        { GameVersion::VERSION_113d, 0x94820 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // Resize Game Logic Resolution and FOV
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x1263D },
        { GameVersion::VERSION_113c, 0x10DFD },
        { GameVersion::VERSION_113d, 0x2C22D },
        { GameVersion::VERSION_114d, 0x4BA30 }
    }), OpCode::CALL, (void*) D2HD::resizeGameLogicResolutionInterception, 0x10E49 - 0x10DFD),

    // Read From D2HD.ini Instead of Registry
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x7CC34 },
        { GameVersion::VERSION_113c, 0x44454 },
        { GameVersion::VERSION_113d, 0x454A4 }
    }), OpCode::CALL, (void*) D2HD::getConfigResolutionInterception, 0x44464 - 0x44454),

    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x55CF7 },
        { GameVersion::VERSION_113c, 0x65E47 },
        { GameVersion::VERSION_113d, 0xC40E7 }
    }), OpCode::CALL, (void*) D2HD::getConfigResolutionInterception, 0x662BC - 0x662AB),

    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x56129 },
        { GameVersion::VERSION_113c, 0x66279 },
        { GameVersion::VERSION_113d, 0xC4519 }
    }), OpCode::CALL, (void*) D2HD::getConfigResolutionInterception, 0x6628A - 0x66279),

    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x67EC1 },
        { GameVersion::VERSION_113c, 0xAF951 },
        { GameVersion::VERSION_113d, 0x85F61 }
    }), OpCode::CALL, (void*) D2HD::getConfigResolutionInterception, 0x6628A - 0x66279),

    // Interpret Config Resolution Mode and Remove Limit on Config Resolution Mode
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x7CC4A },
        { GameVersion::VERSION_113c, 0x4446A },
        { GameVersion::VERSION_113d, 0x454BA }
    }), OpCode::CALL, (void*) D2HD::setResolutionModeEAXInterception, 0x44472 - 0x4446A),

    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x55D0E },
        { GameVersion::VERSION_113c, 0x65E5E },
        { GameVersion::VERSION_113d, 0xC40FE }
    }), OpCode::CALL, (void*) D2HD::setResolutionModeEAXInterception, 0x44472 - 0x4446A),

    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x5613E },
        { GameVersion::VERSION_113c, 0x6628E },
        { GameVersion::VERSION_113d, 0xC452E }
    }), OpCode::CALL, (void*) D2HD::setResolutionModeEDIInterception, 0x44472 - 0x4446A),

    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x67ED8 },
        { GameVersion::VERSION_113c, 0xAF968 },
        { GameVersion::VERSION_113d, 0x85F78 }
    }), OpCode::CALL, (void*) D2HD::setResolutionModeEAXInterception, 0x44472 - 0x4446A),

    // Write to D2HD.ini Instead of Registry
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x5615B },
        { GameVersion::VERSION_113c, 0x662AB },
        { GameVersion::VERSION_113d, 0xC454B },
        { GameVersion::VERSION_114d, 0x7D0AA }
    }), OpCode::CALL, (void*) D2HD::setConfigResolutionInterception, 0x662BC - 0x662AB),

    // Increase Number of Resolutions in Video Options
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x56174 },
        { GameVersion::VERSION_113c, 0x662C4 },
        { GameVersion::VERSION_113d, 0xC4564 }
    }), OpCode::CALL, (void*) D2HD::setResolutionModeEDIInterception, 0x662CC - 0x662C4),

    // Modify Resolution Display in Options
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x552AF },
        { GameVersion::VERSION_113c, 0x653FF },
        { GameVersion::VERSION_113d, 0xC369F }
    }), OpCode::CALL, (void*) D2HD::Draw::determineVideoOptionTextInterception, 7),

    // Modify the value of the registry resolution ID
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x54DA0 },
        { GameVersion::VERSION_113c, 0x651E0 },
        { GameVersion::VERSION_113d, 0xC33A0 }
    }), OpCode::CALL, (void*) D2HD::setResolutionModeFromMenuInterception, 0x651EA - 0x651E0),

    // Resize Game Window; D2GFX.Ordinal10025, D2GFX.Ordinal10064
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        { GameVersion::VERSION_107, 0x4B60 },
        { GameVersion::VERSION_108, 0x86BCF },
        { GameVersion::VERSION_109, 0 },
        { GameVersion::VERSION_109b, 0 },
        { GameVersion::VERSION_109c, 0 },
        { GameVersion::VERSION_109d, 0 },
        { GameVersion::VERSION_110, 0 },
        { GameVersion::VERSION_111, D2Patch::NO_PATCH },
        { GameVersion::VERSION_111b, D2Patch::NO_PATCH },
        { GameVersion::VERSION_112, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114a, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114b, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114d, D2Patch::NO_PATCH }
    }), OpCode::CALL, (void*) D2HD::getModeParamsInterception107, 0x4B98 - 0x4B60),

    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        { GameVersion::VERSION_107, D2Patch::NO_PATCH },
        { GameVersion::VERSION_108, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109b, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109d, D2Patch::NO_PATCH },
        { GameVersion::VERSION_110, D2Patch::NO_PATCH },
        { GameVersion::VERSION_111, 0x8110 },
        { GameVersion::VERSION_111b, 0x80F0 },
        { GameVersion::VERSION_112, 0x8590 },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114a, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114b, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114d, D2Patch::NO_PATCH }
    }), OpCode::JMP, (void*) D2HD::getModeParamsInterception111, 0x8143 - 0x8110),

    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        { GameVersion::VERSION_107, D2Patch::NO_PATCH },
        { GameVersion::VERSION_108, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109b, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109d, D2Patch::NO_PATCH },
        { GameVersion::VERSION_110, D2Patch::NO_PATCH },
        { GameVersion::VERSION_111, D2Patch::NO_PATCH },
        { GameVersion::VERSION_111b, D2Patch::NO_PATCH },
        { GameVersion::VERSION_112, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113c, 0x7FD0 },
        { GameVersion::VERSION_113d, 0xB0E0 },
        { GameVersion::VERSION_114a, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114b, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114d, D2Patch::NO_PATCH }
    }), OpCode::JMP, (void*) D2HD::getModeParams, 0x8022 - 0x7FD0),

    // Correct Resizing of Window from any resolution to a smaller one.
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        { GameVersion::VERSION_107, D2Patch::NO_PATCH },
        { GameVersion::VERSION_108, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109b, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109d, D2Patch::NO_PATCH },
        { GameVersion::VERSION_110, D2Patch::NO_PATCH },
        { GameVersion::VERSION_111, D2Patch::NO_PATCH },
        { GameVersion::VERSION_111b, D2Patch::NO_PATCH },
        { GameVersion::VERSION_112, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113c, 0x83F0 },
        { GameVersion::VERSION_113d, 0xB42F },
        { GameVersion::VERSION_114a, 0 },
        { GameVersion::VERSION_114b, 0 },
        { GameVersion::VERSION_114c, 0 },
        { GameVersion::VERSION_114d, 0 }
    }), OpCode::CALL, (void*) D2HD::resizeGameWindowResizeWidthInterception, 0x83F5 - 0x83F0),

    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, {
        { GameVersion::VERSION_107, D2Patch::NO_PATCH },
        { GameVersion::VERSION_108, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109b, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_109d, D2Patch::NO_PATCH },
        { GameVersion::VERSION_110, D2Patch::NO_PATCH },
        { GameVersion::VERSION_111, D2Patch::NO_PATCH },
        { GameVersion::VERSION_111b, D2Patch::NO_PATCH },
        { GameVersion::VERSION_112, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113c, 0x8403 },
        { GameVersion::VERSION_113d, 0xB43E },
        { GameVersion::VERSION_114a, 0 },
        { GameVersion::VERSION_114b, 0 },
        { GameVersion::VERSION_114c, 0 },
        { GameVersion::VERSION_114d, 0 }
    }), OpCode::CALL, (void*) D2HD::resizeGameWindowResizeHeightInterception, 0x8409 - 0x8403),

    // Resize GDI Rendering Resolution
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        { GameVersion::VERSION_112, 0x6284 },
        { GameVersion::VERSION_113c, 0x6D34 },
        { GameVersion::VERSION_113d, 0x7B84 }
    }), OpCode::CALL, (void*) D2HD::setGDIRenderResolutionInterception, 0x6D5F - 0x6D34),

    // Resize Foreground Rendering Width
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        { GameVersion::VERSION_112, 0x6599 },
        { GameVersion::VERSION_113c, 0x7049 },
        { GameVersion::VERSION_113d, 0x7E99 }
    }), OpCode::CALL, (void*) D2HD::setGDIForegroundRenderWidthInterception, 0x706A - 0x7049),

    std::make_shared<D2AnyPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, {
        { GameVersion::VERSION_112, 0x65BB },
        { GameVersion::VERSION_113c, 0x706B },
        { GameVersion::VERSION_113d, 0x7EBB }
    }), OpCode::NOP, false, 0x7075 - 0x706B),

    // Fix D2DDraw Fullscreen
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2DDRAW, {
        { GameVersion::VERSION_112, 0x8CE2 },
        { GameVersion::VERSION_113c, 0x85C2 },
        { GameVersion::VERSION_113d, 0x8202 }
    }), OpCode::CALL, (void*) D2HD::setDirectDrawRenderResolutionInterception, 0x85ED - 0x85C2),

    std::make_shared<D2AnyPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2DDRAW, {
        { GameVersion::VERSION_112, 0x8D19 },
        { GameVersion::VERSION_113c, 0x85F9 },
        { GameVersion::VERSION_113d, 0x8239 }
    }), OpCode::NOP, false, 0x8600 - 0x85F9),

    // Fix Direct3D Fullscreen
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2DIRECT3D, {
        { GameVersion::VERSION_112, 0xFCD4 },
        { GameVersion::VERSION_113c, 0xB9A4 },
        { GameVersion::VERSION_113d, 0xBE64 }
    }), OpCode::CALL, (void*) D2HD::setDirect3DRenderResolutionInterception, /*0xB9D0*/ 0xB9DF - 0xB9A4),

    // Resize Glide Rendering Resolution
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2GLIDE, {
        { GameVersion::VERSION_112, 0xBD26 },
        { GameVersion::VERSION_113c, 0xDCC6 },
        { GameVersion::VERSION_113d, 0xD5D6 }
    }), OpCode::CALL, (void*) D2HD::setGlideRenderResolutionInterception, 0xDD26 - 0xDCC6),
};

static const std::vector<std::shared_ptr<D2BasePatch>> requiredDrawPatches = {
    // Disable Blizzard's UI Panel Borders
    std::make_shared<D2AnyPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x82160 },
        { GameVersion::VERSION_113c, 0x271C0 },
        { GameVersion::VERSION_113d, 0x6D2B0 }
    }), OpCode::NOP, false, 0x271C6 - 0x271C0),
    std::make_shared<D2AnyPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x8216B },
        { GameVersion::VERSION_113c, 0x271CB },
        { GameVersion::VERSION_113d, 0x6D2BB }
    }), OpCode::NOP, false, 0x2728A - 0x271CA),
    std::make_shared<D2AnyPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x82070 },
        { GameVersion::VERSION_113c, 0x270D0 },
        { GameVersion::VERSION_113d, 0x6D1C0 }
    }), OpCode::NOP, false, 0x271B1 - 0x270D0),

    // Draw background and Redraw UI Panel Border Fix
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x8C031 },
        { GameVersion::VERSION_113c, 0xBF361 },
        { GameVersion::VERSION_113d, 0x190B1 }
    }), OpCode::JMP, (void*) D2HD::Draw::drawPanelBackgroundInterception, 5),

    // Draw bottom control panel background
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x82237 },
        { GameVersion::VERSION_113c, 0x27297 },
        { GameVersion::VERSION_113d, 0x6D387 }
    }), OpCode::CALL, (void*) D2HD::Draw::drawControlPanelBackgroundInterception, 5),

    // Draw bottom control panel foreground
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x823C2 },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114a, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114b, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_114d, D2Patch::NO_PATCH },
    }), OpCode::CALL, (void*) D2HD::Draw::drawControlPanel800ForegroundInterception, 0x824B3 - 0x823C2),

    // Unload additional resources when game exits
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x8141C },
        { GameVersion::VERSION_113c, 0x26E1C },
        { GameVersion::VERSION_113d, 0x6CF0C },
        { GameVersion::VERSION_114a, 0 },
        { GameVersion::VERSION_114b, 0 },
        { GameVersion::VERSION_114c, 0 },
        { GameVersion::VERSION_114d, 0 },
    }), OpCode::CALL, (void*) D2HD::Draw::unloadCellFilesInterception, 6),
};

static const std::vector<std::shared_ptr<D2BasePatch>> controlPanel800Patches = {
    // Mouse over skill button detection patch ; Additional Pre-1.13c Patch
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3BED0 },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::JMP, (void*) D2HD::isMouseOverSkillButtonInterception, 5),

    // Mouse over stats button detection patch; Additional Pre-1.13c Patch
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3BF10 },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::JMP, (void*) D2HD::isMouseOverStatsButtonInterception, 5),

    // 800 panel skill click detection
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C59F },
        { GameVersion::VERSION_113c, 0x506AF },
        { GameVersion::VERSION_113d, 0x211DF }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // Skill button animation click detection; Additional Pre-1.13c Patch
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C622 },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::CALL, (void*) D2HD::isMouseOverSkillButtonInterception, 0x3C64E - 0x3C622),

    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C627 },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::JMP, (void*) D2CLIENT_ClickSkillButton, 5),

    // Skill button animation click detection
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C5BD },
        { GameVersion::VERSION_113c, 0x506C9 },
        { GameVersion::VERSION_113d, 0x211F9 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // 800 panel active stats click detection
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C66F },
        { GameVersion::VERSION_113c, 0x5075F },
        { GameVersion::VERSION_113d, 0x2128F }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // Stats button animation click detection; Additional Pre-1.13c Patch
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C6FD },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::CALL, (void*) D2HD::isMouseOverStatsButtonInterception, 0x3C72D - 0x3C6FD),

    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C702 },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::JMP, (void*) D2CLIENT_ClickStatsButton, 5),

    // Stat button animation click detection
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C68D },
        { GameVersion::VERSION_113c, 0x5077D },
        { GameVersion::VERSION_113d, 0x212AD }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // 800 panel active skill button click detection
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C780 },
        { GameVersion::VERSION_113c, 0x50810 },
        { GameVersion::VERSION_113d, 0x21340 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // Skill button click detection
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C79E },
        { GameVersion::VERSION_113c, 0x5082E },
        { GameVersion::VERSION_113d, 0x2135E }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // Unknown
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3CAE0 },
        { GameVersion::VERSION_113c, 0x50B70 },
        { GameVersion::VERSION_113d, 0x216A0 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // Stat button click detection
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3CAFE },
        { GameVersion::VERSION_113c, 0x50B8E },
        { GameVersion::VERSION_113d, 0x216BE }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // Control panel to 800 control panel.
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x82242 },
        { GameVersion::VERSION_113c, 0x272A2 },
        { GameVersion::VERSION_113d, 0x6D392 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // Mouse over stats text position fix; Additional Pre-1.13c Patch
    // Replace active (level up) text draw code.
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C466 },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::CALL, (void*) D2HD::Draw::drawStatsButtonTextInterception, 0x3C4B7 - 0x3C466),

    // Replace inactive (greyed out) text draw code.
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C51F },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::CALL, (void*) D2HD::Draw::drawStatsButtonTextInterception, 0x3C569 - 0x3C51F),

    // Inactive stats (greyed out) button position fix; Additional Pre-1.13c Patch
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C569 },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::CALL, (void*) D2HD::Draw::drawInactiveStatsButtonInterception, 0x3C587 - 0x3C569),

    // Inactive stats (greyed out) button fix
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C4E3 },
        { GameVersion::VERSION_113c, 0x50103 },
        { GameVersion::VERSION_113d, 0x21093 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // Active stats (level up) button position fix; Additional Pre-1.13c Patch
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C4B7 },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::CALL, (void*) D2HD::Draw::drawActiveStatsButtonInterception, 0x3C4D4 - 0x3C4B7),

    // Active stats (level up) button fix
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C2B7 },
        { GameVersion::VERSION_113c, 0x50447 },
        { GameVersion::VERSION_113d, 0x20E67 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C35C },
        { GameVersion::VERSION_113c, 0x504EC },
        { GameVersion::VERSION_113d, 0x20F0C }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C3D3 },
        { GameVersion::VERSION_113c, 0x50563 },
        { GameVersion::VERSION_113d, 0x20F83 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C438 },
        { GameVersion::VERSION_113c, 0x505C8 },
        { GameVersion::VERSION_113d, 0x20FE8 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // Mouse over skill text position fix; Additional Pre-1.13c Patch
    // Replace active (level up) text draw code.
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C16E },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::CALL, (void*) D2HD::Draw::drawSkillButtonTextInterception, 0x3C1C0 - 0x3C16E),

    // Replace inactive (greyed out) text draw code.
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C22F },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::CALL, (void*) D2HD::Draw::drawSkillButtonTextInterception, 0x3C279 - 0x3C22F),

    // Inactive skill (greyed out) button position fix; Additional Pre-1.13c Patch
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C279 },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::CALL, (void*) D2HD::Draw::drawInactiveSkillButtonInterception, 0x3C297 - 0x3C279),

    // Inactive skill (greyed out) button fix
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C1F3 },
        { GameVersion::VERSION_113c, 0x50023 },
        { GameVersion::VERSION_113d, 0x20DA3 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),

    // Active skill (level up) button position fix; Additional Pre-1.13c Patch
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C1C0 },
        { GameVersion::VERSION_113c, D2Patch::NO_PATCH },
        { GameVersion::VERSION_113d, D2Patch::NO_PATCH }
    }), OpCode::CALL, (void*) D2HD::Draw::drawActiveSkillButtonInterception, 0x3C1DD - 0x3C1C0),

    // Active skill (level up) button fix
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3BFC7 },
        { GameVersion::VERSION_113c, 0x50207 },
        { GameVersion::VERSION_113d, 0x20B77 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C065 },
        { GameVersion::VERSION_113c, 0x502A5 },
        { GameVersion::VERSION_113d, 0x20C15 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C0DC },
        { GameVersion::VERSION_113c, 0x5031C },
        { GameVersion::VERSION_113d, 0x20C8C }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
        { GameVersion::VERSION_112, 0x3C140 },
        { GameVersion::VERSION_113c, 0x50380 },
        { GameVersion::VERSION_113d, 0x20CF0 }
    }), OpCode::CALL, (void*) D2HD::getPatchedResolutionModeInterception, 5),
};

// Patches inventory positions to be in the correct location. Credits to D2Ex.
static const std::vector<std::shared_ptr<D2BasePatch>> inventoryPatches = {
    // D2Common.Ordinal10333
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        { GameVersion::VERSION_112, 0x4BB10 },
        { GameVersion::VERSION_113c, 0x13340 },
        { GameVersion::VERSION_113d, 0x70780 }
    }), OpCode::JMP, (void*) D2HD::Inventory::getBeltPos, 7),

    // D2Common.Ordinal10991
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        { GameVersion::VERSION_112, 0x4BA30 },
        { GameVersion::VERSION_113c, 0x132A0 },
        { GameVersion::VERSION_113d, 0x706A0 }
    }), OpCode::JMP, (void*) D2HD::Inventory::getBeltsTxtRecord, 10),

    // D2Common.Ordinal11012
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        { GameVersion::VERSION_112, 0x1B100 },
        { GameVersion::VERSION_113c, 0x82030 },
        { GameVersion::VERSION_113d, 0x6BFB0 }
    }), OpCode::JMP, (void*) D2HD::Inventory::getInventorySize, 8),

    // D2Common.Ordinal10760
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        { GameVersion::VERSION_112, 0x1B080 },
        { GameVersion::VERSION_113c, 0x81FB0 },
        { GameVersion::VERSION_113d, 0x6BF30 }
    }), OpCode::JMP, (void*) D2HD::Inventory::getInventoryGrid, 8),

    // D2Common.Ordinal10701
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, {
        { GameVersion::VERSION_112, 0x1AFF0 },
        { GameVersion::VERSION_113c, 0x81F20 },
        { GameVersion::VERSION_113d, 0x6BEA0 }
    }), OpCode::JMP, (void*) D2HD::Inventory::getInventoryField, 8),
};

// Replace for HD, Resize Glide Game Window, but not used if using custom glide3x.dll
static const std::vector<std::shared_ptr<D2BasePatch>> glide3xPatches = {
    std::make_shared<D2InterceptorPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_GLIDE3X, {
        { GameVersion::VERSION_112, 0xCA97 },
        { GameVersion::VERSION_113c, 0xCA97 },
        { GameVersion::VERSION_113d, 0xCA97 }
    }), OpCode::CALL, (void*) D2HD::setupGlideWindowSizeInterception, 0xCBA7 - 0xCA97),
};

// end of file --------------------------------------------------------------
#endif
