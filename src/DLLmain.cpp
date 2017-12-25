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
#include "D2Patches.h"

void __fastcall D2TEMPLATE_FatalError(const wchar_t* szMessage) {
    MessageBoxW(NULL, szMessage, L"D2Template", MB_OK | MB_ICONERROR);
    TerminateProcess(GetCurrentProcess(), -1);
}

bool __fastcall D2TEMPLATE_ApplyPatch(void* hGame, const DLLPatchStrc* hPatch) {
    while (hPatch->nDLL != D2TEMPLATE_DLL_FILES::D2DLL_INVALID) {
        int nReturn = 0;
        int nDLL = (int) hPatch->nDLL;
        if (nDLL < 0 || nDLL >= (int) D2TEMPLATE_DLL_FILES::D2DLL_INVALID) {
            return false;
        }

        HMODULE dwBaseAddress = gptDllFiles[nDLL].dwAddress;
        if (!dwBaseAddress) {
            return false;
        }

        D2Pointer pointers = hPatch->d2Pointer;
        int offset = pointers.getCurrentPointer();

        DWORD dwAddress;
        if (offset < 0) {
            dwAddress = (DWORD) GetProcAddress((HINSTANCE) dwBaseAddress,
                    (LPSTR) -offset);
        } else if (offset > 0) {
            dwAddress = (DWORD) dwBaseAddress + offset;
        } else {
            return false;
        }

        DWORD dwData = hPatch->dwData;
        if (hPatch->bRelative) {
            dwData = dwData - (dwAddress + sizeof(dwData));
        }

        LPVOID hAddress = (LPVOID) dwAddress;
        DWORD dwOldPage;

        if (hPatch->nPatchSize > 0) {
            BYTE Buffer[1024];

            for (size_t i = 0; i < hPatch->nPatchSize; i++)
                Buffer[i] = (BYTE) dwData;

            VirtualProtect(hAddress, hPatch->nPatchSize, PAGE_EXECUTE_READWRITE,
                    &dwOldPage);
            nReturn = WriteProcessMemory(hGame, hAddress, &Buffer,
                    hPatch->nPatchSize, 0);
            VirtualProtect(hAddress, hPatch->nPatchSize, dwOldPage, 0);
        } else {
            VirtualProtect(hAddress, sizeof(dwData), PAGE_EXECUTE_READWRITE,
                    &dwOldPage);
            nReturn = WriteProcessMemory(hGame, hAddress, &dwData,
                    sizeof(dwData), 0);
            VirtualProtect(hAddress, sizeof(dwData), dwOldPage, 0);
        }

        if (nReturn == 0) {
            return false;
        }

        hPatch++;
    }

    return true;
}

bool __fastcall D2TEMPLATE_LoadModules() {
    for (int i = 0; i < (int) D2TEMPLATE_DLL_FILES::D2DLL_INVALID; i++) {
        DLLBaseStrc* hDllFile = &gptDllFiles[i];

        HMODULE hModule = GetModuleHandleW(hDllFile->szName);
        if (!hModule) {
            hModule = LoadLibraryW(hDllFile->szName);
        }

        hDllFile->dwAddress = hModule;
    }

    return true;
}

bool __fastcall D2TEMPLATE_GetDebugPrivilege() {
    void* hToken;
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

    void* hGame = GetCurrentProcess();
    if (!hGame) {
        D2TEMPLATE_FatalError(L"Failed to retrieve process");
        return false;
    }

    if (!D2TEMPLATE_LoadModules()) {
        D2TEMPLATE_FatalError(L"Failed to load modules");
        return false;
    }

    D2TEMPLATE_ApplyPatch(hGame, gptTemplatePatches);

    return true;
}

BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, void* lpReserved) {
    switch (dwReason) {
    case DLL_PROCESS_ATTACH: {
        if (!DllAttach())
            D2TEMPLATE_FatalError(L"Couldn't attach to Diablo II");
        break;
    }
    }

    return TRUE;
}
