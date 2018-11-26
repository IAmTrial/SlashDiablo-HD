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
 *   This file defines functions used by the D2AnyPatch class, which can     *
 *   create any type of patch to Diablo II.                                  *
 *                                                                           *
 *****************************************************************************/

#include "D2AnyPatch.h"

#include <windows.h>

#include "../D2Offset.h"

D2AnyPatch::D2AnyPatch(const D2Offset& d2Offset, const DWORD data,
                       const bool relative = false, size_t patchSize = 0) : D2BasePatch(d2Offset,
                                   patchSize),
    data(data), relative(relative) {
}

D2AnyPatch::D2AnyPatch(const D2Offset& d2Offset, const OpCode opCode,
                       const bool relative = false, size_t patchSize = 0) : D2AnyPatch(d2Offset,
                                   (int)opCode, relative, patchSize) {
}

bool D2AnyPatch::applyPatch() const {
    HANDLE gameHandle = GetCurrentProcess();

    if ((getD2Offset().getCurrentOffset() & D2Patch::NO_PATCH) ==
            D2Patch::NO_PATCH) {
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

    bool nReturn;

    if (getPatchSize() > 0) {
        std::unique_ptr<BYTE[]> buffer(new BYTE[getPatchSize()]);

        for (size_t i = 0; i < getPatchSize(); i++) {
            buffer[i] = (BYTE) dwData;
        }

        VirtualProtect(hAddress, getPatchSize(), PAGE_EXECUTE_READWRITE, &dwOldPage);
        nReturn = WriteProcessMemory(gameHandle, hAddress, buffer.get(), getPatchSize(),
                                     0);
        VirtualProtect(hAddress, getPatchSize(), dwOldPage, &dwOldPage);
    } else {
        VirtualProtect(hAddress, sizeof(dwData), PAGE_EXECUTE_READWRITE,
                       &dwOldPage);
        nReturn = WriteProcessMemory(gameHandle, hAddress, &dwData,
                                     sizeof(dwData), 0);
        VirtualProtect(hAddress, sizeof(dwData), dwOldPage, &dwOldPage);
    }

    if (nReturn == 0) {
        return false;
    }

    return true;
}

bool D2AnyPatch::isRelative() const {
    return relative;
}
