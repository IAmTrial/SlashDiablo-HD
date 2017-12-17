/****************************************************************************
*                                                                           *
*   D2Version.cpp                                                           *
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
*   Defines the functions that are used for Diablo II Game.exe version      *
*   detection.                                                              *
*                                                                           *
*****************************************************************************/

#include "D2Version.h"
#include <Windows.h>

#pragma comment(lib,"Version.lib")

VersionID D2Version::versionID = INVALID;

void D2Version::Init() {
    std::string version = GetGameVersionString();

    if (version == "1.0.13.60") {
        versionID = VERSION_113c;
    } else if (version == "1.0.13.64") {
        versionID = VERSION_113d;
    } else {
        versionID = INVALID;
    }
}

VersionID D2Version::GetGameVersionID() {
    if (versionID == INVALID) {
        Init();
    }
    return versionID;
}

// Taken from StackOverflow user crashmstr
std::string D2Version::GetGameVersionString() {
    LPSTR szVersionFile = "Game.exe";
    DWORD  verHandle = 0;
    UINT   size = 0;
    LPBYTE lpBuffer = NULL;
    DWORD  verSize = GetFileVersionInfoSize(szVersionFile, &verHandle);

    std::string returnValue;

    if (verSize != NULL) {
        LPSTR verData = new char[verSize];

        if (GetFileVersionInfo(szVersionFile, verHandle, verSize, verData)) {
            if (VerQueryValue(verData, "\\", (VOID FAR* FAR*)&lpBuffer, &size)) {
                if (size) {
                    VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
                    if (verInfo->dwSignature == 0xfeef04bd) {
                        char szBuffer[MAX_PATH];
                        // Doesn't matter if you are on 32 bit or 64 bit,
                        // DWORD is always 32 bits, so first two revision numbers
                        // come from dwFileVersionMS, last two come from dwFileVersionLS
                        std::sprintf(szBuffer, "%d.%d.%d.%d",
                            (verInfo->dwFileVersionMS >> 16) & 0xffff,
                            (verInfo->dwFileVersionMS >> 0) & 0xffff,
                            (verInfo->dwFileVersionLS >> 16) & 0xffff,
                            (verInfo->dwFileVersionLS >> 0) & 0xffff
                            );

                        returnValue = std::string(szBuffer);
                    }
                }
            }
        }
        delete[] verData;
    }
    return returnValue;
}
