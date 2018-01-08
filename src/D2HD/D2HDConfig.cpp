/*****************************************************************************
 *                                                                           *
 *   D2HDConfig.cpp                                                          *
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
 *   Defines the functions that read and write to a configuration file.      *
 *                                                                           *
 *   This file can be modified to add more configuration options.            *
 *                                                                           *
 *****************************************************************************/

#include "D2HDConfig.h"

#include <windows.h>

#include <regex>
#include <sstream>
#include <string>

#include "D2HDColor.h"

bool D2HD::Config::enableCustomResolution;
int D2HD::Config::customWidth;
int D2HD::Config::customHeight;

bool D2HD::Config::enable800ControlPanel;
bool D2HD::Config::enableD2MRBackgroundRibbon;
bool D2HD::Config::enableD2MRPanelBorderStyle;
bool D2HD::Config::flipD2MRControlPanel;

D2HD::D2HDColor D2HD::Config::leftPanelBackgroundColor;
D2HD::D2HDColor D2HD::Config::leftPanelBorderColor;
D2HD::D2HDColor D2HD::Config::rightPanelBackgroundColor;
D2HD::D2HDColor D2HD::Config::rightPanelBorderColor;

void readMainSettings();
D2HD::D2HDColor readColor(std::wstring sectionName, std::wstring keyName);
bool readBool(std::wstring sectionName, std::wstring keyName,
              bool defaultValue);
unsigned int readUnsignedInt(std::wstring sectionName, std::wstring keyName,
                             unsigned int defaultValue);
int readInt(std::wstring sectionName, std::wstring keyName, int defaultValue);

void D2HD::Config::readConfig() {
    readMainSettings();
}

void readMainSettings() {
    D2HD::Config::enableCustomResolution = readBool(
            D2HD::Config::MAIN_SETTING_SECTION_NAME, L"Enable Custom Resolution",
            D2HD::Config::DEFAULT_ENABLE_CUSTOM_RESOLUTION);

    std::wostringstream widthTextStream;
    widthTextStream << L"Custom Width (Can't be larger than " <<
                    D2HD::Config::MAXIMUM_WIDTH << ')';
    D2HD::Config::customWidth = readInt(D2HD::Config::MAIN_SETTING_SECTION_NAME,
                                        widthTextStream.str().c_str(),
                                        D2HD::Config::DEFAULT_CUSTOM_WIDTH);

    std::wostringstream heightTextStream;
    heightTextStream << L"Custom Height (Can't be larger than " <<
                     D2HD::Config::MAXIMUM_HEIGHT << ')';
    D2HD::Config::customHeight = readInt(D2HD::Config::MAIN_SETTING_SECTION_NAME,
                                         heightTextStream.str().c_str(),
                                         D2HD::Config::DEFAULT_CUSTOM_HEIGHT);

    D2HD::Config::leftPanelBackgroundColor = readColor(
                D2HD::Config::MAIN_SETTING_SECTION_NAME, L"Left Panel Background Color");
    D2HD::Config::leftPanelBorderColor = readColor(
            D2HD::Config::MAIN_SETTING_SECTION_NAME, L"Left Panel Border Color");
    D2HD::Config::rightPanelBorderColor = readColor(
            D2HD::Config::MAIN_SETTING_SECTION_NAME, L"Right Panel Border Color");
    D2HD::Config::rightPanelBackgroundColor = readColor(
                D2HD::Config::MAIN_SETTING_SECTION_NAME, L"Right Panel Background Color");

    D2HD::Config::enable800ControlPanel = readBool(
            D2HD::Config::MAIN_SETTING_SECTION_NAME, L"Enable 800x600 Style Control Panel",
            D2HD::Config::DEFAULT_ENABLE_800_CONTROL_PANEL);
    D2HD::Config::enableD2MRBackgroundRibbon = readBool(
                D2HD::Config::MAIN_SETTING_SECTION_NAME, L"Enable D2MR Panel Background Ribbon",
                D2HD::Config::DEFAULT_ENABLE_D2MR_BACKGROUND_RIBBON);
    D2HD::Config::enableD2MRPanelBorderStyle = readBool(
                D2HD::Config::MAIN_SETTING_SECTION_NAME, L"Enable D2MR Panel Border Style",
                D2HD::Config::DEFAULT_ENABLE_D2MR_PANEL_BORDER_STYLE);
    D2HD::Config::flipD2MRControlPanel = readBool(
            D2HD::Config::MAIN_SETTING_SECTION_NAME, L"Flip D2MR Bottom Control Panel",
            D2HD::Config::DEFAULT_FLIP_D2MR_CONTROL_PANEL);
}

void __stdcall D2HD::Config::getConfigResolution(int* mode) {
    *mode = (int) readUnsignedInt(D2HD::Config::MAIN_SETTING_SECTION_NAME,
                                  L"Resolution Mode", D2HD::Config::DEFAULT_RESOLUTION_MODE);
}

void __stdcall D2HD::Config::setConfigResolution(int mode) {
    WritePrivateProfileStringW(D2HD::Config::MAIN_SETTING_SECTION_NAME.c_str(),
                               L"Resolution Mode", std::to_wstring(mode).c_str(),
                               D2HD::Config::CONFIG_PATH.c_str());
}

D2HD::D2HDColor readColor(std::wstring sectionName, std::wstring keyName) {
    WCHAR colorBuffer[MAX_PATH];
    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(), nullptr,
                             colorBuffer, MAX_PATH, D2HD::Config::CONFIG_PATH.c_str());

    std::wstring colorString(colorBuffer);
    const std::wregex HEX_REGEX(L"0x[0-9A-F]{8}",
                                std::regex_constants::ECMAScript | std::regex_constants::icase);

    if (!std::regex_match(colorString, HEX_REGEX)) {
        std::wostringstream ouputStream;
        ouputStream << std::showbase << std::hex << D2HD::Config::DEFAULT_COLOR;
        colorString = ouputStream.str();
        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   colorString.c_str(), D2HD::Config::CONFIG_PATH.c_str());
    }

    return D2HD::D2HDColor(colorString);
}

bool readBool(std::wstring sectionName, std::wstring keyName,
              bool defaultValue) {
    std::wstring defaultString = defaultValue ? L"true" : L"false";
    WCHAR privateProfileStringBuffer[MAX_PATH];

    const std::wregex VALID_BOOL_REGEX(L"false|true|0|1",
                                       std::regex_constants::ECMAScript | std::regex_constants::icase);

    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                             nullptr, privateProfileStringBuffer,
                             MAX_PATH, D2HD::Config::CONFIG_PATH.c_str());
    std::wstring privateProfileString(privateProfileStringBuffer);

    if (!std::regex_match(privateProfileString, VALID_BOOL_REGEX)) {
        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   defaultString.c_str(),
                                   D2HD::Config::CONFIG_PATH.c_str());
        return defaultValue;
    }

    const std::wregex TRUE_REGEX(L"true|1");
    return std::regex_match(privateProfileString, TRUE_REGEX);
}

unsigned int readUnsignedInt(std::wstring sectionName, std::wstring keyName,
                             unsigned int defaultValue) {
    WCHAR privateProfileStringBuffer[MAX_PATH];
    std::wregex VALID_UNSIGNED_INT_REGEX(L"[0-9]+");

    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                             nullptr, privateProfileStringBuffer,
                             MAX_PATH, D2HD::Config::CONFIG_PATH.c_str());

    std::wstring privateProfileString(privateProfileStringBuffer);

    if (!std::regex_match(privateProfileString, VALID_UNSIGNED_INT_REGEX)) {
        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   std::to_wstring(defaultValue).c_str(), D2HD::Config::CONFIG_PATH.c_str());
        return defaultValue;
    }

    return std::stoul(privateProfileString);
}

int readInt(std::wstring sectionName, std::wstring keyName, int defaultValue) {
    WCHAR privateProfileStringBuffer[MAX_PATH];
    std::wregex VALID_INT_REGEX(L"-?[0-9]+");

    GetPrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                             nullptr, privateProfileStringBuffer,
                             MAX_PATH, D2HD::Config::CONFIG_PATH.c_str());

    std::wstring privateProfileString(privateProfileStringBuffer);

    if (!std::regex_match(privateProfileString, VALID_INT_REGEX)) {
        WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(),
                                   std::to_wstring(defaultValue).c_str(), D2HD::Config::CONFIG_PATH.c_str());
        return defaultValue;
    }

    return std::stol(privateProfileString);
}
