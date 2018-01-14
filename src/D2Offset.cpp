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
#include "DLLmain.h"

std::map<D2TEMPLATE_DLL_FILES, DLLBaseStrc> D2Offset::dllFiles;

D2Offset::D2Offset(const D2TEMPLATE_DLL_FILES dllFile,
                   const Offsets& offsets) : dllFile(dllFile), offsets(offsets) {
}

int D2Offset::getCurrentOffset() const {
    return *(&offsets._107 + (int) D2Version::getGameVersionID());
}

DWORD D2Offset::getCurrentAddress() const {
    if (dllFiles.count(dllFile) == 0) {
        if (!D2Offset::loadModules()) {
            D2TEMPLATE_FatalError(L"Failed to load modules");
            return 0;
        }
    }

    HMODULE baseAddress = dllFiles.at(dllFile).dwAddress;

    if (baseAddress == nullptr) {
        return 0;
    }

    int offset = getCurrentOffset();

    DWORD address;

    if (offset < 0) {
        address = (DWORD) GetProcAddress((HINSTANCE) baseAddress,
                                         (LPSTR) - offset);
    } else if (offset > 0) {
        address = (DWORD) baseAddress + offset;
    } else {
        return 0;
    }

    return address;
}

bool D2Offset::loadModules() {
    dllFiles = {
        { D2TEMPLATE_DLL_FILES::D2DLL_BINKW32, { L"Binkw32.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_BNCLIENT, { L"BnClient.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { L"D2Client.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2CMP, { L"D2CMP.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, { L"D2Common.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2DDRAW, { L"D2DDraw.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2DIRECT3D, { L"D2Direct3D.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2GAME, { L"D2Game.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, { L"D2Gdi.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, { L"D2Gfx.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2GLIDE, { L"D2Glide.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2LANG, { L"D2Lang.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2LAUNCH, { L"D2Launch.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2MCPCLIENT, { L"D2MCPClient.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2MULTI, { L"D2Multi.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2NET, { L"D2Net.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2SOUND, { L"D2Sound.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_D2WIN, { L"D2Win.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_FOG, { L"Fog.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_IJL11, { L"Ijl11.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_SMACKW32, { L"SmackW32.dll", nullptr }},
        { D2TEMPLATE_DLL_FILES::D2DLL_STORM, { L"Storm.dll", nullptr }}
    };

    for (auto& dllFile : dllFiles) {
        std::wstring moduleName = std::wstring(dllFile.second.wszName);

        if (D2Version::isGameVersion114Plus()) {
            if (moduleName == L"BnClient.dll" || moduleName == L"D2Client.dll"
                    || moduleName == L"D2CMP.dll" || moduleName == L"D2Common.dll"
                    || moduleName == L"D2DDraw.dll" || moduleName == L"D2Direct3D.dll"
                    || moduleName == L"D2Game.dll" || moduleName == L"D2Gdi.dll"
                    || moduleName == L"D2Gfx.dll" || moduleName == L"D2Glide.dll"
                    || moduleName == L"D2Lang.dll" || moduleName == L"D2Launch.dll"
                    || moduleName == L"D2MCPClient.dll" || moduleName == L"D2Multi.dll"
                    || moduleName == L"D2Net.dll" || moduleName == L"D2Sound.dll"
                    || moduleName == L"D2Win.dll" || moduleName == L"Fog.dll"
                    || moduleName == L"Storm.dll") {
                moduleName = L"Game.exe";
            }
        }

        HMODULE hModule = GetModuleHandleW(moduleName.c_str());

        if (!hModule) {
            hModule = LoadLibraryW(moduleName.c_str());
        }

        dllFile.second.dwAddress = hModule;
    }

    return true;
}
