#pragma once

#ifndef D2HDDRAW_H
#define D2HDDRAW_H

#include "../DLLmain.h"

namespace D2HD {
namespace Draw {
    extern HANDLE d2mrArchive;
    extern CellFile* blankCellFile;
    extern CellFile* d2mrFancyBorderBottom;
    extern CellFile* d2mrFancyBorderCorner;
    extern CellFile* d2mrFancyBorderInterfaceLeft;
    extern CellFile* d2mrFancyBorderInterfaceRight;
    extern CellFile* d2mrFancyBorderLeft;
    extern CellFile* d2mrFancyBorderRight;
    extern CellFile* d2mrFancyBorderTop;
    extern CellFile* d2mrFancyHorizontalBar;
    extern CellFile* d2mrFancyPanelBar;
    extern CellFile* d2mrFancyPanelLeft;
    extern CellFile* d2mrFancyPanelRight;
    extern CellFile* d2mrFancyVerticalBar;
    extern CellFile* d2mrStoneBack;
    extern CellFile* resolution1068x600Text;
    extern CellFile* resolution1344x700Text;

extern "C" {
    void __stdcall determineVideoOptionText(struct CellFile** outCellFile, void* baseAddress, unsigned int offset, struct CellFile* defaultCellFile);
    void determineVideoOptionTextInterception();
}
}
}

#endif // D2HDDRAW_H
