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
 *   Declares the configuration functions that stores settings and acts as   *
 *   the parent class for derivative mods that also need to have a settings  *
 *   file.                                                                   *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef D2CONFIG_H
#define D2CONFIG_H

#include <string>

class D2Config {
public:
    static constexpr const wchar_t* DEFAULT_CONFIG_PATH =
        L"./SlashDiablo-Tools.ini";

    D2Config();
    D2Config(const std::wstring& configPath);

    bool readBool(const std::wstring& sectionName, const std::wstring& keyName,
                  const bool defaultValue) const;
    unsigned int readHex(const std::wstring& sectionName,
                         const std::wstring& keyName, const unsigned int defaultValue) const;
    int readInt(const std::wstring& sectionName, const std::wstring& keyName,
                const int defaultValue) const;
    std::string readString(const std::wstring& sectionName,
                           const std::wstring& keyName, const std::string& defaultValue) const;
    unsigned int readUnsignedInt(const std::wstring& sectionName,
                                 const std::wstring& keyName, const unsigned int defaultValue) const;
    std::wstring readWideString(const std::wstring& sectionName,
                                const std::wstring& keyName, const std::wstring& defaultValue) const;

    virtual void readSettings() = 0;
    std::wstring getConfigPath() const;

private:
    std::wstring configPath;
};

#endif // D2CONFIG_H
