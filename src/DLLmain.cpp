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
#include "D2Patch.h"
#include "D2Patches.h"

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

void __fastcall D2TEMPLATE_FatalError(LPCWSTR wszMessage) {
    MessageBoxW(NULL, wszMessage, L"D2Template", MB_OK | MB_ICONERROR);
    TerminateProcess(GetCurrentProcess(), -1);
}

bool __fastcall D2TEMPLATE_LoadModules() {
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

    if (!D2TEMPLATE_LoadModules()) {
        D2TEMPLATE_FatalError(L"Failed to load modules");
        return false;
    }

    D2HD::Config::readConfig();
    D2Patch::applyPatches(requiredHDPatches);

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