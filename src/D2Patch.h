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
 *   This file declares the D2Patch class, which is used to for applying     *
 *   patches for Diablo II.                                                  *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2PATCH_H
#define _D2PATCH_H

#include <vector>
#include "D2Offset.h"

class D2Patch {
public:
    D2Patch(const D2Offset& d2Offset, const DWORD data, const bool relative, const size_t patchSize);
    bool applyPatch() const;
    static bool applyPatches(const std::vector<D2Patch>& patches);

private:
    D2Offset d2Offset;
    DWORD data;
    bool relative;
    size_t patchSize;
};

#endif
