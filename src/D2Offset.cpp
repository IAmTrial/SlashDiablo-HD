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

DLLBaseStrc gptDllFiles[] = {
        { L"Binkw32.dll", nullptr },
        { L"BnClient.dll", nullptr },
        { L"D2Client.dll", nullptr },
        { L"D2CMP.dll", nullptr },
        { L"D2Common.dll", nullptr },
        { L"D2DDraw.dll", nullptr },
        { L"D2Direct3D.dll", nullptr },
        { L"D2Game.dll", nullptr },
        { L"D2Gdi.dll", nullptr },
        { L"D2Gfx.dll", nullptr },
        { L"D2Glide.dll", nullptr },
        { L"D2Lang.dll", nullptr },
        { L"D2Launch.dll", nullptr },
        { L"D2MCPClient.dll", nullptr },
        { L"D2Multi.dll", nullptr },
        { L"D2Net.dll", nullptr },
        { L"D2Sound.dll", nullptr },
        { L"D2Win.dll", nullptr },
        { L"Fog.dll", nullptr },
        { L"Ijl11.dll", nullptr },
        { L"SmackW32.dll", nullptr },
        { L"Storm.dll", nullptr } };

D2Offset::D2Offset() :
        D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_INVALID, { }) {
}

/*D2Offset::D2Offset(Offsets offsets) :
        D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_INVALID, offsets) {
}*/

D2Offset::D2Offset(D2TEMPLATE_DLL_FILES dllFile, Offsets offsets) {
    D2Offset::dllFile = dllFile;
    D2Offset::offsets = offsets;
}

int D2Offset::getCurrentOffset() {
    return *(&offsets._107 + (int) D2Version::getGameVersionID());
}

DWORD D2Offset::getCurrentAddress() {
    int nDLL = (int) dllFile;
    if (nDLL < 0 || nDLL >= (int) D2TEMPLATE_DLL_FILES::D2DLL_INVALID) {
        return 0;
    }

    HMODULE baseAddress = gptDllFiles[nDLL].dwAddress;
    if (!baseAddress) {
        D2Offset::loadModules();
        if (!baseAddress) {
            return 0;
        }
    }

    int offset = getCurrentOffset();

    DWORD address;
    if (offset < 0) {
        address = (DWORD) GetProcAddress((HINSTANCE) baseAddress,
                (LPSTR) -offset);
    } else if (offset > 0) {
        address = (DWORD) baseAddress + offset;
    } else {
        return 0;
    }

    return address;
}

bool D2Offset::loadModules() {
    for (int i = 0; i < (int) D2TEMPLATE_DLL_FILES::D2DLL_INVALID; i++) {
        DLLBaseStrc* hDllFile = &gptDllFiles[i];

        HMODULE hModule = GetModuleHandleW(hDllFile->wszName);
        if (!hModule) {
            hModule = LoadLibraryW(hDllFile->wszName);
        }

        hDllFile->dwAddress = hModule;
    }

    return true;
}
