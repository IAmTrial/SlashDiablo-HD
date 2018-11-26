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
 *   This file declares the base patch class, which provides an interface    *
 *   for more specific patches that are used for applying patches for        *
 *   Diablo II.                                                              *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2BASEPATCH_H
#define _D2BASEPATCH_H

#include <memory>
#include <vector>

#include "../D2Offset.h"

class D2BasePatch {
public:
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
