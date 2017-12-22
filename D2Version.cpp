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
#include <sstream>

#pragma comment(lib,"Version.lib")

D2Version::GameVersionID D2Version::gameVersionID = D2Version::GameVersionID::INVALID;
D2Version::Glide3xVersionID D2Version::glide3xVersionID = D2Version::Glide3xVersionID::INVALID;

void D2Version::Init() {
    std::string gameVersion = GetGameVersionString();

    if (gameVersion == "1.0.13.60") {
        gameVersionID = GameVersionID::VERSION_113c;
    } else if (gameVersion == "1.0.13.64") {
        gameVersionID = GameVersionID::VERSION_113d;
    } else {
        gameVersionID = GameVersionID::INVALID;
    }

    std::string glide3xVersion = GetGlide3xVersionString();

    if (glide3xVersion == "1.4.4.21") {
        glide3xVersionID = Glide3xVersionID::VERSION_14e;
    } else if (glide3xVersion == "1.4.8.2") {
        glide3xVersionID = Glide3xVersionID::RESURGENCE;
    } else {
        glide3xVersionID = Glide3xVersionID::INVALID;
    }
}

D2Version::GameVersionID D2Version::GetGameVersionID() {
    if (gameVersionID == GameVersionID::INVALID) {
        Init();
    }
    return gameVersionID;
}

D2Version::Glide3xVersionID D2Version::GetGlide3xVersionID() {
    if (glide3xVersionID == Glide3xVersionID::INVALID) {
        Init();
    }
    return glide3xVersionID;
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
                        // Doesn't matter if you are on 32 bit or 64 bit,
                        // DWORD is always 32 bits, so first two revision numbers
                        // come from dwFileVersionMS, last two come from dwFileVersionLS
                        std::ostringstream stringStream;

                        stringStream << ((verInfo->dwFileVersionMS >> 16) & 0xffff) << ".";
                        stringStream << ((verInfo->dwFileVersionMS >> 0) & 0xffff) << ".";
                        stringStream << ((verInfo->dwFileVersionLS >> 16) & 0xffff) << ".";
                        stringStream << ((verInfo->dwFileVersionLS >> 0) & 0xffff);

                        returnValue = stringStream.str();
                    }
                }
            }
        }
        delete[] verData;
    }
    return returnValue;
}

std::string D2Version::GetGlide3xVersionString() {
    LPSTR szVersionFile = "glide3x.dll";
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
                        // Doesn't matter if you are on 32 bit or 64 bit,
                        // DWORD is always 32 bits, so first two revision numbers
                        // come from dwFileVersionMS, last two come from dwFileVersionLS
                        std::ostringstream stringStream;

                        stringStream << ((verInfo->dwFileVersionMS >> 16) & 0xffff) << ".";
                        stringStream << ((verInfo->dwFileVersionMS >> 0) & 0xffff) << ".";
                        stringStream << ((verInfo->dwFileVersionLS >> 16) & 0xffff) << ".";
                        stringStream << ((verInfo->dwFileVersionLS >> 0) & 0xffff);

                        returnValue = stringStream.str();
                    }
                }
            }
        }
        delete[] verData;
    }
    return returnValue;
}
