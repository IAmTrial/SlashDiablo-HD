/****************************************************************************
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

#include <Windows.h>
#include <string>
#include <sstream>
#include "D2HDStructs.h"
#include "../D2Vars.h"

#define RESOLUTION_640_TO_HD_WIDTH 1068
#define RESOLUTION_640_TO_HD_HEIGHT 600

#define RESOLUTION_800_TO_HD_WIDTH 800
#define RESOLUTION_800_TO_HD_HEIGHT 600

#define RESOLUTION_1344_TO_HD_WIDTH 800
#define RESOLUTION_1344_TO_HD_HEIGHT 600

/*
    Determines whether you want a separate MPQ file to be used to
    load the HD assets. Keep it to 0 if you are having the HD
    assets included in the Patch_D2.mpq file.
*/
#define USE_CUSTOM_MPQ_FILE 0

/*
    Determines the number of custom resolutions available. This
    includes the first two standard resolutions.
*/
#define NUMBER_OF_CUSTOM_RESOLUTIONS 4

namespace Config {
    extern std::string configPath;
    extern std::string archiveName;

    void ReadConfig();
    void ReadMainSettings();
    void ReadExperimentalSettings();

    void __stdcall WriteRegistryResolution(int mode);
    void __stdcall ReadRegistryResolution(int* mode);
}

#endif
