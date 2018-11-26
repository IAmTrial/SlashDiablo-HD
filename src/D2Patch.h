/*****************************************************************************
 *                                                                           *
 * SlashDiablo HD                                                            *
 * Copyright (C) 2017  Mir Drualga                                           *
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
 *---------------------------------------------------------------------------*
 *                                                                           *
 *   A convenience file to include all patch types and to declare the        *
 *   applyPatches functions to apply all patches in a vector.                *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2PATCH_H
#define _D2PATCH_H

enum class OpCode : BYTE;

enum class OpCode : BYTE;

#include "D2Patch/D2AnyPatch.h"
#include "D2Patch/D2BasePatch.h"
#include "D2Patch/D2InterceptorPatch.h"

enum class OpCode : BYTE {
    NOP = 0x90,
    CALL = 0xE8,
    JMP = 0xE9
};

namespace D2Patch {
static constexpr long long int NO_PATCH = 0x4000000000000000;

template<class T>
bool applyPatches(const T patches) {
    // For anyone encountering errors here:
    // The function only accepts containers of (smart) D2BasePatch pointers.
    bool returnValue = true;

    for (const auto& patch : patches) {
        returnValue = returnValue && patch->applyPatch();
    }

    return returnValue;
}
}

#endif // _D2PATCH_H
