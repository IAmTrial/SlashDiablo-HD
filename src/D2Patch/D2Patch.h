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
 *   This file declares the D2Patch base class, which provides an interface  *
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

class D2Patch {
public:
    static constexpr long long int NO_PATCH = 0x4000000000000000;

    D2Patch(const D2Offset& d2Offset, const bool relative, const size_t patchSize);

    static bool applyPatches(const std::vector<std::shared_ptr<D2Patch>>& patches);
    virtual bool applyPatch() const = 0;

    D2Offset getD2Offset() const;
    bool isRelative() const;
    size_t getPatchSize() const;


private:
    D2Offset d2Offset;
    bool relative;
    size_t patchSize;

    D2Patch() = delete;
};

#endif
