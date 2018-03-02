/*****************************************************************************
 *                                                                           *
 *   D2Patch.h                                                               *
 *   Copyright (C) 2017 Mir Drualga                                          *
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
