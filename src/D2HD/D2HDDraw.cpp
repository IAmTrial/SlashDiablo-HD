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

void D2HD::Draw::drawControlPanel() {
    if (D2HD::Draw::d2mrFancyPanelLeft == nullptr) {
        D2HD::Draw::d2mrFancyPanelLeft = config.isFlipD2MRControlPanel() ? D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyPanelInvertLeft", 0) : D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyPanelLeft", 0);
    }
    if (D2HD::Draw::d2mrFancyPanelRight == nullptr) {
        D2HD::Draw::d2mrFancyPanelRight = config.isFlipD2MRControlPanel() ? D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyPanelInvertRight", 0) : D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyPanelRight", 0);
    }
    if (D2HD::Draw::d2mrFancyPanelBar == nullptr) {
        D2HD::Draw::d2mrFancyPanelBar = config.isFlipD2MRControlPanel() ? D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyPanelInvertBar", 0) : D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyPanelBar", 0);
    }

    CellContext panelLeft = { 0 };
    panelLeft.pCellFile = D2HD::Draw::d2mrFancyPanelLeft;
    panelLeft.nFrame = 0;
    D2GFX_DrawCellContext(&panelLeft, (117 + 48), *D2CLIENT_ScreenSizeY - 1, 0xFFFFFFFF, 5, 0);

    CellContext panelRight = { 0 };
    panelRight.pCellFile = D2HD::Draw::d2mrFancyPanelRight;
    panelRight.nFrame = 0;
    D2GFX_DrawCellContext(&panelRight, (*D2CLIENT_ScreenSizeX - 117 - 48 - 238), *D2CLIENT_ScreenSizeY - 1, 0xFFFFFFFF, 5, 0);

    CellContext panelBar = { 0 };
    panelBar.pCellFile = D2HD::Draw::d2mrFancyPanelBar;
    panelBar.nFrame = 0;

    for (int i = 0; ((i * 254) + (117 + 48 + 238)) < ((*D2CLIENT_ScreenSizeX / 2) - 128); i++) {
        D2GFX_DrawCellContext(&panelBar, ((i * 254) + (117 + 48 + 238)), *D2CLIENT_ScreenSizeY - 1, 0xFFFFFFFF, 5, 0);
    }

    for (int i = 0; ((*D2CLIENT_ScreenSizeX - 117 - 48 - 238) - (i * 254)) > ((*D2CLIENT_ScreenSizeX / 2) + 128); i++) {
        D2GFX_DrawCellContext(&panelBar, ((*D2CLIENT_ScreenSizeX - 117 - 48 - 238) - ((i + 1) * 254)), *D2CLIENT_ScreenSizeY - 1, 0xFFFFFFFF, 5, 0);
    }
}

void D2HD::Draw::drawPanelBackground() {
    switch (*D2CLIENT_PanelOpenMode) {
    case 1:
        D2HD::Draw::drawRightPanelBackground();
        D2HD::Draw::drawRightPanelBorders();
        break;

    case 2:
        D2HD::Draw::drawLeftPanelBackground();
        D2HD::Draw::drawLeftPanelBorders();
        break;

    case 3:
        D2HD::Draw::drawLeftPanelBackground();
        D2HD::Draw::drawRightPanelBackground();

        D2HD::Draw::drawLeftPanelBorders();
        D2HD::Draw::drawRightPanelBorders();
        break;

    default:
        break;
    }
}

// Draws a background on opened left panels to cover up extra space.
void D2HD::Draw::drawLeftPanelBackground() {
    if (D2HD::Draw::d2mrStoneBack == nullptr) {
        D2HD::Draw::d2mrStoneBack = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRStoneBack", 0);
    }

    CellContext image = { 0 };
    image.pCellFile = D2HD::Draw::d2mrStoneBack;
    image.nFrame = 0;

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2);

    // Draw background pieces
    const int backWidth = 256;
    const int backHeight = 256;

    for (int row = 0; (row * backHeight) < *D2CLIENT_ScreenSizeY; row++) {
        int backBasePositionY = ((row + 1) * backHeight);

        for (int col = 0; (int)(basePositionX - (col * backWidth)) >= 0; col++) {
            image.nFrame = ((row % 2) * 2) + (col % 2);
            int backBasePositionX = basePositionX - ((col + 1) * backWidth);

            D2GFX_DrawCellContext(&image, backBasePositionX, backBasePositionY, config.getLeftPanelBackgroundColor().getBGRFormat(), 5, nullptr);
        }
    }

    // Draw the ribbons only if the user has it enabled AND the game resolution allows the ribbons to be drawn without
    // problems.
    if (!config.isEnableD2MRBackgroundRibbon() && ((*D2CLIENT_ScreenSizeY - ((256 + 256 + 40) + 48)) <= (2 * (256 + 28)))) {
        return;
    }

    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    if (D2HD::Draw::d2mrFancyBorderLeft == nullptr) {
        D2HD::Draw::d2mrFancyBorderLeft = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderLeft", 0);
    }

    if (D2HD::Draw::d2mrFancyHorizontalBar == nullptr) {
        D2HD::Draw::d2mrFancyHorizontalBar = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyHorizontalBar", 0);
    }

    if (D2HD::Draw::d2mrFancyVerticalBar == nullptr) {
        D2HD::Draw::d2mrFancyVerticalBar = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyVerticalBar", 0);
    }

    CellContext borderLeft = { 0 };
    borderLeft.pCellFile = D2HD::Draw::d2mrFancyBorderLeft;
    borderLeft.nFrame = 0;

    D2GFX_DrawCellContext(&borderLeft, (basePositionX - 60), (basePositionY + 256) + (256 + 256 + 40), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    borderLeft.nFrame++;
    D2GFX_DrawCellContext(&borderLeft, (basePositionX - 60), (basePositionY + 256 + 28), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    D2GFX_DrawCellContext(&borderLeft, (basePositionX - 60), (basePositionY), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    borderLeft.nFrame--;
    D2GFX_DrawCellContext(&borderLeft, (basePositionX - 60), (basePositionY - 28), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);

    CellContext horizontalBar = { 0 };
    horizontalBar.pCellFile = D2HD::Draw::d2mrFancyHorizontalBar;
    horizontalBar.nFrame = 2;

    D2GFX_DrawCellContext(&horizontalBar, (basePositionX - 400 - 35), (basePositionY + (256 + 256 + 40)), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    D2GFX_DrawCellContext(&horizontalBar, (basePositionX - 400 - 35), (basePositionY + 60), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);

    for (int i = 0; (basePositionX - 400 - 35) - (i * 256) >= 0; i++) {
        horizontalBar.nFrame = std::abs(i - 1) % 2;
        D2GFX_DrawCellContext(&horizontalBar, (basePositionX - 400 - 35) - ((i + 1) * 256), (basePositionY + (256 + 256 + 40)), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
        D2GFX_DrawCellContext(&horizontalBar, (basePositionX - 400 - 35) - ((i + 1) * 256), (basePositionY + 60), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    }

    CellContext verticalBar = { 0 };
    verticalBar.pCellFile = D2HD::Draw::d2mrFancyVerticalBar;
    verticalBar.nFrame = 2;

    D2GFX_DrawCellContext(&verticalBar, (basePositionX - 400), (basePositionY), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);

    for (int i = 0; ((basePositionY - 35) - (i * 256)) >= 0; i++) {
        verticalBar.nFrame = std::abs(i - 1) % 2;
        D2GFX_DrawCellContext(&verticalBar, (basePositionX - 400), ((basePositionY - 35) - (i * 256)), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    }

    for (int i = 0; ((basePositionY + (256 + 256 + 40)) + (i * 256)) < (*D2CLIENT_ScreenSizeY); i++) {
        verticalBar.nFrame = i % 2;
        D2GFX_DrawCellContext(&verticalBar, (basePositionX - 400), ((basePositionY + (256 + 256 + 40)) + ((i + 1) * 256)), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    }
}

void D2HD::Draw::drawLeftPanelBorders() {
    if (D2HD::Draw::d2mrFancyBorderInterfaceLeft == nullptr) {
        D2HD::Draw::d2mrFancyBorderInterfaceLeft = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderInterfaceLeft", 0);
    }
    if (D2HD::Draw::d2mrFancyBorderBottom == nullptr) {
        D2HD::Draw::d2mrFancyBorderBottom = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderBottom", 0);
    }
    if (D2HD::Draw::d2mrFancyBorderTop == nullptr) {
        D2HD::Draw::d2mrFancyBorderTop = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderTop", 0);
    }
    if (D2HD::Draw::d2mrFancyBorderCorner == nullptr) {
        D2HD::Draw::d2mrFancyBorderCorner = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderCorner", 0);
    }

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2) - 400;
    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    // Draw top border pieces
    CellContext borderTop = { 0 };
    borderTop.nFrame = 0;
    borderTop.pCellFile = D2HD::Draw::d2mrFancyBorderTop;

    D2GFX_DrawCellContext(&borderTop, (basePositionX + 56), (basePositionY + 60), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    borderTop.nFrame++;
    D2GFX_DrawCellContext(&borderTop, (basePositionX + 56) + 256, (basePositionY + 60), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);


    // Draw bottom border pieces
    CellContext borderBottom = { 0 };
    borderBottom.nFrame = 0;
    borderBottom.pCellFile = D2HD::Draw::d2mrFancyBorderBottom;

    D2GFX_DrawCellContext(&borderBottom, (basePositionX + 56), (basePositionY + 256) + (256 + 40), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    borderBottom.nFrame++;
    D2GFX_DrawCellContext(&borderBottom, (basePositionX + 56) + 256, (basePositionY + 256) + (256 + 40), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);

    // Draw corner border pieces
    CellContext borderCorner = { 0 };
    borderCorner.nFrame = 0;
    borderCorner.pCellFile = D2HD::Draw::d2mrFancyBorderCorner;

    D2GFX_DrawCellContext(&borderCorner, (basePositionX + 56) + 284, (basePositionY + 60), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    D2GFX_DrawCellContext(&borderCorner, (basePositionX + 56) + 284, (basePositionY)+(256 + 256 + 40), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);

    // Draw left border pieces
    CellContext borderLeft = { 0 };
    borderLeft.nFrame = 0;
    borderLeft.pCellFile = D2HD::Draw::d2mrFancyBorderInterfaceLeft;

    D2GFX_DrawCellContext(&borderLeft, basePositionX, (basePositionY + 256), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    borderLeft.nFrame++;
    D2GFX_DrawCellContext(&borderLeft, basePositionX, (basePositionY + 256) + 256, config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    borderLeft.nFrame++;
    D2GFX_DrawCellContext(&borderLeft, basePositionX, (basePositionY + 256) + (256 + 40), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
}

void D2HD::Draw::drawRightPanelBackground() {
    if (D2HD::Draw::d2mrStoneBack == nullptr) {
        D2HD::Draw::d2mrStoneBack = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRStoneBack", 0);
    }

    CellContext image = { 0 };
    image.pCellFile = D2HD::Draw::d2mrStoneBack;
    image.nFrame = 0;

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2);

    // Draw background pieces
    const int backWidth = 256;
    const int backHeight = 256;

    for (int row = 0; (row * backHeight) < *D2CLIENT_ScreenSizeY; row++) {
        int backBasePositionY = ((row + 1) * backHeight);
        for (int col = 0; basePositionX + (col * backWidth) < *D2CLIENT_ScreenSizeX; col++) {
            image.nFrame = ((row % 2) * 2) + ((col + 1) % 2);
            int backBasePositionX = basePositionX + (col * backWidth);

            D2GFX_DrawCellContext(&image, backBasePositionX, backBasePositionY, config.getRightPanelBackgroundColor().getBGRFormat(), 5, 0);
        }
    }

    // Draw the ribbons only if the user has it enabled AND the game resolution allows the ribbons to be drawn without
    // problems.
    if (!config.isEnableD2MRBackgroundRibbon() && ((*D2CLIENT_ScreenSizeY - ((256 + 256 + 40) + 48)) <= (2 * (256 + 28)))) {
        return;
    }

    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    if (D2HD::Draw::d2mrFancyBorderRight == nullptr) {
        D2HD::Draw::d2mrFancyBorderRight = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderRight", 0);
    }

    if (D2HD::Draw::d2mrFancyHorizontalBar == nullptr) {
        D2HD::Draw::d2mrFancyHorizontalBar = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyHorizontalBar", 0);
    }

    if (D2HD::Draw::d2mrFancyVerticalBar == nullptr) {
        D2HD::Draw::d2mrFancyVerticalBar = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyVerticalBar", 0);
    }

    CellContext borderRight = { 0 };
    borderRight.pCellFile = D2HD::Draw::d2mrFancyBorderRight;
    borderRight.nFrame = 0;

    D2GFX_DrawCellContext(&borderRight, (basePositionX), (basePositionY + 256) + (256 + 256 + 40), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    borderRight.nFrame++;
    D2GFX_DrawCellContext(&borderRight, (basePositionX), (basePositionY + 256 + 28), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    D2GFX_DrawCellContext(&borderRight, (basePositionX), (basePositionY), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    borderRight.nFrame--;
    D2GFX_DrawCellContext(&borderRight, (basePositionX), (basePositionY - 28), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);

    CellContext horizontalBar = { 0 };
    horizontalBar.pCellFile = D2HD::Draw::d2mrFancyHorizontalBar;

    for (int i = 0; (basePositionX + 400) + (i * 256) < (*D2CLIENT_ScreenSizeX); i++) {
        horizontalBar.nFrame = i % 2;
        D2GFX_DrawCellContext(&horizontalBar, (basePositionX + 400) + (i * 256), (basePositionY + (256 + 256 + 40)), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
        D2GFX_DrawCellContext(&horizontalBar, (basePositionX + 400) + (i * 256), (basePositionY + 60), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    }

    CellContext verticalBar = { 0 };
    verticalBar.pCellFile = D2HD::Draw::d2mrFancyVerticalBar;
    verticalBar.nFrame = 2;

    D2GFX_DrawCellContext(&verticalBar, (basePositionX + 400 - 60), (basePositionY), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);

    for (int i = 0; ((basePositionY - 35) - (i * 256)) >= 0; i++) {
        verticalBar.nFrame = std::abs(i - 1) % 2;
        D2GFX_DrawCellContext(&verticalBar, (basePositionX + 400 - 60), ((basePositionY - 35) - (i * 256)), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    }

    for (int i = 0; ((basePositionY + (256 + 256 + 40)) + (i * 256)) < (*D2CLIENT_ScreenSizeY); i++) {
        verticalBar.nFrame = i % 2;
        D2GFX_DrawCellContext(&verticalBar, (basePositionX + 400 - 60), ((basePositionY + (256 + 256 + 40)) + ((i + 1) * 256)), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    }
}

void D2HD::Draw::drawRightPanelBorders() {
    if (D2HD::Draw::d2mrFancyBorderInterfaceRight == nullptr) {
        D2HD::Draw::d2mrFancyBorderInterfaceRight = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderInterfaceRight", 0);
    }
    if (D2HD::Draw::d2mrFancyBorderBottom == nullptr) {
        D2HD::Draw::d2mrFancyBorderBottom = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderBottom", 0);
    }
    if (D2HD::Draw::d2mrFancyBorderTop == nullptr) {
        D2HD::Draw::d2mrFancyBorderTop = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderTop", 0);
    }
    if (D2HD::Draw::d2mrFancyBorderCorner == nullptr) {
        D2HD::Draw::d2mrFancyBorderCorner = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderCorner", 0);
    }

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2);
    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    // Draw top border pieces
    CellContext borderTop = { 0 };
    borderTop.nFrame = 0;
    borderTop.pCellFile = D2HD::Draw::d2mrFancyBorderTop;

    D2GFX_DrawCellContext(&borderTop, (basePositionX + 60), (basePositionY + 60), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    borderTop.nFrame++;
    D2GFX_DrawCellContext(&borderTop, (basePositionX + 60) + 256, (basePositionY + 60), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);


    // Draw bottom border pieces
    CellContext borderBottom = { 0 };
    borderBottom.nFrame = 0;
    borderBottom.pCellFile = D2HD::Draw::d2mrFancyBorderBottom;

    D2GFX_DrawCellContext(&borderBottom, (basePositionX + 60), (basePositionY + 256) + (256 + 40), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    borderBottom.nFrame++;
    D2GFX_DrawCellContext(&borderBottom, (basePositionX + 60) + 256, (basePositionY + 256) + (256 + 40), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);

    // Draw corner border pieces
    CellContext borderCorner = { 0 };
    borderCorner.nFrame = 0;
    borderCorner.pCellFile = D2HD::Draw::d2mrFancyBorderCorner;

    D2GFX_DrawCellContext(&borderCorner, (basePositionX), (basePositionY + 60), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    D2GFX_DrawCellContext(&borderCorner, (basePositionX), (basePositionY + 256) + (256 + 40), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);

    // Draw left border pieces
    CellContext borderRight = { 0 };
    borderRight.nFrame = 0;
    borderRight.pCellFile = D2HD::Draw::d2mrFancyBorderInterfaceRight;

    D2GFX_DrawCellContext(&borderRight, (basePositionX + 320), (basePositionY + 256), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    borderRight.nFrame++;
    D2GFX_DrawCellContext(&borderRight, (basePositionX + 320), (basePositionY + 256) + 256, config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    borderRight.nFrame++;
    D2GFX_DrawCellContext(&borderRight, (basePositionX + 320), (basePositionY + 256) + (256 + 40), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
}

void D2HD::Draw::unloadCellFile(CellFile** cellFile) {
    if (*cellFile != nullptr) {
        D2CMP_FreeCellFile(*cellFile);
        FOG_FreeClientMemory(*cellFile, __FILE__, __LINE__, nullptr);

        *cellFile = nullptr;
    }
}

void __stdcall D2HD::Draw::unloadCellFiles(CellFile** original) {
    D2HD::Draw::unloadCellFile(&D2HD::Draw::d2mrStoneBack);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::d2mrFancyBorderBottom);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::d2mrFancyBorderCorner);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::d2mrFancyBorderInterfaceLeft);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::d2mrFancyBorderInterfaceRight);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::d2mrFancyBorderLeft);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::d2mrFancyBorderRight);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::d2mrFancyBorderTop);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::d2mrFancyHorizontalBar);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::d2mrFancyPanelBar);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::d2mrFancyPanelLeft);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::d2mrFancyPanelRight);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::d2mrFancyVerticalBar);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::blankCellFile);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::resolution1068x600Text);
    D2HD::Draw::unloadCellFile(&D2HD::Draw::resolution1344x700Text);

    *original = *D2CLIENT_PanelBorderImage;
}
