/*****************************************************************************
 *                                                                           *
 *   D2HDPatches.cpp                                                         *
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
 *   Defines functions that are intended to replace instruction code in the  *
 *   Diablo II game process.                                                 *
 *                                                                           *
 *   These functions cannot be called without a proper corresponding         *
 *   interception function.                                                  *
 *                                                                           *
 *****************************************************************************/

#include "D2HDPatches.h"

#include "../DLLmain.h"

void D2HD::getModeParams(int mode, int* width, int* height) {
    if (mode < D2HD::D2HDResolution::getResolutions().size()) {
        *width = D2HD::D2HDResolution::getResolutions().at(mode).getWidth();
        *height = D2HD::D2HDResolution::getResolutions().at(mode).getHeight();
    } else {
        *width = 640;
        *height = 480;
        MessageBoxW(nullptr,
                    L"It appears that you have specified a custom resolution, but you haven't defined its width and height.",
                    L"Missing Definition Case", MB_OK | MB_ICONSTOP);
        std::exit(0);
    }
}

void D2HD::repositionPanels() {
    *D2CLIENT_PanelOffsetX = (*D2CLIENT_ScreenSizeX / 2) - 320;
    *D2CLIENT_PanelOffsetY = (*D2CLIENT_ScreenSizeY - 480) / -2;
}

void __stdcall D2HD::getPatchedResolutionMode(int* resolutionMode) {
    *resolutionMode = (*D2CLIENT_ScreenSizeX >= 800) ? 2 : 0;
}

void __stdcall D2HD::resizeGameLogicResolution(int mode) {
    D2HD::getModeParams(mode, D2CLIENT_ScreenSizeX, D2CLIENT_ScreenSizeY);
    *D2CLIENT_InventoryArrangeMode = mode;
}

void __stdcall D2HD::setResolutionMode(int* gameResolution,
                                       int configResolution) {
    if (configResolution == 1) {
        *gameResolution = 2;
    } else {
        *gameResolution = configResolution;
    }
}

void __stdcall D2HD::setResolutionModeFromMenu(int* mode) {
    int currentMode = D2GFX_GetResolutionMode();

    if (currentMode == 0) {
        *mode = 2;
    } else if (currentMode >= D2HDResolution::getResolutions().size() - 1) {
        *mode = 0;
    } else {
        *mode = currentMode + 1;
    }
}

void __stdcall D2HD::setGDIForegroundRenderWidth(int mode) {
    int discarded = 0;
    D2HD::getModeParams(mode, D2GDI_ForegroundRenderWidth, &discarded);
}

void __stdcall D2HD::setGlideRenderResolution(int newGameResolutionMode,
        int* glideResolutionMode) {
    D2HD::getModeParams(newGameResolutionMode, D2GLIDE_ScreenSizeX,
                        D2GLIDE_ScreenSizeY);

    switch (newGameResolutionMode) {
    case 0:
        *glideResolutionMode = 7;
        break;

    case 1:
        *glideResolutionMode = 8;
        break;

    default:
        *glideResolutionMode = (newGameResolutionMode - 2) + 8;
        break;
    }

    // Apply special case for /r/Diablo2Resurgence
    if (D2Version::getGlide3xVersionID() == D2Version::Glide3xVersionID::RESURGENCE
            && *D2GLIDE_ScreenSizeX == 1068 && *D2GLIDE_ScreenSizeY == 600) {
        *glideResolutionMode = 0xFF;
    }

    *D2GLIDE_SpritesInited = (newGameResolutionMode != 1);
}

void __stdcall D2HD::setupGlideWindowSize(int newGlideResolutionMode) {
    const int resolutionMode = (newGlideResolutionMode == 7) ? 0 : ((newGlideResolutionMode - 8) + 2);
    D2HD::getModeParams(resolutionMode, *GLIDE3X_WindowSizeX, *GLIDE3X_WindowSizeY);
}
