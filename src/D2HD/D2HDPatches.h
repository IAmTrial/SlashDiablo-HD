/*****************************************************************************
 *                                                                           *
 *   D2HDPatches.h                                                           *
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
 *   Declares the functions that expands Diablo II's standard functions to   *
 *   allow changing to and using custom resolutions.                         *
 *                                                                           *
 *****************************************************************************/

#include "../DLLmain.h"

#pragma once

#ifndef D2HDPATCHES_H
#define D2HDPATCHES_H

namespace D2HD {
extern "C" {
    void __stdcall getModeParams(int mode, int* width, int* height);

    void repositionPanels();
    void repositionPanelsInterception();

    void __stdcall getPatchedResolutionMode(int* resolutionMode);
    void getPatchedResolutionModeInterception();

    void __stdcall resizeGameLogicResolution(int mode);
    void resizeGameLogicResolutionInterception();

    void __stdcall setResolutionMode(int* gameResolution, int configResolution);
    void setResolutionModeEAXInterception();
    void setResolutionModeEDIInterception();

    void __stdcall setResolutionModeFromMenu(int* mode);
    void setResolutionModeFromMenuInterception();

    void setGDIRenderResolutionInterception();

    void __stdcall setGDIForegroundRenderWidth(int mode);
    void setGDIForegroundRenderWidthInterception();
}
}

#endif
