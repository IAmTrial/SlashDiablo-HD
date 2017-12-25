/*****************************************************************************
 *                                                                           *
 *   D2Patch.cpp                                                             *
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
 *   This file defines functions used by the D2Patch class, to help apply    *
 *   patches for Diablo II.                                                  *
 *                                                                           *
 *****************************************************************************/

#include "D2Patch.h"

D2Patch::D2Patch() : D2Patch(D2Offset(), 0, false, 0) {
}

D2Patch::D2Patch(D2Offset d2Offset, DWORD data,
        bool relative, size_t patchSize)
        {
    D2Patch::d2Offset = d2Offset;
    D2Patch::data = data;
    D2Patch::relative = relative;
    D2Patch::patchSize = patchSize;
}

bool D2Patch::applyPatch() {
    HANDLE gameHandle = GetCurrentProcess();
    int nReturn = 0;

    DWORD dwAddress = d2Offset.getCurrentAddress();
    if (dwAddress == 0) {
        return false;
    }

    DWORD dwData = data;
    if (relative) {
        dwData = dwData - (dwAddress + sizeof(dwData));
    }

    LPVOID hAddress = (LPVOID) dwAddress;
    DWORD dwOldPage;

    if (patchSize > 0) {
        BYTE Buffer[1024];

        for (size_t i = 0; i < patchSize; i++)
            Buffer[i] = (BYTE) dwData;

        VirtualProtect(hAddress, patchSize, PAGE_EXECUTE_READWRITE, &dwOldPage);
        nReturn = WriteProcessMemory(gameHandle, hAddress, &Buffer, patchSize,
                0);
        VirtualProtect(hAddress, patchSize, dwOldPage, 0);
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

bool D2Patch::applyPatches(std::vector<D2Patch> patches) {
    bool returnValue = true;

    for (auto& patch : patches) {
        returnValue = returnValue && patch.applyPatch();
    }

    return returnValue;
}
