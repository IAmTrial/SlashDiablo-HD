/*****************************************************************************
 *                                                                           *
 *   D2Patch.cpp                                                             *
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
 *   This file defines functions used by the D2Patch class, to define some   *
 *   of the functions used by more specific Diablo II patches.               *
 *                                                                           *
 *****************************************************************************/

#include "D2Patch.h"

#include <memory>
#include <vector>

#include "../D2Offset.h"

D2Patch::D2Patch(const D2Offset& d2Offset, const size_t patchSize) : d2Offset(d2Offset), patchSize(patchSize) {
}

bool D2Patch::applyPatches(const std::vector<std::shared_ptr<D2Patch>>& patches) {
    bool returnValue = true;

    for (const auto& patch : patches) {
        returnValue = returnValue && patch->applyPatch();
    }

    return returnValue;
}

const D2Offset& D2Patch::getD2Offset() const {
    return d2Offset;
}

size_t D2Patch::getPatchSize() const {
    return patchSize;
}
