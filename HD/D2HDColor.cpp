/****************************************************************************
*                                                                           *
*   D2HDColor.cpp                                                           *
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
*   Defines a custom class that performs conversions of Diablo II color     *
*   representations of BGR to RGB, and vice versa.                          *
*                                                                           *
*****************************************************************************/

#include "D2HDColor.h"

#include <Windows.h>
#include <sstream>
#include <string>

HD::D2HDColor::D2HDColor() : HD::D2HDColor::D2HDColor(255, 255, 255, 255) {
}

HD::D2HDColor::D2HDColor(std::string color) {
    DWORD colorValue = std::stoul(color, NULL, 16);
    
    D2HDColor::red = (colorValue >> (8 * 3)) & 0xFF;
    D2HDColor::green = (colorValue >> (8 * 2)) & 0xFF;
    D2HDColor::blue = (colorValue >> (8 * 1)) & 0xFF;
    D2HDColor::tint = colorValue & 0xFF;
}

HD::D2HDColor::D2HDColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char tint) {
    D2HDColor::red = red;
    D2HDColor::green = green;
    D2HDColor::blue = blue;
    D2HDColor::tint = tint;
}

DWORD HD::D2HDColor::getRGBFormat() {
    DWORD redRGB = (((DWORD)red) << (8 * 3)) & 0xFF000000;
    DWORD greenRGB = ((DWORD)green << (8 * 2)) & 0x00FF0000;
    DWORD blueRGB = ((DWORD)blue << (8 * 1)) & 0x0000FF00;
    DWORD tintRGB = ((DWORD)tint) & 0x000000FF;

    return redRGB | greenRGB | blueRGB | tintRGB;
}

DWORD HD::D2HDColor::getBGRFormat() {
    DWORD redBGR = (((DWORD)red) << (8 * 1)) & 0x0000FF00;
    DWORD greenBGR = (((DWORD)green) << (8 * 2)) & 0x00FF0000;
    DWORD blueBGR = ((DWORD)blue << (8 * 3)) & 0xFF000000;
    DWORD tintBGR = ((DWORD)tint) & 0x000000FF;

    return redBGR | greenBGR | blueBGR | tintBGR;
}

HD::D2HDColor HD::D2HDColor::createFromRGBFormat(DWORD color) {
    unsigned char red = (((DWORD)color) >> (8 * 3)) & 0xFF;
    unsigned char green = (((DWORD)color) >> (8 * 2)) & 0xFF;
    unsigned char blue = (((DWORD)color) >> (8 * 1)) & 0xFF;
    unsigned char tint = color & 0xFF;

    return HD::D2HDColor(red, green, blue, tint);
}

HD::D2HDColor HD::D2HDColor::createFromBGRFormat(DWORD color) {
    unsigned char red = (((DWORD)color) >> (8 * 1)) & 0xFF;
    unsigned char green = (((DWORD)color) >> (8 * 2)) & 0xFF;
    unsigned char blue = (((DWORD)color) >> (8 * 3)) & 0xFF;
    unsigned char tint = ((DWORD)color) & 0xFF;

    return HD::D2HDColor(red, green, blue, tint);
}
