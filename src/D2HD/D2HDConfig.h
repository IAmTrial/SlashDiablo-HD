/*****************************************************************************
 *                                                                           *
 *  SlashDiablo HD                                                           *
 *  Copyright (C) 2017  Mir Drualga                                          *
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
 *   Declares functions that read and write to a configuration file.         *
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

    // Set to false if assets are in Patch_D2.mpq, true if using external MPQ.
    static constexpr bool ALLOW_LOAD_MPQ_ARCHIVE = true;
    static constexpr bool ALLOW_CUSTOM_RESOLUTION = true;

    static constexpr bool DEFAULT_ENABLE_ARCHIVE = true;
    static constexpr const char* DEFAULT_ARCHIVE_NAME = "SlashDiabloHD.mpq";
    static constexpr bool DEFAULT_ENABLE_MOD = true;
    static constexpr unsigned int DEFAULT_RESOLUTION_MODE = 3;
    static constexpr bool DEFAULT_ENABLE_CUSTOM_RESOLUTION = false;
    static constexpr int DEFAULT_CUSTOM_WIDTH = 856;
    static constexpr int DEFAULT_CUSTOM_HEIGHT = 480;
    static constexpr int MINIMUM_WIDTH = 640;
    static constexpr int MINIMUM_HEIGHT = 480;
    static constexpr int MAXIMUM_WIDTH = 1068;
    static constexpr int MAXIMUM_HEIGHT = 600;
    static constexpr unsigned int DEFAULT_COLOR_HEX = 0xFFFFFFFF;
    static const D2HD::D2HDColor DEFAULT_COLOR;

    static constexpr bool DEFAULT_ENABLE_800_CONTROL_PANEL = true;
    static constexpr bool DEFAULT_ENABLE_D2MR_BACKGROUND_RIBBON = true;
    static constexpr bool DEFAULT_ENABLE_D2MR_PANEL_BORDER_STYLE = false;
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
