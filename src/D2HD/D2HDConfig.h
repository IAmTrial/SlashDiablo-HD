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

#include <windows.h>

#include <string>

#include "D2HDColor.h"

namespace D2HD {
namespace Config {
const std::wstring CONFIG_PATH = L"./SlashDiablo-HD.ini";
const std::wstring MAIN_SETTING_SECTION_NAME = L"Settings";

const unsigned int DEFAULT_RESOLUTION_MODE = 3;

const bool DEFAULT_ENABLE_CUSTOM_RESOLUTION = true;
const int DEFAULT_CUSTOM_WIDTH = 856;
const int DEFAULT_CUSTOM_HEIGHT = 480;
const int MAXIMUM_WIDTH = 1068;
const int MAXIMUM_HEIGHT = 600;
const unsigned int DEFAULT_COLOR = 0xFFFFFFFF;

const bool DEFAULT_ENABLE_800_CONTROL_PANEL = true;
const bool DEFAULT_ENABLE_D2MR_BACKGROUND_RIBBON = true;
const bool DEFAULT_ENABLE_D2MR_PANEL_BORDER_STYLE = true;
const bool DEFAULT_FLIP_D2MR_CONTROL_PANEL = true;

extern bool enableCustomResolution;
extern int customWidth;
extern int customHeight;

extern bool enable800ControlPanel;
extern bool enableD2MRBackgroundRibbon;
extern bool enableD2MRPanelBorderStyle;
extern bool flipD2MRControlPanel;

extern D2HD::D2HDColor leftPanelBackgroundColor;
extern D2HD::D2HDColor leftPanelBorderColor;
extern D2HD::D2HDColor rightPanelBackgroundColor;
extern D2HD::D2HDColor rightPanelBorderColor;

void readConfig();

extern "C" void __stdcall getConfigResolution(int* mode);
extern "C" void __stdcall getConfigResolutionInterception(int* mode);
extern "C" void __stdcall setConfigResolution(int mode);
extern "C" void __stdcall setConfigResolutionInterception(int mode);
}
}

#endif
