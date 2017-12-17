/****************************************************************************
*                                                                           *
*   D2HDStructs.cpp                                                         *
*   Copyright (C) 2017 Mir Drualga                                          *
*                                                                           *
*   D2Ex: Copyright (c) 2011-2014 Bartosz Jankowski                         *
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
*   Defines custom structs that are used by this mod.                       *
*                                                                           *
*****************************************************************************/

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
