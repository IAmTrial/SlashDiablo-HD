/*****************************************************************************
 *                                                                           *
 *   D2HDConfig.h                                                            *
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
 *   Declares functions that read and write to a configuration file.         *
 *   By default, this file is D2HD.ini.                                      *
 *                                                                           *
 *   It is here that mod-makers can modify macros to apply acceptable        *
 *   settings for their users. One such important setting specifies the      *
 *   number of custom resolutions available, including the first two         *
 *   standard resolutions.                                                   *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef D2HDCONFIG_H
#define D2HDCONFIG_H

#include "../D2Config.h"

#include <string>
#include <windows.h>

#include "D2HDColor.h"

namespace D2HD {
class D2HDConfig : public D2Config {
public:
    static constexpr const wchar_t* MAIN_SETTING_SECTION_NAME = L"SlashDiablo-HD";
    static constexpr const bool DEFAULT_ENABLE_ARCHIVE = true;
    static constexpr const char* DEFAULT_ARCHIVE_NAME = "SlashDiabloHD.mpq";
    static constexpr bool DEFAULT_ENABLE_MOD = true;
    static constexpr unsigned int DEFAULT_RESOLUTION_MODE = 3;
    static constexpr bool DEFAULT_ENABLE_CUSTOM_RESOLUTION = false;
    static constexpr int DEFAULT_CUSTOM_WIDTH = 856;
    static constexpr int DEFAULT_CUSTOM_HEIGHT = 480;
    static constexpr int MAXIMUM_WIDTH = 1068;
    static constexpr int MAXIMUM_HEIGHT = 600;
    static constexpr unsigned int DEFAULT_COLOR_HEX = 0xFFFFFFFF;
    static const D2HD::D2HDColor DEFAULT_COLOR;

    static constexpr bool DEFAULT_ENABLE_800_CONTROL_PANEL = true;
    static constexpr bool DEFAULT_ENABLE_D2MR_BACKGROUND_RIBBON = true;
    static constexpr bool DEFAULT_ENABLE_D2MR_PANEL_BORDER_STYLE = true;
    static constexpr bool DEFAULT_FLIP_D2MR_CONTROL_PANEL = true;

    D2HDConfig();
    D2HDConfig(const std::wstring& configPath);

    D2HD::D2HDColor readColor(const std::wstring& sectionName,
                              const std::wstring& keyName, const D2HD::D2HDColor& defaultValue) const;
    virtual void readSettings();

    bool isEnableMod() const;

    bool isEnableCustomResolution() const;
    int getCustomWidth() const;
    int getCustomHeight() const;

    bool isEnable800ControlPanel() const;
    bool isEnableD2MRBackgroundRibbon() const;
    bool isEnableD2MRPanelBorderStyle() const;
    bool isFlipD2MRControlPanel() const;

    D2HD::D2HDColor getLeftPanelBackgroundColor() const;
    D2HD::D2HDColor getLeftPanelBorderColor() const;
    D2HD::D2HDColor getRightPanelBackgroundColor() const;
    D2HD::D2HDColor getRightPanelBorderColor() const;

    bool isEnableArchive() const;
    std::string getArchiveName() const;

private:
    bool enableMod;
    bool enableCustomResolution;
    int customWidth;
    int customHeight;

    bool enable800ControlPanel;
    bool enableD2MRBackgroundRibbon;
    bool enableD2MRPanelBorderStyle;
    bool flipD2MRControlPanel;

    D2HD::D2HDColor leftPanelBackgroundColor;
    D2HD::D2HDColor leftPanelBorderColor;
    D2HD::D2HDColor rightPanelBackgroundColor;
    D2HD::D2HDColor rightPanelBorderColor;

    bool enableArchive;
    std::string archiveName;
};

extern "C"  void __stdcall getConfigResolution(int* mode);
extern "C"  void __stdcall getConfigResolutionInterception(int* mode);
extern "C"  void __stdcall setConfigResolution(int mode);
extern "C"  void __stdcall setConfigResolutionInterception(int mode);
}

#endif
