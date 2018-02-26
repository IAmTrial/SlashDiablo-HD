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

#include <windows.h>

#include <unordered_map>
#include <vector>

#include "D2Version.h"

enum class D2TEMPLATE_DLL_FILES
    : int {
    D2DLL_BINKW32,
    D2DLL_BNCLIENT,
    D2DLL_D2CLIENT,
    D2DLL_D2CMP,
    D2DLL_D2COMMON,
    D2DLL_D2DDRAW,
    D2DLL_D2DIRECT3D,
    D2DLL_D2GAME,
    D2DLL_D2GDI,
    D2DLL_D2GFX,
    D2DLL_D2GLIDE,
    D2DLL_D2LANG,
    D2DLL_D2LAUNCH,
    D2DLL_D2MCPCLIENT,
    D2DLL_D2MULTI,
    D2DLL_D2NET,
    D2DLL_D2SOUND,
    D2DLL_D2WIN,
    D2DLL_FOG,
    D2DLL_IJL11,
    D2DLL_SMACKW32,
    D2DLL_STORM,
};

struct DLLBaseStrc {
    LPCWSTR wszName;
    HMODULE dwAddress;
};

class D2Offset {
public:
    D2Offset(const D2TEMPLATE_DLL_FILES dllFile,
             const std::unordered_map<D2Version::GameVersion, long long int>& offsets);

    long long int getCurrentOffset() const;
    DWORD getCurrentAddress() const;

private:
    D2TEMPLATE_DLL_FILES dllFile;
    std::unordered_map<D2Version::GameVersion, long long int> offsets;

    static HMODULE getDllAddress(D2TEMPLATE_DLL_FILES dllFile);
};

#endif
