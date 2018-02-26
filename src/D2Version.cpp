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
 *   detection. You must include Version.lib in your linker settings!        *
 *                                                                           *
 *****************************************************************************/

#include "D2Version.h"

#include <windows.h>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

D2Version::GameVersion D2Version::getGameVersion() {
    static GameVersion gameVersion = getGameVersion(determineVersionString(L"Game.exe"));
    return gameVersion;
}

D2Version::GameVersion D2Version::getGameVersion(std::string_view versionString) {
    static std::unordered_map<std::string_view, D2Version::GameVersion> stringToGameVersion = {
        { "1.0.7.0", GameVersion::VERSION_107 }, { "1.0.8.28", GameVersion::VERSION_108 },
        { "1.0.9.19", GameVersion::VERSION_109 }, { "1.0.9.20", GameVersion::VERSION_109b },
        { "1.0.9.21", GameVersion::VERSION_109c }, { "1.0.9.22", GameVersion::VERSION_109d },
        { "1.0.10.39", GameVersion::VERSION_110 }, { "1.0.11.45", GameVersion::VERSION_111 },
        { "1.0.11.46", GameVersion::VERSION_111b }, { "1.0.12.49", GameVersion::VERSION_112 },
        { "1.0.13.60", GameVersion::VERSION_113c }, { "1.0.13.64", GameVersion::VERSION_113d },
        { "1.14.0.64", GameVersion::VERSION_114a }, { "1.14.1.68", GameVersion::VERSION_114b },
        { "1.14.2.70", GameVersion::VERSION_114c }, { "1.14.3.71", GameVersion::VERSION_114d }
    };

    return (stringToGameVersion.count(versionString) == 1) ?
            stringToGameVersion.at(versionString) : GameVersion::INVALID;
}

bool D2Version::isGameVersion114Plus() {
    static std::unordered_set<GameVersion> versions114Plus = {
        GameVersion::VERSION_114a, GameVersion::VERSION_114b,
        GameVersion::VERSION_114c, GameVersion::VERSION_114d
    };

    return versions114Plus.count(getGameVersion()) == 1;
}

D2Version::Glide3xVersion D2Version::getGlide3xVersion() {
    static Glide3xVersion glide3xVersion = getGlide3xVersion(determineVersionString(L"glide3x.dll"));
    return glide3xVersion;
}

D2Version::Glide3xVersion D2Version::getGlide3xVersion(std::string_view versionString) {
    static std::unordered_map<std::string_view, D2Version::Glide3xVersion> stringToGlide3xVersion = {
        { "1.4.4.21", Glide3xVersion::VERSION_14e }, { "1.4.8.3", Glide3xVersion::RESURGENCE }
    };

    return (stringToGlide3xVersion.count(versionString) == 1) ?
            stringToGlide3xVersion.at(versionString) : Glide3xVersion::INVALID;
}

// Taken from StackOverflow user crashmstr
std::string D2Version::determineVersionString(std::wstring_view filePath) {
    DWORD verHandle = 0;
    UINT size = 0;
    LPBYTE lpBuffer = nullptr;
    DWORD verSize = GetFileVersionInfoSizeW(filePath.data(), &verHandle);

    std::string returnValue;

    if (verSize != 0) {
        std::unique_ptr<WCHAR[]> verData(new WCHAR[verSize]);

        if (GetFileVersionInfoW(filePath.data(), verHandle, verSize, verData.get())) {
            if (VerQueryValueW(verData.get(), L"\\", (VOID FAR * FAR*)&lpBuffer, &size)) {
                if (size > 0) {
                    VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;

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
