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
 *   Defines the configuration functions that stores settings and acts as    *
 *   the parent class for derivative mods that also need to have a settings  *
 *   file.                                                                   *
 *                                                                           *
 *****************************************************************************/

#include "D2Config.h"

#include <cstdlib>
#include <regex>
#include <windows.h>

D2Config::D2Config() : D2Config(DEFAULT_CONFIG_PATH) {
}

D2Config::D2Config(const std::wstring& configPath) : configPath(configPath) {
}

bool D2Config::readBool(const std::wstring& sectionName,
                        const std::wstring& keyName, const bool defaultValue) const {
    const std::wregex VALID_BOOL_REGEX(L"false|true|0|1",
                                       std::regex_constants::ECMAScript | std::regex_constants::icase);
    const std::wregex TRUE_VALUE_REGEX(L"true|1");

    WCHAR privateProfileStringBuffer[MAX_PATH];
    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(), nullptr,
                             privateProfileStringBuffer, MAX_PATH, configPath.c_str());
    std::wstring privateProfileString(privateProfileStringBuffer);

    if (!std::regex_match(privateProfileString, VALID_BOOL_REGEX)) {
        const std::wstring defaultString = defaultValue ? L"true" : L"false";

        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   defaultString.c_str(), configPath.c_str());
        return defaultValue;
    }

    return std::regex_match(privateProfileString, TRUE_VALUE_REGEX);
}

unsigned int D2Config::readHex(const std::wstring& sectionName,
                               const std::wstring& keyName, const unsigned int defaultValue) const {
    const std::wregex HEX_REGEX(L"0x[0-9A-F]{8}",
                                std::regex_constants::ECMAScript | std::regex_constants::icase);

    WCHAR hexBuffer[MAX_PATH];
    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(), nullptr,
                             hexBuffer, MAX_PATH, configPath.c_str());

    std::wstring privateProfileString(hexBuffer);

    if (!std::regex_match(privateProfileString, HEX_REGEX)) {
        std::wostringstream ouputStream;
        ouputStream << std::showbase << std::hex << defaultValue;
        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   ouputStream.str().c_str(), configPath.c_str());
        return defaultValue;
    }

    return std::stoul(privateProfileString, nullptr, 16);
}

int D2Config::readInt(const std::wstring& sectionName,
                      const std::wstring& keyName, const int defaultValue) const {
    const std::wregex VALID_INT_REGEX(L"-?[0-9]+");

    WCHAR privateProfileStringBuffer[MAX_PATH];
    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(), nullptr,
                             privateProfileStringBuffer, MAX_PATH, configPath.c_str());

    std::wstring privateProfileString(privateProfileStringBuffer);

    if (!std::regex_match(privateProfileString, VALID_INT_REGEX)) {
        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   std::to_wstring(defaultValue).c_str(), configPath.c_str());
        return defaultValue;
    }

    return std::stol(privateProfileString);
}

std::string D2Config::readString(const std::wstring& sectionName, const std::wstring& keyName, const std::string& defaultValue) const {
    wchar_t defaultValueWideStringBuffer[MAX_PATH];
    std::mbstowcs(defaultValueWideStringBuffer, defaultValue.c_str(), MAX_PATH);
    std::wstring returnValueWideString = readWideString(sectionName, keyName, defaultValueWideStringBuffer);

    char returnValueCharStringBuffer[MAX_PATH];
    std::wcstombs(returnValueCharStringBuffer, returnValueWideString.c_str(), MAX_PATH);
    return returnValueCharStringBuffer;
}

unsigned int D2Config::readUnsignedInt(const std::wstring& sectionName,
                                       const std::wstring& keyName, const unsigned int defaultValue) const {
    const std::wregex VALID_UNSIGNED_INT_REGEX(L"[0-9]+");

    WCHAR privateProfileStringBuffer[MAX_PATH];
    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(), nullptr,
                             privateProfileStringBuffer, MAX_PATH, configPath.c_str());

    std::wstring privateProfileString(privateProfileStringBuffer);

    if (!std::regex_match(privateProfileString, VALID_UNSIGNED_INT_REGEX)) {
        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   std::to_wstring(defaultValue).c_str(), configPath.c_str());
        return defaultValue;
    }

    return std::stoul(privateProfileString);
}

std::wstring D2Config::readWideString(const std::wstring& sectionName,
                                      const std::wstring& keyName, const std::wstring& defaultValue) const {
    WCHAR privateProfileStringBuffer[MAX_PATH];
    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(), nullptr,
                             privateProfileStringBuffer, MAX_PATH, configPath.c_str());
    std::wstring privateProfileString(privateProfileStringBuffer);

    if (privateProfileString.length() == 0) {
        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   defaultValue.c_str(), configPath.c_str());
        return defaultValue;
    }

    return privateProfileString;
}

std::wstring D2Config::getConfigPath() const {
    return D2Config::configPath;
}
