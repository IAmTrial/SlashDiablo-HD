/*****************************************************************************
 *                                                                           *
 *   D2Offset.h                                                              *
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
 *   This file is used when defining offset information for Diablo II while  *
 *   allowing flexible ports to multiple versions.                           *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2OFFSET_H
#define _D2OFFSET_H

#include "DLLmain.h"

struct Offsets {
    int _107, _108;
    int _109, _109b, _109c, _109d;
    int _110;
    int _111, _111b;
    int _112;
    int _113c, _113d;
    int _114a, _114b, _114c, _114d;
};

class D2Offset {
public:
    D2Offset();
    D2Offset(D2TEMPLATE_DLL_FILES dllFile, Offsets offsets);
    int getCurrentOffset();
    DWORD getCurrentAddress();

private:
    D2TEMPLATE_DLL_FILES dllFile;
    Offsets offsets;
};

#endif
