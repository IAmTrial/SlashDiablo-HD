#include "D2HDDraw.h"
#include "../DLLmain.h"
#include "../D2Ptrs.h"

void DrawUILeftPanelBackground();
void DrawUIRightPanelBackground();
void RedrawUILeftPanelBorders_D2MR();
void RedrawUILeftPanelBorders_Original();
void RedrawUIRightPanelBorders_D2MR();
void RedrawUIRightPanelBorders_Original();

// Redraws the left side panel borders in the correct places, independent of resolution.
void HD::RedrawUILeftPanelBorders_Interception() {
    __asm push edi

    if (EnableD2MRPanelBorderStyle) {
        RedrawUILeftPanelBorders_D2MR();
    } else {
        RedrawUILeftPanelBorders_Original();
    }

    __asm pop edi
}

// Redraws the right side panel borders in the correct places, independent of resolution.
void HD::RedrawUIRightPanelBorders_Interception() {
    __asm push edi

    if (EnableD2MRPanelBorderStyle) {
        RedrawUIRightPanelBorders_D2MR();
    } else {
        RedrawUIRightPanelBorders_Original();
    }

    __asm pop edi
}

__declspec(naked) void* __stdcall LoadCellFile(const char* szBuffer) {
    __asm
    {
        PUSH ESI
            MOV ESI, [ESP + 8]
            CALL[D2CLIENT_LoadUIImage]
            POP ESI
            RETN 4
    }
}

void RedrawUIRightPanelBorders_D2MR() {
    if (D2MRFancyBorderInterfaceRight == nullptr) {
        D2MRFancyBorderInterfaceRight = LoadCellFile("Panel/D2MRFancyBorderInterfaceRight");
    }
    if (D2MRFancyBorderBottom == nullptr) {
        D2MRFancyBorderBottom = LoadCellFile("Panel/D2MRFancyBorderBottom");
    }
    if (D2MRFancyBorderTop == nullptr) {
        D2MRFancyBorderTop = LoadCellFile("Panel/D2MRFancyBorderTop");
    }
    if (D2MRFancyBorderCorner == nullptr) {
        D2MRFancyBorderCorner = LoadCellFile("Panel/D2MRFancyBorderCorner");
    }

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2);
    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    // Draw top border pieces
    D2ImageDrawStrc borderTop = { 0 };
    borderTop.nFrame = 0;
    borderTop.pCellFile = D2MRFancyBorderTop;

    D2GFX_DrawImage(&borderTop, (basePositionX + 60), (basePositionY + 60), RightPanelBorderColor, 5, nullptr);
    borderTop.nFrame++;
    D2GFX_DrawImage(&borderTop, (basePositionX + 60) + 256, (basePositionY + 60), RightPanelBorderColor, 5, nullptr);


    // Draw bottom border pieces
    D2ImageDrawStrc borderBottom = { 0 };
    borderBottom.nFrame = 0;
    borderBottom.pCellFile = D2MRFancyBorderBottom;

    D2GFX_DrawImage(&borderBottom, (basePositionX + 60), (basePositionY + 256) + (256 + 40), RightPanelBorderColor, 5, nullptr);
    borderBottom.nFrame++;
    D2GFX_DrawImage(&borderBottom, (basePositionX + 60) + 256, (basePositionY + 256) + (256 + 40), RightPanelBorderColor, 5, nullptr);

    // Draw corner border pieces
    D2ImageDrawStrc borderCorner = { 0 };
    borderCorner.nFrame = 0;
    borderCorner.pCellFile = D2MRFancyBorderCorner;

    D2GFX_DrawImage(&borderCorner, (basePositionX), (basePositionY + 60), RightPanelBorderColor, 5, nullptr);
    D2GFX_DrawImage(&borderCorner, (basePositionX), (basePositionY + 256) + (256 + 40), RightPanelBorderColor, 5, nullptr);

    // Draw left border pieces
    D2ImageDrawStrc borderRight = { 0 };
    borderRight.nFrame = 0;
    borderRight.pCellFile = D2MRFancyBorderInterfaceRight;

    D2GFX_DrawImage(&borderRight, (basePositionX + 320), (basePositionY + 256), RightPanelBorderColor, 5, nullptr);
    borderRight.nFrame++;
    D2GFX_DrawImage(&borderRight, (basePositionX + 320), (basePositionY + 256) + 256, RightPanelBorderColor, 5, nullptr);
    borderRight.nFrame++;
    D2GFX_DrawImage(&borderRight, (basePositionX + 320), (basePositionY + 256) + (256 + 40), RightPanelBorderColor, 5, nullptr);
}

void RedrawUIRightPanelBorders_Original() {
    if (*D2CLIENT_PanelBorderImage == nullptr) {
        *D2CLIENT_PanelBorderImage = LoadCellFile("Panel/800BorderFrame");
    }

    D2ImageDrawStrc image = { 0 };
    image.pCellFile = *D2CLIENT_PanelBorderImage;
    image.nFrame = 5;

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2);
    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    // Frame 5
    D2GFX_DrawImage(&image, basePositionX, basePositionY + 63, RightPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 6
    D2GFX_DrawImage(&image, basePositionX + 144, basePositionY + 253, RightPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 7
    D2GFX_DrawImage(&image, basePositionX + 313, basePositionY + 484, RightPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 8
    D2GFX_DrawImage(&image, basePositionX + 144, basePositionY + 553, RightPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 9
    D2GFX_DrawImage(&image, basePositionX, basePositionY + 553, RightPanelBorderColor, 5, 0);
    image.nFrame++;
}

void RedrawUILeftPanelBorders_Original() {
    if (*D2CLIENT_PanelBorderImage == nullptr) {
        *D2CLIENT_PanelBorderImage = LoadCellFile("Panel/800BorderFrame");
    }

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2) - 400;
    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    D2ImageDrawStrc image = { 0 };
    image.pCellFile = *D2CLIENT_PanelBorderImage;
    image.nFrame = 0;

    // Frame 0
    D2GFX_DrawImage(&image, basePositionX, basePositionY + 253, LeftPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 1
    D2GFX_DrawImage(&image, basePositionX + 256, basePositionY + 63, LeftPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 2
    D2GFX_DrawImage(&image, basePositionX, basePositionY + 484, LeftPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 3
    D2GFX_DrawImage(&image, basePositionX, basePositionY + 553, LeftPanelBorderColor, 5, 0);
    image.nFrame++;

    // Frame 4
    D2GFX_DrawImage(&image, basePositionX + 256, basePositionY + 553, LeftPanelBorderColor, 5, 0);
    image.nFrame++;
}

void RedrawUILeftPanelBorders_D2MR() {
    if (D2MRFancyBorderInterfaceLeft == nullptr) {
        D2MRFancyBorderInterfaceLeft = LoadCellFile("Panel/D2MRFancyBorderInterfaceLeft");
    }
    if (D2MRFancyBorderBottom == nullptr) {
        D2MRFancyBorderBottom = LoadCellFile("Panel/D2MRFancyBorderBottom");
    }
    if (D2MRFancyBorderTop == nullptr) {
        D2MRFancyBorderTop = LoadCellFile("Panel/D2MRFancyBorderTop");
    }
    if (D2MRFancyBorderCorner == nullptr) {
        D2MRFancyBorderCorner = LoadCellFile("Panel/D2MRFancyBorderCorner");
    }

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2) - 400;
    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    // Draw top border pieces
    D2ImageDrawStrc borderTop = { 0 };
    borderTop.nFrame = 0;
    borderTop.pCellFile = D2MRFancyBorderTop;

    D2GFX_DrawImage(&borderTop, (basePositionX + 56), (basePositionY + 60), LeftPanelBorderColor, 5, nullptr);
    borderTop.nFrame++;
    D2GFX_DrawImage(&borderTop, (basePositionX + 56) + 256, (basePositionY + 60), LeftPanelBorderColor, 5, nullptr);


    // Draw bottom border pieces
    D2ImageDrawStrc borderBottom = { 0 };
    borderBottom.nFrame = 0;
    borderBottom.pCellFile = D2MRFancyBorderBottom;

    D2GFX_DrawImage(&borderBottom, (basePositionX + 56), (basePositionY + 256) + (256 + 40), LeftPanelBorderColor, 5, nullptr);
    borderBottom.nFrame++;
    D2GFX_DrawImage(&borderBottom, (basePositionX + 56) + 256, (basePositionY + 256) + (256 + 40), LeftPanelBorderColor, 5, nullptr);

    // Draw corner border pieces
    D2ImageDrawStrc borderCorner = { 0 };
    borderCorner.nFrame = 0;
    borderCorner.pCellFile = D2MRFancyBorderCorner;

    D2GFX_DrawImage(&borderCorner, (basePositionX + 56) + 284, (basePositionY + 60), LeftPanelBorderColor, 5, nullptr);
    D2GFX_DrawImage(&borderCorner, (basePositionX + 56) + 284, (basePositionY)+(256 + 256 + 40), LeftPanelBorderColor, 5, nullptr);

    // Draw left border pieces
    D2ImageDrawStrc borderLeft = { 0 };
    borderLeft.nFrame = 0;
    borderLeft.pCellFile = D2MRFancyBorderInterfaceLeft;

    D2GFX_DrawImage(&borderLeft, basePositionX, (basePositionY + 256), LeftPanelBorderColor, 5, nullptr);
    borderLeft.nFrame++;
    D2GFX_DrawImage(&borderLeft, basePositionX, (basePositionY + 256) + 256, LeftPanelBorderColor, 5, nullptr);
    borderLeft.nFrame++;
    D2GFX_DrawImage(&borderLeft, basePositionX, (basePositionY + 256) + (256 + 40), LeftPanelBorderColor, 5, nullptr);
}

void HD::DrawUIPanelBackground() {
    switch (*D2CLIENT_PanelOpenMode) {
    case 1:
        DrawUIRightPanelBackground();
        break;

    case 2:
        DrawUILeftPanelBackground();
        break;

    case 3:
        DrawUILeftPanelBackground();
        DrawUIRightPanelBackground();
        break;

    default:
        break;
    }
}

// Draws a background on opened left panels to cover up extra space.
void DrawUILeftPanelBackground() {
    if (D2MRStoneBack == nullptr) {
        D2MRStoneBack = LoadCellFile(/*"data/global/ui/*/"Panel/D2MRStoneBack");
    }

    D2ImageDrawStrc image = { 0 };
    image.pCellFile = D2MRStoneBack;
    image.nFrame = 0;

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2);

    // Draw background pieces
    const DWORD backWidth = 256;
    const DWORD backHeight = 256;

    for (int row = 0; (row * backHeight) < *D2CLIENT_ScreenSizeY; row++) {
        DWORD backBasePositionY = ((row + 1) * backHeight);

        for (int col = 0; (int)(basePositionX - (col * backWidth)) >= 0; col++) {
            image.nFrame = ((row % 2) * 2) + (col % 2);
            DWORD backBasePositionX = basePositionX - ((col + 1) * backWidth);

            D2GFX_DrawImage(&image, backBasePositionX, backBasePositionY, LeftPanelBackgroundColor, 5, nullptr);
        }
    }

    // Draw the ribbons only if the user has it enabled AND the game resolution allows the ribbons to be drawn without
    // problems.
    if (!EnableD2MRBackgroundRibbon && ((*D2CLIENT_ScreenSizeY - ((256 + 256 + 40) + 48)) <= (2 * (256 + 28)))) {
        return;
    }

    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    if (D2MRFancyBorderLeft == nullptr) {
        D2MRFancyBorderLeft = LoadCellFile("Panel/D2MRFancyBorderLeft");
    }

    if (D2MRFancyHorizontalBar == nullptr) {
        D2MRFancyHorizontalBar = LoadCellFile("Panel/D2MRFancyHorizontalBar");
    }

    if (D2MRFancyVerticalBar == nullptr) {
        D2MRFancyVerticalBar = LoadCellFile("Panel/D2MRFancyVerticalBar");
    }

    D2ImageDrawStrc borderLeft = { 0 };
    borderLeft.pCellFile = D2MRFancyBorderLeft;
    borderLeft.nFrame = 0;

    D2GFX_DrawImage(&borderLeft, (basePositionX - 60), (basePositionY + 256) + (256 + 256 + 40), LeftPanelBorderColor, 5, nullptr);
    borderLeft.nFrame++;
    D2GFX_DrawImage(&borderLeft, (basePositionX - 60), (basePositionY + 256 + 28), LeftPanelBorderColor, 5, nullptr);
    D2GFX_DrawImage(&borderLeft, (basePositionX - 60), (basePositionY), LeftPanelBorderColor, 5, nullptr);
    borderLeft.nFrame--;
    D2GFX_DrawImage(&borderLeft, (basePositionX - 60), (basePositionY - 28), LeftPanelBorderColor, 5, nullptr);

    D2ImageDrawStrc horizontalBar = { 0 };
    horizontalBar.pCellFile = D2MRFancyHorizontalBar;
    horizontalBar.nFrame = 2;

    D2GFX_DrawImage(&horizontalBar, (basePositionX - 400 - 35), (basePositionY + (256 + 256 + 40)), LeftPanelBorderColor, 5, nullptr);
    D2GFX_DrawImage(&horizontalBar, (basePositionX - 400 - 35), (basePositionY + 60), LeftPanelBorderColor, 5, nullptr);

    for (int i = 0; (basePositionX - 400 - 35) - (i * 256) >= 0; i++) {
        horizontalBar.nFrame = std::abs(i - 1) % 2;
        D2GFX_DrawImage(&horizontalBar, (basePositionX - 400 - 35) - ((i + 1) * 256), (basePositionY + (256 + 256 + 40)), LeftPanelBorderColor, 5, nullptr);
        D2GFX_DrawImage(&horizontalBar, (basePositionX - 400 - 35) - ((i + 1) * 256), (basePositionY + 60), LeftPanelBorderColor, 5, nullptr);
    }

    D2ImageDrawStrc verticalBar = { 0 };
    verticalBar.pCellFile = D2MRFancyVerticalBar;
    verticalBar.nFrame = 2;

    D2GFX_DrawImage(&verticalBar, (basePositionX - 400), (basePositionY), LeftPanelBorderColor, 5, nullptr);

    for (int i = 0; ((basePositionY - 35) - (i * 256)) >= 0; i++) {
        verticalBar.nFrame = std::abs(i - 1) % 2;
        D2GFX_DrawImage(&verticalBar, (basePositionX - 400), ((basePositionY - 35) - (i * 256)), LeftPanelBorderColor, 5, nullptr);
    }

    for (int i = 0; ((basePositionY + (256 + 256 + 40)) + (i * 256)) < (*D2CLIENT_ScreenSizeY); i++) {
        verticalBar.nFrame = i % 2;
        D2GFX_DrawImage(&verticalBar, (basePositionX - 400), ((basePositionY + (256 + 256 + 40)) + ((i + 1) * 256)), LeftPanelBorderColor, 5, nullptr);
    }
}

// Draws a background on opened right panels to cover up extra space.
void DrawUIRightPanelBackground() {
    if (D2MRStoneBack == nullptr) {
        D2MRStoneBack = LoadCellFile("Panel/D2MRStoneBack");
    }

    D2ImageDrawStrc image = { 0 };
    image.pCellFile = D2MRStoneBack;
    image.nFrame = 0;

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2);

    // Draw background pieces
    const DWORD backWidth = 256;
    const DWORD backHeight = 256;

    for (int row = 0; (row * backHeight) < *D2CLIENT_ScreenSizeY; row++) {
        DWORD backBasePositionY = ((row + 1) * backHeight);
        for (int col = 0; basePositionX + (col * backWidth) < *D2CLIENT_ScreenSizeX; col++) {
            image.nFrame = ((row % 2) * 2) + ((col + 1) % 2);
            DWORD backBasePositionX = basePositionX + (col * backWidth);

            D2GFX_DrawImage(&image, backBasePositionX, backBasePositionY, RightPanelBackgroundColor, 5, 0);
        }
    }

    // Draw the ribbons only if the user has it enabled AND the game resolution allows the ribbons to be drawn without
    // problems.
    if (!EnableD2MRBackgroundRibbon && ((*D2CLIENT_ScreenSizeY - ((256 + 256 + 40) + 48)) <= (2 * (256 + 28)))) {
        return;
    }

    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    if (D2MRFancyBorderRight == nullptr) {
        D2MRFancyBorderRight = LoadCellFile("Panel/D2MRFancyBorderRight");
    }

    if (D2MRFancyHorizontalBar == nullptr) {
        D2MRFancyHorizontalBar = LoadCellFile("Panel/D2MRFancyHorizontalBar");
    }

    if (D2MRFancyVerticalBar == nullptr) {
        D2MRFancyVerticalBar = LoadCellFile("Panel/D2MRFancyVerticalBar");
    }

    D2ImageDrawStrc borderRight = { 0 };
    borderRight.pCellFile = D2MRFancyBorderRight;
    borderRight.nFrame = 0;

    D2GFX_DrawImage(&borderRight, (basePositionX), (basePositionY + 256) + (256 + 256 + 40), RightPanelBorderColor, 5, nullptr);
    borderRight.nFrame++;
    D2GFX_DrawImage(&borderRight, (basePositionX), (basePositionY + 256 + 28), RightPanelBorderColor, 5, nullptr);
    D2GFX_DrawImage(&borderRight, (basePositionX), (basePositionY), RightPanelBorderColor, 5, nullptr);
    borderRight.nFrame--;
    D2GFX_DrawImage(&borderRight, (basePositionX), (basePositionY - 28), RightPanelBorderColor, 5, nullptr);

    D2ImageDrawStrc horizontalBar = { 0 };
    horizontalBar.pCellFile = D2MRFancyHorizontalBar;

    for (int i = 0; (basePositionX + 400) + (i * 256) < (*D2CLIENT_ScreenSizeX); i++) {
        horizontalBar.nFrame = i % 2;
        D2GFX_DrawImage(&horizontalBar, (basePositionX + 400) + (i * 256), (basePositionY + (256 + 256 + 40)), RightPanelBorderColor, 5, nullptr);
        D2GFX_DrawImage(&horizontalBar, (basePositionX + 400) + (i * 256), (basePositionY + 60), RightPanelBorderColor, 5, nullptr);
    }

    D2ImageDrawStrc verticalBar = { 0 };
    verticalBar.pCellFile = D2MRFancyVerticalBar;
    verticalBar.nFrame = 2;

    D2GFX_DrawImage(&verticalBar, (basePositionX + 400 - 60), (basePositionY), RightPanelBorderColor, 5, nullptr);

    for (int i = 0; ((basePositionY - 35) - (i * 256)) >= 0; i++) {
        verticalBar.nFrame = std::abs(i - 1) % 2;
        D2GFX_DrawImage(&verticalBar, (basePositionX + 400 - 60), ((basePositionY - 35) - (i * 256)), RightPanelBorderColor, 5, nullptr);
    }

    for (int i = 0; ((basePositionY + (256 + 256 + 40)) + (i * 256)) < (*D2CLIENT_ScreenSizeY); i++) {
        verticalBar.nFrame = i % 2;
        D2GFX_DrawImage(&verticalBar, (basePositionX + 400 - 60), ((basePositionY + (256 + 256 + 40)) + ((i + 1) * 256)), RightPanelBorderColor, 5, nullptr);
    }
}

void HD::DrawUIControlPanel() {
    if (D2MRFancyPanelLeft == nullptr) {
        D2MRFancyPanelLeft = InvertD2MRControlPanel ? LoadCellFile("Panel/D2MRFancyPanelInvertLeft") : LoadCellFile("Panel/D2MRFancyPanelLeft");
    }
    if (D2MRFancyPanelRight == nullptr) {
        D2MRFancyPanelRight = InvertD2MRControlPanel ? LoadCellFile("Panel/D2MRFancyPanelInvertRight") : LoadCellFile("Panel/D2MRFancyPanelRight");
    }
    if (D2MRFancyPanelBar == nullptr) {
        D2MRFancyPanelBar = InvertD2MRControlPanel ? LoadCellFile("Panel/D2MRFancyPanelInvertBar") : LoadCellFile("Panel/D2MRFancyPanelBar");
    }

    D2ImageDrawStrc panelLeft = { 0 };
    panelLeft.pCellFile = D2MRFancyPanelLeft;
    panelLeft.nFrame = 0;
    D2GFX_DrawImage(&panelLeft, (117 + 48), *D2CLIENT_ScreenSizeY - 1, 0xFFFFFFFF, 5, 0);

    D2ImageDrawStrc panelRight = { 0 };
    panelRight.pCellFile = D2MRFancyPanelRight;
    panelRight.nFrame = 0;
    D2GFX_DrawImage(&panelRight, (*D2CLIENT_ScreenSizeX - 117 - 48 - 238), *D2CLIENT_ScreenSizeY - 1, 0xFFFFFFFF, 5, 0);

    D2ImageDrawStrc panelBar = { 0 };
    panelBar.pCellFile = D2MRFancyPanelBar;
    panelBar.nFrame = 0;

    for (int i = 0; ((i * 254) + (117 + 48 + 238)) < ((*D2CLIENT_ScreenSizeX / 2) - 128); i++) {
        D2GFX_DrawImage(&panelBar, ((i * 254) + (117 + 48 + 238)), *D2CLIENT_ScreenSizeY - 1, 0xFFFFFFFF, 5, 0);
    }

    for (int i = 0; ((*D2CLIENT_ScreenSizeX - 117 - 48 - 238) - (i * 254)) > ((*D2CLIENT_ScreenSizeX / 2) + 128); i++) {
        D2GFX_DrawImage(&panelBar, ((*D2CLIENT_ScreenSizeX - 117 - 48 - 238) - ((i + 1) * 254)), *D2CLIENT_ScreenSizeY - 1, 0xFFFFFFFF, 5, 0);
    }
}
