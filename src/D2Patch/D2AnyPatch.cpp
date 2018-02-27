/*****************************************************************************
 *                                                                           *
 *   D2AnyPatch.cpp                                                          *
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
 *   This file defines functions used by the D2AnyPatch class, which can     *
 *   create any type of patch to Diablo II.                                  *
 *                                                                           *
 *****************************************************************************/

#include "D2AnyPatch.h"

D2AnyPatch::D2AnyPatch(const D2Offset& d2Offset, const DWORD data,
                       const bool relative, size_t patchSize) : D2Patch(d2Offset, relative, patchSize),
    data(data) {
}

bool D2AnyPatch::applyPatch() const {
    HANDLE gameHandle = GetCurrentProcess();

    if ((getD2Offset().getCurrentOffset() & D2AnyPatch::NO_PATCH) ==
            D2AnyPatch::NO_PATCH) {
        return true;
    }

    DWORD dwAddress = getD2Offset().getCurrentAddress();

    if (dwAddress == 0) {
        return false;
    }

    DWORD dwData = data;

    if (isRelative()) {
        dwData = dwData - (dwAddress + sizeof(dwData));
    }

    LPVOID hAddress = (LPVOID) dwAddress;
    DWORD dwOldPage;

    int nReturn = 0;

    if (getPatchSize() > 0) {
        BYTE Buffer[1024];

        for (size_t i = 0; i < getPatchSize(); i++)
            Buffer[i] = (BYTE) dwData;

        VirtualProtect(hAddress, getPatchSize(), PAGE_EXECUTE_READWRITE, &dwOldPage);
        nReturn = WriteProcessMemory(gameHandle, hAddress, &Buffer, getPatchSize(),
                                     0);
        VirtualProtect(hAddress, getPatchSize(), dwOldPage, 0);
    } else {
        VirtualProtect(hAddress, sizeof(dwData), PAGE_EXECUTE_READWRITE,
                       &dwOldPage);
        nReturn = WriteProcessMemory(gameHandle, hAddress, &dwData,
                                     sizeof(dwData), 0);
        VirtualProtect(hAddress, sizeof(dwData), dwOldPage, 0);
    }

    if (nReturn == 0) {
        return false;
    }

    return true;
}
