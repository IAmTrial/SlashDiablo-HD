/*****************************************************************************
 *                                                                           *
 *   D2Config.cpp                                                            *
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
 *   Defines the configuration functions that stores settings and acts as    *
 *   the parent class for derivative mods that also need to have a settings  *
 *   file.                                                                   *
 *                                                                           *
 *****************************************************************************/

#include "D2Config.h"

#include <regex>

#include <windows.h>

const std::wstring D2Config::CONFIG_PATH  = L"./SlashDiablo-Tools.ini";

bool D2Config::readBool(const std::wstring& sectionName,
                        const std::wstring& keyName, const bool defaultValue) {
    const std::wregex VALID_BOOL_REGEX(L"false|true|0|1",
                                       std::regex_constants::ECMAScript | std::regex_constants::icase);
    const std::wregex TRUE_VALUE_REGEX(L"true|1");

    WCHAR privateProfileStringBuffer[MAX_PATH];
    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(), nullptr,
                             privateProfileStringBuffer, MAX_PATH, D2Config::CONFIG_PATH.c_str());
    std::wstring privateProfileString(privateProfileStringBuffer);

    if (!std::regex_match(privateProfileString, VALID_BOOL_REGEX)) {
        const std::wstring defaultString = defaultValue ? L"true" : L"false";

        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   defaultString.c_str(), D2Config::CONFIG_PATH.c_str());
        return defaultValue;
    }

    return std::regex_match(privateProfileString, TRUE_VALUE_REGEX);
}

unsigned int D2Config::readHex(const std::wstring& sectionName,
                               const std::wstring& keyName, const unsigned int defaultValue) {
    const std::wregex HEX_REGEX(L"0x[0-9A-F]{8}",
                                std::regex_constants::ECMAScript | std::regex_constants::icase);

    WCHAR hexBuffer[MAX_PATH];
    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(), nullptr,
                             hexBuffer, MAX_PATH, D2Config::CONFIG_PATH.c_str());

    std::wstring privateProfileString(hexBuffer);

    if (!std::regex_match(privateProfileString, HEX_REGEX)) {
        std::wostringstream ouputStream;
        ouputStream << std::showbase << std::hex << defaultValue;
        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   ouputStream.str().c_str(), D2Config::CONFIG_PATH.c_str());
        return defaultValue;
    }

    return std::stoul(privateProfileString);
}

int D2Config::readInt(const std::wstring& sectionName,
                      const std::wstring& keyName, const int defaultValue) {
    const std::wregex VALID_INT_REGEX(L"-?[0-9]+");

    WCHAR privateProfileStringBuffer[MAX_PATH];
    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(), nullptr,
                             privateProfileStringBuffer, MAX_PATH, D2Config::CONFIG_PATH.c_str());

    std::wstring privateProfileString(privateProfileStringBuffer);

    if (!std::regex_match(privateProfileString, VALID_INT_REGEX)) {
        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   std::to_wstring(defaultValue).c_str(), D2Config::CONFIG_PATH.c_str());
        return defaultValue;
    }

    return std::stol(privateProfileString);
}

unsigned int D2Config::readUnsignedInt(const std::wstring& sectionName,
                                       const std::wstring& keyName, const unsigned int defaultValue) {
    const std::wregex VALID_UNSIGNED_INT_REGEX(L"[0-9]+");

    WCHAR privateProfileStringBuffer[MAX_PATH];
    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(), nullptr,
                             privateProfileStringBuffer, MAX_PATH, D2Config::CONFIG_PATH.c_str());

    std::wstring privateProfileString(privateProfileStringBuffer);

    if (!std::regex_match(privateProfileString, VALID_UNSIGNED_INT_REGEX)) {
        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   std::to_wstring(defaultValue).c_str(), D2Config::CONFIG_PATH.c_str());
        return defaultValue;
    }

    return std::stoul(privateProfileString);
}

std::wstring D2Config::readWideString(const std::wstring& sectionName,
                                      const std::wstring& keyName, const std::wstring& defaultValue) {
    WCHAR privateProfileStringBuffer[MAX_PATH];
    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(), nullptr,
                             privateProfileStringBuffer, MAX_PATH, D2Config::CONFIG_PATH.c_str());
    std::wstring privateProfileString(privateProfileStringBuffer);

    if (privateProfileString.length() == 0) {
        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   defaultValue.c_str(), D2Config::CONFIG_PATH.c_str());
        return defaultValue;
    }

    return privateProfileString;
}
