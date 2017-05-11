#include "D2HDStructs.h"

DWORD Color::FormatRGBtoBGR(RGBFormat* format) {
    DWORD red = ((DWORD)format->red) << (4 * 4);
    DWORD green = (DWORD)format->green;
    DWORD blue = (DWORD)format->blue >> (4 * 4);
    DWORD tint = (DWORD)format->tint;

    return red | green | blue | tint;
}

DWORD Color::FormatRGBtoBGR(DWORD color) {
    DWORD red = (color >> (4 * 4)) & 0x0000FF00;
    DWORD green = color & 0x00FF0000;
    DWORD blue = (color << (4 * 4)) & 0xFF000000;
    DWORD tint = tint & 0x000000FF;

    return red | green | blue | tint;
}

DWORD Color::FormatRGBtoBGR(std::string color) {
    DWORD value = std::stoul(color, NULL, 16);
    return FormatRGBtoBGR(value);
}
