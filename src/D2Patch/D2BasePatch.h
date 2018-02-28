/*****************************************************************************
 *                                                                           *
 *   D2BasePatch.h                                                           *
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
 *   This file declares the base patch class, which provides an interface    *
 *   for more specific patches that are used for applying patches for        *
 *   Diablo II.                                                              *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2PATCH_H
#define _D2PATCH_H

#include <memory>
#include <vector>

#include "../D2Offset.h"

enum class OpCode : BYTE {
    NOP = 0x90,
    CALL = 0xE8,
    JMP = 0xE9
};

class D2BasePatch {
public:
    static constexpr long long int NO_PATCH = 0x4000000000000000;

    static bool applyPatches(const std::vector<std::shared_ptr<D2BasePatch>>& patches);
    virtual bool applyPatch() const = 0;

    const D2Offset& getD2Offset() const;
    bool isRelative() const;
    size_t getPatchSize() const;

protected:
    D2BasePatch(const D2Offset& d2Offset, const size_t patchSize);
    D2BasePatch(D2BasePatch&& d2Patch) = default;

private:
    D2Offset d2Offset;
    size_t patchSize;

    D2BasePatch() = delete;
};

#endif
