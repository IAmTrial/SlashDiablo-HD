/*****************************************************************************
 *                                                                           *
 *   D2HDResolution.h                                                        *
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
 *   Declares a class that stores resolutions and the list of resolutions    *
 *   intended for the game.                                                  *
 *                                                                           *
 *****************************************************************************/

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
