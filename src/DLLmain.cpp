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
    MessageBoxW(nullptr, wszMessage, L"D2Template", MB_OK | MB_ICONERROR);
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

    std::ifstream in(D2HD::D2HDConfig::DEFAULT_ARCHIVE_NAME);
    if (in.good()) {
        in.close();
        D2HD::Draw::d2mrArchive = loadMPQ(5000, "SlashDiabloHD.dll", D2HD::D2HDConfig::DEFAULT_ARCHIVE_NAME.c_str(), "SlashDiabloHD", 0, nullptr);
    }

    config.readSettings();
    D2Patch::applyPatches(requiredHDPatches);
    D2Patch::applyPatches(requiredDrawPatches);
    D2Patch::applyPatches(inventoryPatches);

    if (config.isEnable800ControlPanel()) {
        D2Patch::applyPatches(controlPanel800Patches);
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
