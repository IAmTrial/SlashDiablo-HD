/*****************************************************************************
 *                                                                           *
 *   D2IntercerptorPatch.h                                                   *
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
 *   This file declares the D2InterceptorPatch class, which is specifically  *
 *   designed to simplify replacing Diablo II code with interception         *
 *   functions.                                                              *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2INTERCEPTORPATCH_H
#define _D2INTERCEPTORPATCH_H

#include <windows.h>
#include <any>
#include <functional>

#include "D2Patch.h"
#include "../D2Offset.h"

class D2InterceptorPatch : public D2Patch {
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
