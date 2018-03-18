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
 *   This file declares the D2InterceptorPatch class, which is specifically  *
 *   designed to simplify replacing Diablo II code with interception         *
 *   functions.                                                              *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2INTERCEPTORPATCH_H
#define _D2INTERCEPTORPATCH_H

#include <windows.h>

#include "D2BasePatch.h"
#include "../D2Patch.h"
#include "../D2Offset.h"

class D2InterceptorPatch : public D2BasePatch {
public:
    D2InterceptorPatch(const D2Offset& d2Offset, const OpCode& opCode,
                       void* const pFunc, const size_t patchSize);
    D2InterceptorPatch(D2InterceptorPatch&& d2InterceptorPatch) = default;

    virtual bool applyPatch() const override;
    OpCode getOpCode() const;

private:
    OpCode opCode;
    void* pFunc;
};

#endif
