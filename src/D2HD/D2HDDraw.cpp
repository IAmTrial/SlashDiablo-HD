#include "D2HDDraw.h"

HANDLE D2HD::Draw::d2mrArchive = nullptr;

CellFile* D2HD::Draw::blankCellFile = nullptr;
CellFile* D2HD::Draw::d2mrFancyBorderBottom = nullptr;
CellFile* D2HD::Draw::d2mrFancyBorderCorner = nullptr;
CellFile* D2HD::Draw::d2mrFancyBorderInterfaceLeft = nullptr;
CellFile* D2HD::Draw::d2mrFancyBorderInterfaceRight = nullptr;
CellFile* D2HD::Draw::d2mrFancyBorderLeft = nullptr;
CellFile* D2HD::Draw::d2mrFancyBorderRight = nullptr;
CellFile* D2HD::Draw::d2mrFancyBorderTop = nullptr;
CellFile* D2HD::Draw::d2mrFancyHorizontalBar = nullptr;
CellFile* D2HD::Draw::d2mrFancyPanelBar = nullptr;
CellFile* D2HD::Draw::d2mrFancyPanelLeft = nullptr;
CellFile* D2HD::Draw::d2mrFancyPanelRight = nullptr;
CellFile* D2HD::Draw::d2mrFancyVerticalBar = nullptr;
CellFile* D2HD::Draw::d2mrStoneBack = nullptr;
CellFile* D2HD::Draw::resolution1068x600Text = nullptr;
CellFile* D2HD::Draw::resolution1344x700Text = nullptr;

void __stdcall D2HD::Draw::determineVideoOptionText(struct CellFile**
        outCellFile, void* baseAddress, unsigned int offset,
        struct CellFile* defaultCellFile) {
    if (D2HD::Draw::blankCellFile == nullptr) {
        D2HD::Draw::blankCellFile = D2WIN_LoadCellFile("data\\local\\UI\\ENG\\Blank",
                                    0);
    }

    if (D2HD::Draw::resolution1068x600Text == nullptr) {
        D2HD::Draw::resolution1068x600Text =
            D2WIN_LoadCellFile("data\\local\\UI\\ENG\\1068x600", 0);
    }

    if (D2HD::Draw::resolution1344x700Text == nullptr) {
        D2HD::Draw::resolution1344x700Text =
            D2WIN_LoadCellFile("data\\local\\UI\\ENG\\1344x700", 0);
    }

    if (baseAddress == D2CLIENT_VideoOptionCellFileStart && offset == 0x154) {
        if ((*D2CLIENT_ScreenSizeX == 640 && *D2CLIENT_ScreenSizeY == 480) || (*D2CLIENT_ScreenSizeX == 800 && *D2CLIENT_ScreenSizeY == 600)) {
            *outCellFile = defaultCellFile;
        } else if (*D2CLIENT_ScreenSizeX == 1068 && *D2CLIENT_ScreenSizeY == 600) {
            *outCellFile = D2HD::Draw::resolution1068x600Text;
        } else if (*D2CLIENT_ScreenSizeX == 1344 && *D2CLIENT_ScreenSizeY == 700) {
            *outCellFile = D2HD::Draw::resolution1344x700Text;
        } else {
            *outCellFile = D2HD::Draw::blankCellFile;
        }
    } else {
        *outCellFile = defaultCellFile;
    }
}
