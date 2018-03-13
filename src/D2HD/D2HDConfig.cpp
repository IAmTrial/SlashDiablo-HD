/***************************************************************************
 *                                                                         *
 *   SlashDiablo HD                                                        *
 *   Copyright (C) 2017  Mir Drualga                                       *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 *-------------------------------------------------------------------------*
 *                                                                         *
 *   Defines the functions that read and write to a configuration file.    *
 *                                                                         *
 *   This file can be modified to add more configuration options.          *
 *                                                                         *
 ***************************************************************************/

#include "D2HDConfig.h"

#include <windows.h>

#include <regex>
#include <sstream>
#include <string>

#include "../DLLmain.h"
#include "D2HDColor.h"

const D2HD::D2HDColor D2HD::D2HDConfig::DEFAULT_COLOR(255, 255, 255, 255);

D2HD::D2HDConfig::D2HDConfig() : D2Config(), leftPanelBackgroundColor(255, 255,
            255, 255), leftPanelBorderColor(255, 255, 255, 255),
    rightPanelBackgroundColor(255, 255, 255, 255), rightPanelBorderColor(255, 255,
            255, 255) {
}

D2HD::D2HDConfig::D2HDConfig(const std::wstring& configPath) : D2Config(
        configPath), leftPanelBackgroundColor(255, 255, 255, 255),
    leftPanelBorderColor(255, 255, 255, 255), rightPanelBackgroundColor(255, 255,
            255, 255), rightPanelBorderColor(255, 255, 255, 255) {
}

void D2HD::D2HDConfig::readSettings() {
    enableMod = readBool(MAIN_SETTING_SECTION_NAME, L"Enable Mod",
                         DEFAULT_ENABLE_MOD);

    // Add "Resolution Mode" entry after "Enable Mod"
    int discarded = 0;
    D2HD::getConfigResolution(&discarded);

    if constexpr (D2HD::D2HDConfig::ALLOW_LOAD_MPQ_ARCHIVE) {
        enableArchive = readBool(MAIN_SETTING_SECTION_NAME, L"Enable Archive",
                                 DEFAULT_ENABLE_ARCHIVE);
        archiveName = readString(MAIN_SETTING_SECTION_NAME, L"Archive Name",
                                 DEFAULT_ARCHIVE_NAME);
    }

    if constexpr (D2HD::D2HDConfig::ALLOW_CUSTOM_RESOLUTION) {
        enableCustomResolution = readBool(MAIN_SETTING_SECTION_NAME,
                                          L"Enable Custom Resolution", DEFAULT_ENABLE_CUSTOM_RESOLUTION);

        // Enforce resolution limits on the custom resolution.
        std::wostringstream widthTextStream;
        widthTextStream << L"Custom Width (Can't be larger than " << MAXIMUM_WIDTH <<
                        ')';
        customWidth = readInt(MAIN_SETTING_SECTION_NAME, widthTextStream.str().c_str(),
                              DEFAULT_CUSTOM_WIDTH);

        if (customWidth < MINIMUM_WIDTH || customWidth > MAXIMUM_WIDTH) {
            customWidth = DEFAULT_CUSTOM_WIDTH;
        }

        std::wostringstream heightTextStream;
        heightTextStream << L"Custom Height (Can't be larger than " << MAXIMUM_HEIGHT <<
                         ')';
        customHeight = readInt(MAIN_SETTING_SECTION_NAME,
                               heightTextStream.str().c_str(), DEFAULT_CUSTOM_HEIGHT);

        if (customHeight < MINIMUM_HEIGHT || customWidth > MAXIMUM_HEIGHT) {
            customHeight = DEFAULT_CUSTOM_HEIGHT;
        }

        if (isEnableCustomResolution()) {
            D2HD::D2HDResolution::getResolutions().push_back(D2HD::D2HDResolution(
                        customWidth, customHeight));
        }
    }

    leftPanelBackgroundColor = readColor(MAIN_SETTING_SECTION_NAME,
                                         L"Left Panel Background Color", DEFAULT_COLOR);
    leftPanelBorderColor = readColor(MAIN_SETTING_SECTION_NAME,
                                     L"Left Panel Border Color", DEFAULT_COLOR);
    rightPanelBorderColor = readColor(MAIN_SETTING_SECTION_NAME,
                                      L"Right Panel Border Color", DEFAULT_COLOR);
    rightPanelBackgroundColor = readColor(MAIN_SETTING_SECTION_NAME,
                                          L"Right Panel Background Color", DEFAULT_COLOR);

    enable800ControlPanel = readBool(MAIN_SETTING_SECTION_NAME,
                                     L"Enable 800x600 Style Control Panel", DEFAULT_ENABLE_800_CONTROL_PANEL);
    enableD2MRBackgroundRibbon = readBool(MAIN_SETTING_SECTION_NAME,
                                          L"Enable D2MR Panel Background Ribbon", DEFAULT_ENABLE_D2MR_BACKGROUND_RIBBON);
    enableD2MRPanelBorderStyle = readBool(MAIN_SETTING_SECTION_NAME,
                                          L"Enable D2MR Panel Border Style", DEFAULT_ENABLE_D2MR_PANEL_BORDER_STYLE);
    flipD2MRControlPanel = readBool(MAIN_SETTING_SECTION_NAME,
                                    L"Flip D2MR Bottom Control Panel", DEFAULT_FLIP_D2MR_CONTROL_PANEL);
}

D2HD::D2HDColor D2HD::D2HDConfig::readColor(const std::wstring& sectionName,
        const std::wstring& keyName, const D2HD::D2HDColor& defaultValue) const {
    return D2HD::D2HDColor::createFromRGBFormat(readHex(sectionName, keyName,
            defaultValue.getRGBFormat()));
}

bool D2HD::D2HDConfig::isEnableMod() const {
    return enableMod;
}

bool D2HD::D2HDConfig::isEnableCustomResolution() const {
    return enableCustomResolution;
}

int D2HD::D2HDConfig::getCustomWidth() const {
    return customWidth;
}

int D2HD::D2HDConfig::getCustomHeight() const {
    return customHeight;
}

bool D2HD::D2HDConfig::isEnable800ControlPanel() const {
    return enable800ControlPanel;
}

bool D2HD::D2HDConfig::isEnableD2MRBackgroundRibbon() const {
    return enableD2MRBackgroundRibbon;
}

bool D2HD::D2HDConfig::isEnableD2MRPanelBorderStyle() const {
    return enableD2MRPanelBorderStyle;
}

bool D2HD::D2HDConfig::isFlipD2MRControlPanel() const {
    return flipD2MRControlPanel;
}

D2HD::D2HDColor D2HD::D2HDConfig::getLeftPanelBackgroundColor() const {
    return leftPanelBackgroundColor;
}

D2HD::D2HDColor D2HD::D2HDConfig::getLeftPanelBorderColor() const {
    return leftPanelBorderColor;
}

D2HD::D2HDColor D2HD::D2HDConfig::getRightPanelBackgroundColor() const {
    return rightPanelBackgroundColor;
}

D2HD::D2HDColor D2HD::D2HDConfig::getRightPanelBorderColor() const {
    return rightPanelBorderColor;
}

bool D2HD::D2HDConfig::isEnableArchive() const {
    return enableArchive;
}

std::string D2HD::D2HDConfig::getArchiveName() const {
    return archiveName;
}

void __stdcall D2HD::getConfigResolution(int* mode) {
    *mode = config.readInt(D2HD::D2HDConfig::MAIN_SETTING_SECTION_NAME,
                           L"Resolution Mode",
                           D2HD::D2HDConfig::DEFAULT_RESOLUTION_MODE);

    if (*mode < 0
            || (unsigned int)*mode >= D2HD::D2HDResolution::getResolutions().size()) {
        *mode = 0;
    }
}

void __stdcall D2HD::setConfigResolution(int mode) {
    WritePrivateProfileStringW(D2HD::D2HDConfig::MAIN_SETTING_SECTION_NAME,
                               L"Resolution Mode", std::to_wstring(mode).c_str(),
                               config.getConfigPath().c_str());
}
