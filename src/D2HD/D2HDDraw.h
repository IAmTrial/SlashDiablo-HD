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
    extern D2HD::D2HDCellContext blankCellFile;

    extern D2HD::D2HDCellContext d2mrFancyBorderCorner;
    extern D2HD::D2HDCellContext neoD2MRFancyBorderCornerBottomLeft;
    extern D2HD::D2HDCellContext neoD2MRFancyBorderCornerBottomRight;
    extern D2HD::D2HDCellContext neoD2MRFancyBorderCornerTopLeft;
    extern D2HD::D2HDCellContext neoD2MRFancyBorderCornerTopRight;

    extern D2HD::D2HDCellContext d2mrFancyBorderInterfaceLeft;
    extern D2HD::D2HDCellContext d2mrFancyBorderInterfaceRight;
    extern D2HD::D2HDCellContext neoD2MRFancyBorderInterfaceLeft;
    extern D2HD::D2HDCellContext neoD2MRFancyBorderInterfaceRight;

    extern D2HD::D2HDCellContext d2mrFancyBorderLeft;
    extern D2HD::D2HDCellContext d2mrFancyBorderRight;

    extern D2HD::D2HDCellContext d2mrFancyBorderBottom;
    extern D2HD::D2HDCellContext d2mrFancyBorderTop;
    extern D2HD::D2HDCellContext neoD2MRFancyBorderBottomLeft;
    extern D2HD::D2HDCellContext neoD2MRFancyBorderBottomRight;
    extern D2HD::D2HDCellContext neoD2MRFancyBorderTopLeft;
    extern D2HD::D2HDCellContext neoD2MRFancyBorderTopRight;

    extern D2HD::D2HDCellContext d2mrFancyHorizontalBar;
    extern D2HD::D2HDCellContext d2mrFancyVerticalBar;
    extern D2HD::D2HDCellContext d2mrFancyPanelFlipHorizontalBar;
    extern D2HD::D2HDCellContext d2mrFancyPanelFlipVerticalBar;

    extern D2HD::D2HDCellContext d2mrFancyPanelHorizontalBar;
    extern D2HD::D2HDCellContext d2mrFancyPanelVerticalBar;

    extern D2HD::D2HDCellContext d2mrFancyPanelLeft;
    extern D2HD::D2HDCellContext d2mrFancyPanelRight;
    extern D2HD::D2HDCellContext d2mrFancyPanelFlipLeft;
    extern D2HD::D2HDCellContext d2mrFancyPanelFlipRight;

    extern D2HD::D2HDCellContext d2mrStoneBack;
    extern D2HD::D2HDCellContext resolution1068x600Text;
    extern D2HD::D2HDCellContext resolution1344x700Text;

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
