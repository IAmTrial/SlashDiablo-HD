/*****************************************************************************
 *                                                                           *
 *   D2Offset.cpp                                                            *
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
 *   This file defines the functions that correctly manages returning the    *
 *   correct offset for the requested Diablo II variable, function, or       *
 *   pointer.                                                                *
 *                                                                           *
 *****************************************************************************/

#include "D2Offset.h"

#include <windows.h>

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "D2Version.h"
#include "DLLmain.h"

D2Offset::D2Offset(const D2TEMPLATE_DLL_FILES dllFile,
                   const std::unordered_map<GameVersion, long long int>& offsets) :
    dllFile(dllFile), offsets(offsets) {
}

long long int D2Offset::getCurrentOffset() const {
    return offsets.at(D2Version::getGameVersion());
}

DWORD D2Offset::getCurrentAddress() const {
    HMODULE baseAddress = getDllAddress(dllFile);

    if (baseAddress == nullptr) {
        return 0;
    }

    long long int offset = getCurrentOffset();

    DWORD address;

    if (offset < 0) {
        address = (DWORD) GetProcAddress((HINSTANCE) baseAddress,
                                         (LPSTR) - offset);
    } else {
        address = (DWORD) baseAddress + (DWORD)offset;
    }

    return address;
}

HMODULE D2Offset::getDllAddress(D2TEMPLATE_DLL_FILES dllFile) {
    static std::unordered_map<D2TEMPLATE_DLL_FILES, HMODULE> dllHandles;
    static const std::unordered_map<D2TEMPLATE_DLL_FILES, std::wstring_view>
    dllFilePaths = {
        { D2TEMPLATE_DLL_FILES::D2DLL_BINKW32, L"Binkw32.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_BNCLIENT, L"BnClient.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, L"D2Client.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2CMP, L"D2CMP.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, L"D2Common.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2DDRAW, L"D2DDraw.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2DIRECT3D, L"D2Direct3D.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2GAME, L"D2Game.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, L"D2Gdi.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, L"D2Gfx.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2GLIDE, L"D2Glide.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2LANG, L"D2Lang.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2LAUNCH, L"D2Launch.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2MCPCLIENT, L"D2MCPClient.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2MULTI, L"D2Multi.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2NET, L"D2Net.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2SOUND, L"D2Sound.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_D2WIN, L"D2Win.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_FOG, L"Fog.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_IJL11, L"Ijl11.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_SMACKW32, L"SmackW32.dll" },
        { D2TEMPLATE_DLL_FILES::D2DLL_STORM, L"Storm.dll" }
    };

    static const std::unordered_set<D2TEMPLATE_DLL_FILES> redirectedDlls = {
        D2TEMPLATE_DLL_FILES::D2DLL_BNCLIENT, D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT,
        D2TEMPLATE_DLL_FILES::D2DLL_D2CMP, D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON,
        D2TEMPLATE_DLL_FILES::D2DLL_D2DDRAW, D2TEMPLATE_DLL_FILES::D2DLL_D2DIRECT3D,
        D2TEMPLATE_DLL_FILES::D2DLL_D2GAME, D2TEMPLATE_DLL_FILES::D2DLL_D2GDI,
        D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, D2TEMPLATE_DLL_FILES::D2DLL_D2GLIDE,
        D2TEMPLATE_DLL_FILES::D2DLL_D2LANG, D2TEMPLATE_DLL_FILES::D2DLL_D2LAUNCH,
        D2TEMPLATE_DLL_FILES::D2DLL_D2MCPCLIENT, D2TEMPLATE_DLL_FILES::D2DLL_D2MULTI,
        D2TEMPLATE_DLL_FILES::D2DLL_D2NET, D2TEMPLATE_DLL_FILES::D2DLL_D2SOUND,
        D2TEMPLATE_DLL_FILES::D2DLL_D2WIN, D2TEMPLATE_DLL_FILES::D2DLL_FOG,
        D2TEMPLATE_DLL_FILES::D2DLL_STORM
    };

    HMODULE dllAddress = dllHandles[dllFile];

    if (dllAddress == nullptr) {
        std::wstring_view moduleName = dllFilePaths.at(dllFile);

        if (D2Version::isGameVersion114Plus()) {
            if (redirectedDlls.count(dllFile) == 1) {
                moduleName = L"Game.exe";
            }
        }

        dllAddress = GetModuleHandleW(moduleName.data());

        if (dllAddress == nullptr) {
            dllAddress = LoadLibraryW(moduleName.data());
        }

        dllHandles.at(dllFile) = dllAddress;
    }

    return dllAddress;
}
