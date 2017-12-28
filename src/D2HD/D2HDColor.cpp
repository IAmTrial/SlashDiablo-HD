/*****************************************************************************
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

#include <string>

D2HD::D2HDColor::D2HDColor() : D2HD::D2HDColor::D2HDColor(255, 255, 255, 255) {
}

D2HD::D2HDColor::D2HDColor(std::string colorHex) {
    unsigned int colorValue = std::stoul(colorHex, nullptr, 16);

    D2HDColor::red = (colorValue >> (8 * 3)) & 0xFF;
    D2HDColor::green = (colorValue >> (8 * 2)) & 0xFF;
    D2HDColor::blue = (colorValue >> (8 * 1)) & 0xFF;
    D2HDColor::tint = colorValue & 0xFF;
}

D2HD::D2HDColor::D2HDColor(std::wstring colorHex) {
    unsigned int colorValue = std::stoul(colorHex, nullptr, 16);

    D2HDColor::red = (colorValue >> (8 * 3)) & 0xFF;
    D2HDColor::green = (colorValue >> (8 * 2)) & 0xFF;
    D2HDColor::blue = (colorValue >> (8 * 1)) & 0xFF;
    D2HDColor::tint = colorValue & 0xFF;
}

D2HD::D2HDColor::D2HDColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char tint) {
    D2HDColor::red = red;
    D2HDColor::green = green;
    D2HDColor::blue = blue;
    D2HDColor::tint = tint;
}

unsigned int D2HD::D2HDColor::getRGBFormat() {
    unsigned int redRGB = (((unsigned int)red) << (8 * 3)) & 0xFF000000;
    unsigned int greenRGB = ((unsigned int)green << (8 * 2)) & 0x00FF0000;
    unsigned int blueRGB = ((unsigned int)blue << (8 * 1)) & 0x0000FF00;
    unsigned int tintRGB = ((unsigned int)tint) & 0x000000FF;

    return redRGB | greenRGB | blueRGB | tintRGB;
}

unsigned int D2HD::D2HDColor::getBGRFormat() {
    unsigned int redBGR = (((unsigned int)red) << (8 * 1)) & 0x0000FF00;
    unsigned int greenBGR = (((unsigned int)green) << (8 * 2)) & 0x00FF0000;
    unsigned int blueBGR = ((unsigned int)blue << (8 * 3)) & 0xFF000000;
    unsigned int tintBGR = ((unsigned int)tint) & 0x000000FF;

    return redBGR | greenBGR | blueBGR | tintBGR;
}

D2HD::D2HDColor D2HD::D2HDColor::createFromRGBFormat(unsigned int color) {
    unsigned char red = (((unsigned int)color) >> (8 * 3)) & 0xFF;
    unsigned char green = (((unsigned int)color) >> (8 * 2)) & 0xFF;
    unsigned char blue = (((unsigned int)color) >> (8 * 1)) & 0xFF;
    unsigned char tint = color & 0xFF;

    return D2HD::D2HDColor(red, green, blue, tint);
}

D2HD::D2HDColor D2HD::D2HDColor::createFromBGRFormat(unsigned int color) {
    unsigned char red = (((unsigned int)color) >> (8 * 1)) & 0xFF;
    unsigned char green = (((unsigned int)color) >> (8 * 2)) & 0xFF;
    unsigned char blue = (((unsigned int)color) >> (8 * 3)) & 0xFF;
    unsigned char tint = ((unsigned int)color) & 0xFF;

    return D2HD::D2HDColor(red, green, blue, tint);
}
