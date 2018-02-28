/*****************************************************************************
 *                                                                           *
 *   D2AnyPatch.h                                                            *
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
 *   This file declares the D2AnyPatch class, which can be used to create    *
 *   any patch for Diablo II.                                                *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2ANYPATCH_H
#define _D2ANYPATCH_H

#include <windows.h>

#include "D2BasePatch.h"
#include "../D2Offset.h"

class D2AnyPatch : public D2BasePatch {
public:
    D2AnyPatch(const D2Offset& d2Offset, const DWORD data, const bool relative,
            const size_t patchSize);
    D2AnyPatch(const D2Offset& d2Offset, const OpCode opCode, const bool relative,
            const size_t patchSize);

    virtual bool applyPatch() const override;
    bool isRelative() const;

private:
    DWORD data;
    bool relative;
};

#endif
