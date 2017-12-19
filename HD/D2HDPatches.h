/****************************************************************************
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

#pragma once

#ifndef D2HDPATCHES_H
#define D2HDPATCHES_H

#include "../DLLmain.h"

namespace HD {
    void __stdcall D2GFX_GetModeParams(int mode, DWORD* width, DWORD* height);

    void ResizeWindow_Interception();
    void ResizeRenderResolution_Interception();
    void ResizeForgroundRenderWidth_Interception();
    void ResizeGameLogicResolution_Interception();
    void SetResolutionModeId_Interception();
    void SetResolutionModeOnGameStart001_Interception();
    void SetResolutionModeOnGameStart002_Interception();
    void SetRegistryResolutionModeId_Interception();
    void SaveRegistryResolution_Interception(int mode);
    void LoadRegistryResolution_Interception(int* mode);

    void ResizeD2DWindow_Interception();
    void Replace640_ResizeD2D_Interception1();

    void SetupGlideRenderResolution_Interception();
    void __stdcall SetupGlideWindowSize();

    void __stdcall RepositionPanels();

    int __stdcall GetResolutionMode_Patch();
}

#endif
