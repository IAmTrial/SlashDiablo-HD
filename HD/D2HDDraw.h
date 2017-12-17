/****************************************************************************
*                                                                           *
*   D2HDDraw.h                                                              *
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
*   Declares the functions that corrects standard Diablo II draw functions  *
*   to work with higher resolutions. It also declares new draw calls to     *
*   imitate the look of D2MultiRes.                                         *
*                                                                           *
*****************************************************************************/

/*
    Many thanks to the creator of D2MultiRes and the person who revealed its source on BlizzHackers.
    In addition, thanks to the creators of D2Ex2 for publicly hosting their own code, which helped
    me double-check whether I was going toward the right direction.
*/

#pragma once

#ifndef D2HDDRAW_H
#define D2HDDRAW_H

namespace HD {
    void RedrawUILeftPanelBorders();
    void RedrawUIRightPanelBorders();
    void STUB_DrawUIPanelBackground();
    void DrawUIPanelBackground();
    void STUB_DrawUIControlPanel();
    void DrawUIControlPanel();
    void STUB_UnloadCellFiles();
    void STUB_DetermineText();
    void* DetermineText();
}

#endif
