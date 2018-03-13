/***************************************************************************
 *                                                                         *
 *   SlashDiablo HD                                                        *
 *   Copyright (C) 2017  Mir Drualga                                       *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 *-------------------------------------------------------------------------*
 *                                                                         *
 *   Declares a class that stores resolutions and the list of resolutions  *
 *   intended for the game.                                                *
 *                                                                         *
 ***************************************************************************/

#pragma once

#ifndef D2HDRESOLUTION_H
#define D2HDRESOLUTION_H

#include <vector>

namespace D2HD {
class D2HDResolution {
public:
    D2HDResolution(const int width, const int height);
    int getWidth() const;
    int getHeight() const;

    bool operator==(const D2HD::D2HDResolution& other) const;

    static std::vector<D2HDResolution>& getResolutions();

private:
    static std::vector<D2HDResolution> resolutions;
    static void removeNonStandardResolutions();

    int width;
    int height;
};
}

#endif // D2HDRESOLUTION_H
