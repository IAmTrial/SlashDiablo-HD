/*****************************************************************************
 *                                                                           *
 *  SlashDiablo HD                                                           *
 *  Copyright (C) 2017  Mir Drualga                                          *
 *                                                                           *
 *  This program is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU Affero General Public License as published *
 *  by the Free Software Foundation, either version 3 of the License, or     *
 *  (at your option) any later version.                                      *
 *                                                                           *
 *  This program is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU Affero General Public License for more details.                      *
 *                                                                           *
 *  You should have received a copy of the GNU Affero General Public License *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
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
    D2HDColor(const unsigned char red, const unsigned char green,
              const unsigned char blue, const unsigned char tint);
    unsigned int getBGRFormat() const;
    unsigned int getRGBFormat() const;

    static D2HDColor createFromRGBFormat(const unsigned int color);
    static D2HDColor createFromRGBFormat(const std::string& color);
    static D2HDColor createFromRGBFormat(const std::wstring& color);

    static D2HDColor createFromBGRFormat(const unsigned int color);
    static D2HDColor createFromBGRFormat(const std::string& color);
    static D2HDColor createFromBGRFormat(const std::wstring& color);

private:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char tint;
};
}

#endif
