/*****************************************************************************
 *                                                                           *
 *  SlashDiablo HD                                                           *
 *  Copyright (C) 2017  Mir Drualga                                          *
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
 *****************************************************************************/

/*****************************************************************************
 *                                                                           *
 *   DLLmain.cpp                                                             *
 *   Copyright (C) Olivier Verville                                          *
 *   SlashDiablo-Tools Modifications: Copyright (C) 2017 Mir Drualga         *
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
 *   https://github.com/olivier-verville/D2Template                          *
 *                                                                           *
 *   D2Template core file, do not modify unless you know what you're doing   *
 *                                                                           *
 *****************************************************************************/

#define _D2VARS_H

#include "DLLmain.h"

#include <fstream>

#include "D2Patch.h"
#include "D2Patches.h"

void __fastcall D2TEMPLATE_FatalError(LPCWSTR wszMessage) {
    MessageBoxW(nullptr, wszMessage, L"SlashDiablo HD", MB_OK | MB_ICONERROR);
    TerminateProcess(GetCurrentProcess(), -1);
}

bool __fastcall D2TEMPLATE_GetDebugPrivilege() {
    HANDLE hToken;
    LUID luid;
    TOKEN_PRIVILEGES tokenPrivileges;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken) == 0) {
        D2TEMPLATE_FatalError(L"OpenProcessToken Failed");
        return false;
    }

    if (LookupPrivilegeValue(0, SE_DEBUG_NAME, &luid) == 0) {
        D2TEMPLATE_FatalError(L"LookupPrivilegeValue Failed");
        CloseHandle(hToken);
        return false;
    }

    tokenPrivileges.PrivilegeCount = 1;
    tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    tokenPrivileges.Privileges[0].Luid = luid;

    if (AdjustTokenPrivileges(hToken, 0, &tokenPrivileges,
                              sizeof(tokenPrivileges), 0, 0) == 0) {
        D2TEMPLATE_FatalError(L"AdjustTokenPrivileges Failed");
        CloseHandle(hToken);
        return false;
    }

    CloseHandle(hToken);
    return true;
}

bool __stdcall DllAttach() {
    D2TEMPLATE_GetDebugPrivilege();

    HANDLE hGame = GetCurrentProcess();

    if (!hGame) {
        D2TEMPLATE_FatalError(L"Failed to retrieve process");
        return false;
    }

    if (D2Version::getGameVersion() == GameVersion::INVALID) {
        D2TEMPLATE_FatalError(
            L"SlashDiablo HD currently does not support this version of Diablo II.");
        return false;
    }

    config.readSettings();

    if (!config.isEnableMod()) {
        return true;
    }

    if constexpr (D2HD::D2HDConfig::ALLOW_LOAD_MPQ_ARCHIVE) {
        if (config.isEnableArchive()) {
            std::ifstream in(config.getArchiveName());

            if (in.good()) {
                in.close();
                D2HD::Draw::d2mrArchive = loadMPQ(5000, "SlashDiabloHD.dll",
                                                  config.getArchiveName().c_str(), "SlashDiabloHD", 0, nullptr);
            }
        }
    }

    D2Patch::applyPatches(requiredHDPatches);
    D2Patch::applyPatches(requiredDrawPatches);
    D2Patch::applyPatches(inventoryPatches);

    if (config.isEnable800ControlPanel()) {
        D2Patch::applyPatches(controlPanel800Patches);
    }

    if (D2Version::getGlide3xVersion() == Glide3xVersion::VERSION_14e) {
        D2Patch::applyPatches(glide3xPatches);
    }

    return true;
}

BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved) {
    switch (dwReason) {
    case DLL_PROCESS_ATTACH: {
        if (!DllAttach())
            D2TEMPLATE_FatalError(L"Couldn't attach to Diablo II");

        break;
    }
    }

    return TRUE;
}
