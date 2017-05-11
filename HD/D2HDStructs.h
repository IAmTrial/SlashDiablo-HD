#include <Windows.h>
#include <string>

#pragma once

namespace Color {
    struct RGBFormat {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned char tint;
    };

    DWORD FormatRGBtoBGR(RGBFormat* format);
    DWORD FormatRGBtoBGR(DWORD color);
    DWORD FormatRGBtoBGR(std::string color);
}