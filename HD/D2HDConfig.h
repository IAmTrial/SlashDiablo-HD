#pragma once

#include <Windows.h>
#include <string>
#include <sstream>
#include "D2HDStructs.h"
#include "../D2Vars.h"

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

namespace Config {
    extern std::string archiveName;

    void ReadConfig();
    void ReadMainSettings(std::string path);
    void ReadExperimentalSettings(std::string path);
}