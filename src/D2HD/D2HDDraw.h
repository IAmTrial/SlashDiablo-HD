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
 *   Declares the functions that corrects standard Diablo II draw            *
 *   functions to work with higher resolutions. It also declares new draw    *
 *   calls to imitate the look of D2MultiRes.                                *
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

    extern D2HD::D2HDCellContext controlPanel800;
    extern D2HD::D2HDCellContext statsButton;
    extern D2HD::D2HDCellContext skillButton;

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

    void drawControlPanel800Foreground();
    void drawControlPanel800ForegroundInterception();

    void drawControlPanelBackground();
    void drawControlPanelBackgroundInterception();

    void __stdcall drawActiveStatsButton();
    void drawActiveStatsButtonInterception();
    void __stdcall drawInactiveStatsButton();
    void drawInactiveStatsButtonInterception();
    void __stdcall drawStatsButtonText();
    void drawStatsButtonTextInterception();

    void __stdcall drawActiveSkillButton();
    void drawActiveSkillButtonInterception();
    void __stdcall drawInactiveSkillButton();
    void drawInactiveSkillButtonInterception();
    void __stdcall drawSkillButtonText();
    void drawSkillButtonTextInterception();

    void unloadCellFile(CellFile** cellFile);
    void __stdcall unloadCellFiles(CellFile** orignal);
    void unloadCellFilesInterception();
}
}
}

#endif // D2HDDRAW_H
