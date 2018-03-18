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
 *   This file declares the D2AnyPatch class, which can be used to create    *
 *   any patch for Diablo II.                                                *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2ANYPATCH_H
#define _D2ANYPATCH_H

#include <windows.h>

#include "D2BasePatch.h"
#include "../D2Patch.h"
#include "../D2Offset.h"

class D2AnyPatch : public D2BasePatch {
public:
    D2AnyPatch(const D2Offset& d2Offset, const DWORD data, const bool relative,
            const size_t patchSize);
    D2AnyPatch(const D2Offset& d2Offset, const OpCode opCode, const bool relative,
            const size_t patchSize);
    D2AnyPatch(D2AnyPatch&& d2AnyPatch) = default;

    virtual bool applyPatch() const override;
    bool isRelative() const;

private:
    DWORD data;
    bool relative;
};

#endif
