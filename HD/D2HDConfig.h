#pragma once

#include <Windows.h>
#include <string>
#include <sstream>
#include "D2HDStructs.h"
#include "../D2Vars.h"

/*
    It is here that mod-makers can modify macros to apply acceptable
    settings for their users.
*/

/*
    To define your own custom replacement for 640x480, simply
    change the values of the definition below.

    I highly do NOT recommend changing the 800x600 values. The
    values you place are overriden in the D2GDI code and messes
    everything up.
*/

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