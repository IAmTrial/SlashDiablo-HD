/*****************************************************************************
 *                                                                           *
 *   D2HDColor.h                                                             *
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
 *   Declares a custom class that performs conversions of Diablo II color    *
 *   representations of BGR to RGB, and vice versa.                          *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef D2HDCOLOR_H
#define D2HDCOLOR_H

#include <string>

namespace D2HD {
class D2HDColor {
public:
    D2HDColor();
    D2HDColor(std::string color);
    D2HDColor(std::wstring color);
    D2HDColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char tint);
    unsigned int getBGRFormat();
    unsigned int getRGBFormat();
    static D2HDColor createFromRGBFormat(unsigned int color);
    static D2HDColor createFromBGRFormat(unsigned int color);

private:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char tint;
};
}

#endif
