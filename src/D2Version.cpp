/*****************************************************************************
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

// #pragma comment(lib,"Version.lib")

D2Version::GameVersionID D2Version::gameVersionID =
        D2Version::GameVersionID::INVALID;
D2Version::Glide3xVersionID D2Version::glide3xVersionID =
        D2Version::Glide3xVersionID::INVALID;

D2Version::GameVersionID D2Version::getGameVersionID() {
    if (gameVersionID == GameVersionID::INVALID) {
        std::string gameVersion = determineVersionString(L"Game.exe");

        if (gameVersion == "1.0.7.0") {
            gameVersionID = GameVersionID::VERSION_107;
        } else if (gameVersion == "1.0.8.28") {
            gameVersionID = GameVersionID::VERSION_108;
        } else if (gameVersion == "1.0.9.19") {
            gameVersionID = GameVersionID::VERSION_109;
        } else if (gameVersion == "1.0.9.20") {
            gameVersionID = GameVersionID::VERSION_109b;
        } else if (gameVersion == "1.0.9.21") {
            gameVersionID = GameVersionID::VERSION_109c;
        } else if (gameVersion == "1.0.9.22") {
            gameVersionID = GameVersionID::VERSION_109d;
        } else if (gameVersion == "1.0.10.39") {
            gameVersionID = GameVersionID::VERSION_110;
        } else if (gameVersion == "1.0.11.45") {
            gameVersionID = GameVersionID::VERSION_111;
        } else if (gameVersion == "1.0.11.46") {
            gameVersionID = GameVersionID::VERSION_111b;
        } else if (gameVersion == "1.0.12.49") {
            gameVersionID = GameVersionID::VERSION_112;
        } else if (gameVersion == "1.0.13.60") {
            gameVersionID = GameVersionID::VERSION_113c;
        } else if (gameVersion == "1.0.13.64") {
            gameVersionID = GameVersionID::VERSION_113d;
        } else if (gameVersion == "1.14.0.64") {
            gameVersionID = GameVersionID::VERSION_114a;
        } else if (gameVersion == "1.14.1.68") {
            gameVersionID = GameVersionID::VERSION_114b;
        } else if (gameVersion == "1.14.2.70") {
            gameVersionID = GameVersionID::VERSION_114c;
        } else if (gameVersion == "1.14.3.71") {
            gameVersionID = GameVersionID::VERSION_114d;
        } else {
            gameVersionID = GameVersionID::INVALID;
        }
    }
    return gameVersionID;
}

D2Version::Glide3xVersionID D2Version::getGlide3xVersionID() {
    if (glide3xVersionID == Glide3xVersionID::INVALID) {
        std::string glide3xVersion = determineVersionString(L"glide3x.dll");

        if (glide3xVersion == "1.4.4.21") {
            glide3xVersionID = Glide3xVersionID::VERSION_14e;
        } else if (glide3xVersion == "1.4.8.2") {
            glide3xVersionID = Glide3xVersionID::RESURGENCE;
        } else {
            glide3xVersionID = Glide3xVersionID::INVALID;
        }
    }
    return glide3xVersionID;
}

// Taken from StackOverflow user crashmstr
std::string D2Version::determineVersionString(LPCWSTR szVersionFile) {
    DWORD verHandle = 0;
    UINT size = 0;
    LPBYTE lpBuffer = NULL;
    DWORD verSize = GetFileVersionInfoSizeW(szVersionFile, &verHandle);

    std::string returnValue;

    if (verSize != 0) {
        WCHAR verData[verSize];

        if (GetFileVersionInfoW(szVersionFile, verHandle, verSize, verData)) {
            if (VerQueryValueW(verData, L"\\", (VOID FAR* FAR*)&lpBuffer, &size)) {
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
    }
    return returnValue;
}
