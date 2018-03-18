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
    D2DLL_GLIDE3X,
    D2DLL_IJL11,
    D2DLL_SMACKW32,
    D2DLL_STORM
};

class D2Offset {
public:
    D2Offset(const D2TEMPLATE_DLL_FILES dllFile,
             const std::unordered_map<GameVersion, long long int>& offsets);

    long long int getCurrentOffset() const;
    DWORD getCurrentAddress() const;

private:
    D2TEMPLATE_DLL_FILES dllFile;
    std::unordered_map<GameVersion, long long int> offsets;

    static HMODULE getDllAddress(D2TEMPLATE_DLL_FILES dllFile);
};

#endif
