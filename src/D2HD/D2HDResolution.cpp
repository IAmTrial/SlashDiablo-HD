/*****************************************************************************
 *                                                                           *
 *   D2HDResolution.cpp                                                      *
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
 *   Defines a class that stores resolutions and the list of resolutions     *
 *   intended for the game.                                                  *
 *                                                                           *
 *****************************************************************************/

#include "D2HDResolution.h"

#include <algorithm>
#include "../DLLmain.h"

std::vector<D2HD::D2HDResolution> D2HD::D2HDResolution::resolutions = {
    D2HD::D2HDResolution(640, 480),
    D2HD::D2HDResolution(800, 600),
    D2HD::D2HDResolution(800, 600),
    D2HD::D2HDResolution(856, 480),
    D2HD::D2HDResolution(1068, 600)
};

D2HD::D2HDResolution::D2HDResolution(const int width,
                                     const int height) : width(width), height(height) {
}

int D2HD::D2HDResolution::getWidth() const {
    return D2HD::D2HDResolution::width;
}

int D2HD::D2HDResolution::getHeight() const {
    return D2HD::D2HDResolution::height;
}

bool D2HD::D2HDResolution::operator==(const D2HD::D2HDResolution& other) const {
    return D2HD::D2HDResolution::width == other.width
           && D2HD::D2HDResolution::height == other.height;
}

std::vector<D2HD::D2HDResolution>& D2HD::D2HDResolution::getResolutions() {
    if (D2GFX_GetRenderMode() == D2RenderModes::VIDEO_MODE_DDRAW
            || D2GFX_GetRenderMode() == D2RenderModes::VIDEO_MODE_D3D) {
        D2HD::D2HDResolution::removeNonStandardResolutions();
    }

    return D2HD::D2HDResolution::resolutions;
}

void D2HD::D2HDResolution::removeNonStandardResolutions() {
    // Enumerate all valid resolutions for checking.
    std::vector<D2HD::D2HDResolution> compatibleResolutions;

    DEVMODEW devMode;
    devMode.dmSize = sizeof(DEVMODEW);

    for (DWORD i = 0; EnumDisplaySettingsW(nullptr, i, &devMode); i++) {
        compatibleResolutions.push_back(D2HD::D2HDResolution(devMode.dmPelsWidth,
                                        devMode.dmPelsHeight));
    }

    // If a resolution is not listed in EnumDisplaySettings, then remove it to prevent crash.
    for (auto it = D2HD::D2HDResolution::resolutions.cbegin();
            it != D2HD::D2HDResolution::resolutions.cend();) {
        if (std::find(compatibleResolutions.cbegin(), compatibleResolutions.cend(),
                      *it) == compatibleResolutions.cend()) {
            it = D2HD::D2HDResolution::resolutions.erase(it);
        } else {
            it++;
        }
    }
}
