/*****************************************************************************
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

#pragma once

#ifndef D2HDDRAW_H
#define D2HDDRAW_H

#include "../DLLmain.h"

namespace D2HD {
namespace Draw {
    extern HANDLE d2mrArchive;
    extern CellFile* blankCellFile;

    extern CellFile* d2mrFancyBorderCornerBottomLeft;
    extern CellFile* d2mrFancyBorderCornerBottomRight;
    extern CellFile* d2mrFancyBorderCornerTopLeft;
    extern CellFile* d2mrFancyBorderCornerTopRight;

    extern CellFile* d2mrFancyBorderInterfaceLeft;
    extern CellFile* d2mrFancyBorderInterfaceRight;

    extern CellFile* d2mrFancyBorderBottomLeft;
    extern CellFile* d2mrFancyBorderBottomRight;
    extern CellFile* d2mrFancyBorderLeft;
    extern CellFile* d2mrFancyBorderRight;

    extern CellFile* d2mrFancyBorderBottomLeft;
    extern CellFile* d2mrFancyBorderBottomRight;
    extern CellFile* d2mrFancyBorderTopLeft;
    extern CellFile* d2mrFancyBorderTopRight;

    extern CellFile* d2mrFancyHorizontalBar;
    extern CellFile* d2mrFancyVerticalBar;

    extern CellFile* d2mrFancyPanelHorizontalBar;
    extern CellFile* d2mrFancyPanelVerticalBar;

    extern CellFile* d2mrFancyPanelLeft;
    extern CellFile* d2mrFancyPanelRight;

    extern CellFile* d2mrStoneBack;
    extern CellFile* resolution1068x600Text;
    extern CellFile* resolution1344x700Text;

extern "C" {
    void __stdcall determineVideoOptionText(struct CellFile** outCellFile, void* baseAddress, unsigned int offset, struct CellFile* defaultCellFile);
    void determineVideoOptionTextInterception();

    void drawPanelBackground();
    void drawPanelBackgroundInterception();
    void drawLeftPanelBackground();
    void drawLeftPanelBorders();
    void drawRightPanelBackground();
    void drawRightPanelBorders();
    void drawLeftPanelBorders();
    void drawRightPanelBorders();

    void drawControlPanel();
    void drawControlPanelInterception();

    void unloadCellFile(CellFile** cellFile);
    void __stdcall unloadCellFiles(CellFile** orignal);
    void unloadCellFilesInterception();
}
}
}

#endif // D2HDDRAW_H
