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

D2Offset::D2Offset() :
        D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_INVALID, { }) {
}

D2Offset::D2Offset(Offsets offsets) :
        D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_INVALID, offsets) {
}

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
        return 0;
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
