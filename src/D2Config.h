/*****************************************************************************
 *                                                                           *
 *   D2Config.h                                                              *
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
    static const std::wstring DEFAULT_CONFIG_PATH;

    D2Config();
    D2Config(const std::wstring& configPath);

    bool readBool(const std::wstring& sectionName, const std::wstring& keyName,
                  const bool defaultValue) const;
    unsigned int readHex(const std::wstring& sectionName,
                         const std::wstring& keyName, const unsigned int defaultValue) const;
    int readInt(const std::wstring& sectionName, const std::wstring& keyName,
                const int defaultValue) const;
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
