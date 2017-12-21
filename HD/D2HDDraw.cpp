/****************************************************************************
*                                                                           *
*   D2HDDraw.cpp                                                            *
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
*   Defines the functions that corrects standard Diablo II draw functions   *
*   to work with higher resolutions. It also defines new draw calls to      *
*   imitate the look of D2MultiRes.                                         *
*                                                                           *
*****************************************************************************/

#include "D2HDDraw.h"
#include "../DLLmain.h"
#include "../D2Ptrs.h"

void DrawUILeftPanelBackground();
void DrawUIRightPanelBackground();
void RedrawUILeftPanelBorders_D2MR();
void RedrawUILeftPanelBorders_Original();
void RedrawUIRightPanelBorders_D2MR();
void RedrawUIRightPanelBorders_Original();
void UnloadCellFiles();

// Redraws the left side panel borders in the correct places, independent of resolution.
void HD::RedrawUILeftPanelBorders() {
    __asm push edi

    if (EnableD2MRPanelBorderStyle) {
        RedrawUILeftPanelBorders_D2MR();
    } else {
        RedrawUILeftPanelBorders_Original();
    }

    __asm pop edi
}

// Redraws the right side panel borders in the correct places, independent of resolution.
void HD::RedrawUIRightPanelBorders() {
    __asm push edi

    if (EnableD2MRPanelBorderStyle) {
        RedrawUIRightPanelBorders_D2MR();
    } else {
        RedrawUIRightPanelBorders_Original();
    }

    __asm pop edi
}

void RedrawUIRightPanelBorders_D2MR() {
    if (D2MRFancyBorderInterfaceRight == nullptr) {
        D2MRFancyBorderInterfaceRight = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderInterfaceRight", 0);
    }
    if (D2MRFancyBorderBottom == nullptr) {
        D2MRFancyBorderBottom = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderBottom", 0);
    }
    if (D2MRFancyBorderTop == nullptr) {
        D2MRFancyBorderTop = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderTop", 0);
    }
    if (D2MRFancyBorderCorner == nullptr) {
        D2MRFancyBorderCorner = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderCorner", 0);
    }

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2);
    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    // Draw top border pieces
    CellContext borderTop = { 0 };
    borderTop.nFrame = 0;
    borderTop.pCellFile = D2MRFancyBorderTop;

    D2GFX_DrawCellContext(&borderTop, (basePositionX + 60), (basePositionY + 60), RightPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderTop.nFrame++;
    D2GFX_DrawCellContext(&borderTop, (basePositionX + 60) + 256, (basePositionY + 60), RightPanelBorderColor.getBGRFormat(), 5, nullptr);


    // Draw bottom border pieces
    CellContext borderBottom = { 0 };
    borderBottom.nFrame = 0;
    borderBottom.pCellFile = D2MRFancyBorderBottom;

    D2GFX_DrawCellContext(&borderBottom, (basePositionX + 60), (basePositionY + 256) + (256 + 40), RightPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderBottom.nFrame++;
    D2GFX_DrawCellContext(&borderBottom, (basePositionX + 60) + 256, (basePositionY + 256) + (256 + 40), RightPanelBorderColor.getBGRFormat(), 5, nullptr);

    // Draw corner border pieces
    CellContext borderCorner = { 0 };
    borderCorner.nFrame = 0;
    borderCorner.pCellFile = D2MRFancyBorderCorner;

    D2GFX_DrawCellContext(&borderCorner, (basePositionX), (basePositionY + 60), RightPanelBorderColor.getBGRFormat(), 5, nullptr);
    D2GFX_DrawCellContext(&borderCorner, (basePositionX), (basePositionY + 256) + (256 + 40), RightPanelBorderColor.getBGRFormat(), 5, nullptr);

    // Draw left border pieces
    CellContext borderRight = { 0 };
    borderRight.nFrame = 0;
    borderRight.pCellFile = D2MRFancyBorderInterfaceRight;

    D2GFX_DrawCellContext(&borderRight, (basePositionX + 320), (basePositionY + 256), RightPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderRight.nFrame++;
    D2GFX_DrawCellContext(&borderRight, (basePositionX + 320), (basePositionY + 256) + 256, RightPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderRight.nFrame++;
    D2GFX_DrawCellContext(&borderRight, (basePositionX + 320), (basePositionY + 256) + (256 + 40), RightPanelBorderColor.getBGRFormat(), 5, nullptr);
}

void RedrawUIRightPanelBorders_Original() {
    if (*D2CLIENT_PanelBorderImage == nullptr) {
        *D2CLIENT_PanelBorderImage = STUB_D2CLIENT_LoadCellFile("Panel\\800BorderFrame");
    }

    CellContext cellContext = { 0 };
    cellContext.pCellFile = *D2CLIENT_PanelBorderImage;
    cellContext.nFrame = 5;

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2);
    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    // Frame 5
    D2GFX_DrawCellContext(&cellContext, basePositionX, basePositionY + 63, RightPanelBorderColor.getBGRFormat(), 5, 0);
    cellContext.nFrame++;

    // Frame 6
    D2GFX_DrawCellContext(&cellContext, basePositionX + 144, basePositionY + 253, RightPanelBorderColor.getBGRFormat(), 5, 0);
    cellContext.nFrame++;

    // Frame 7
    D2GFX_DrawCellContext(&cellContext, basePositionX + 313, basePositionY + 484, RightPanelBorderColor.getBGRFormat(), 5, 0);
    cellContext.nFrame++;

    // Frame 8
    D2GFX_DrawCellContext(&cellContext, basePositionX + 144, basePositionY + 553, RightPanelBorderColor.getBGRFormat(), 5, 0);
    cellContext.nFrame++;

    // Frame 9
    D2GFX_DrawCellContext(&cellContext, basePositionX, basePositionY + 553, RightPanelBorderColor.getBGRFormat(), 5, 0);
    cellContext.nFrame++;
}

void RedrawUILeftPanelBorders_Original() {
    if (*D2CLIENT_PanelBorderImage == nullptr) {
        *D2CLIENT_PanelBorderImage = STUB_D2CLIENT_LoadCellFile("Panel\\800BorderFrame");
    }

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2) - 400;
    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    CellContext cellContext = { 0 };
    cellContext.pCellFile = *D2CLIENT_PanelBorderImage;
    cellContext.nFrame = 0;

    // Frame 0
    D2GFX_DrawCellContext(&cellContext, basePositionX, basePositionY + 253, LeftPanelBorderColor.getBGRFormat(), 5, 0);
    cellContext.nFrame++;

    // Frame 1
    D2GFX_DrawCellContext(&cellContext, basePositionX + 256, basePositionY + 63, LeftPanelBorderColor.getBGRFormat(), 5, 0);
    cellContext.nFrame++;

    // Frame 2
    D2GFX_DrawCellContext(&cellContext, basePositionX, basePositionY + 484, LeftPanelBorderColor.getBGRFormat(), 5, 0);
    cellContext.nFrame++;

    // Frame 3
    D2GFX_DrawCellContext(&cellContext, basePositionX, basePositionY + 553, LeftPanelBorderColor.getBGRFormat(), 5, 0);
    cellContext.nFrame++;

    // Frame 4
    D2GFX_DrawCellContext(&cellContext, basePositionX + 256, basePositionY + 553, LeftPanelBorderColor.getBGRFormat(), 5, 0);
    cellContext.nFrame++;
}

void RedrawUILeftPanelBorders_D2MR() {
    if (D2MRFancyBorderInterfaceLeft == nullptr) {
        D2MRFancyBorderInterfaceLeft = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderInterfaceLeft", 0);
    }
    if (D2MRFancyBorderBottom == nullptr) {
        D2MRFancyBorderBottom = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderBottom", 0);
    }
    if (D2MRFancyBorderTop == nullptr) {
        D2MRFancyBorderTop = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderTop", 0);
    }
    if (D2MRFancyBorderCorner == nullptr) {
        D2MRFancyBorderCorner = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderCorner", 0);
    }

    int basePositionX = (*D2CLIENT_ScreenSizeX / 2) - 400;
    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    // Draw top border pieces
    CellContext borderTop = { 0 };
    borderTop.nFrame = 0;
    borderTop.pCellFile = D2MRFancyBorderTop;

    D2GFX_DrawCellContext(&borderTop, (basePositionX + 56), (basePositionY + 60), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderTop.nFrame++;
    D2GFX_DrawCellContext(&borderTop, (basePositionX + 56) + 256, (basePositionY + 60), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);


    // Draw bottom border pieces
    CellContext borderBottom = { 0 };
    borderBottom.nFrame = 0;
    borderBottom.pCellFile = D2MRFancyBorderBottom;

    D2GFX_DrawCellContext(&borderBottom, (basePositionX + 56), (basePositionY + 256) + (256 + 40), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderBottom.nFrame++;
    D2GFX_DrawCellContext(&borderBottom, (basePositionX + 56) + 256, (basePositionY + 256) + (256 + 40), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);

    // Draw corner border pieces
    CellContext borderCorner = { 0 };
    borderCorner.nFrame = 0;
    borderCorner.pCellFile = D2MRFancyBorderCorner;

    D2GFX_DrawCellContext(&borderCorner, (basePositionX + 56) + 284, (basePositionY + 60), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
    D2GFX_DrawCellContext(&borderCorner, (basePositionX + 56) + 284, (basePositionY)+(256 + 256 + 40), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);

    // Draw left border pieces
    CellContext borderLeft = { 0 };
    borderLeft.nFrame = 0;
    borderLeft.pCellFile = D2MRFancyBorderInterfaceLeft;

    D2GFX_DrawCellContext(&borderLeft, basePositionX, (basePositionY + 256), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderLeft.nFrame++;
    D2GFX_DrawCellContext(&borderLeft, basePositionX, (basePositionY + 256) + 256, LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderLeft.nFrame++;
    D2GFX_DrawCellContext(&borderLeft, basePositionX, (basePositionY + 256) + (256 + 40), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
}

void __declspec(naked) HD::STUB_DrawUIPanelBackground() {
    __asm {
        PUSHAD
        CALL[HD::DrawUIPanelBackground]
        POPAD
        ADD ESP, 0x128
        RET
    }
}

void HD::DrawUIPanelBackground() {
    switch (*D2CLIENT_PanelOpenMode) {
    case 1:
        DrawUIRightPanelBackground();
        RedrawUIRightPanelBorders();
        break;

    case 2:
        DrawUILeftPanelBackground();
        RedrawUILeftPanelBorders();
        break;

    case 3:
        DrawUILeftPanelBackground();
        DrawUIRightPanelBackground();

        RedrawUILeftPanelBorders();
        RedrawUIRightPanelBorders();
        break;

    default:
        break;
    }
}

// Draws a background on opened left panels to cover up extra space.
void DrawUILeftPanelBackground() {
    if (D2MRStoneBack == nullptr) {
        D2MRStoneBack = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRStoneBack", 0);
    }

    CellContext image = { 0 };
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

            D2GFX_DrawCellContext(&image, backBasePositionX, backBasePositionY, LeftPanelBackgroundColor.getBGRFormat(), 5, nullptr);
        }
    }

    // Draw the ribbons only if the user has it enabled AND the game resolution allows the ribbons to be drawn without
    // problems.
    if (!EnableD2MRBackgroundRibbon && ((*D2CLIENT_ScreenSizeY - ((256 + 256 + 40) + 48)) <= (2 * (256 + 28)))) {
        return;
    }

    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    if (D2MRFancyBorderLeft == nullptr) {
        D2MRFancyBorderLeft = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderLeft", 0);
    }

    if (D2MRFancyHorizontalBar == nullptr) {
        D2MRFancyHorizontalBar = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyHorizontalBar", 0);
    }

    if (D2MRFancyVerticalBar == nullptr) {
        D2MRFancyVerticalBar = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyVerticalBar", 0);
    }

    CellContext borderLeft = { 0 };
    borderLeft.pCellFile = D2MRFancyBorderLeft;
    borderLeft.nFrame = 0;

    D2GFX_DrawCellContext(&borderLeft, (basePositionX - 60), (basePositionY + 256) + (256 + 256 + 40), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderLeft.nFrame++;
    D2GFX_DrawCellContext(&borderLeft, (basePositionX - 60), (basePositionY + 256 + 28), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
    D2GFX_DrawCellContext(&borderLeft, (basePositionX - 60), (basePositionY), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderLeft.nFrame--;
    D2GFX_DrawCellContext(&borderLeft, (basePositionX - 60), (basePositionY - 28), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);

    CellContext horizontalBar = { 0 };
    horizontalBar.pCellFile = D2MRFancyHorizontalBar;
    horizontalBar.nFrame = 2;

    D2GFX_DrawCellContext(&horizontalBar, (basePositionX - 400 - 35), (basePositionY + (256 + 256 + 40)), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
    D2GFX_DrawCellContext(&horizontalBar, (basePositionX - 400 - 35), (basePositionY + 60), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);

    for (int i = 0; (basePositionX - 400 - 35) - (i * 256) >= 0; i++) {
        horizontalBar.nFrame = std::abs(i - 1) % 2;
        D2GFX_DrawCellContext(&horizontalBar, (basePositionX - 400 - 35) - ((i + 1) * 256), (basePositionY + (256 + 256 + 40)), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
        D2GFX_DrawCellContext(&horizontalBar, (basePositionX - 400 - 35) - ((i + 1) * 256), (basePositionY + 60), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
    }

    CellContext verticalBar = { 0 };
    verticalBar.pCellFile = D2MRFancyVerticalBar;
    verticalBar.nFrame = 2;

    D2GFX_DrawCellContext(&verticalBar, (basePositionX - 400), (basePositionY), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);

    for (int i = 0; ((basePositionY - 35) - (i * 256)) >= 0; i++) {
        verticalBar.nFrame = std::abs(i - 1) % 2;
        D2GFX_DrawCellContext(&verticalBar, (basePositionX - 400), ((basePositionY - 35) - (i * 256)), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
    }

    for (int i = 0; ((basePositionY + (256 + 256 + 40)) + (i * 256)) < (*D2CLIENT_ScreenSizeY); i++) {
        verticalBar.nFrame = i % 2;
        D2GFX_DrawCellContext(&verticalBar, (basePositionX - 400), ((basePositionY + (256 + 256 + 40)) + ((i + 1) * 256)), LeftPanelBorderColor.getBGRFormat(), 5, nullptr);
    }
}

// Draws a background on opened right panels to cover up extra space.
void DrawUIRightPanelBackground() {
    if (D2MRStoneBack == nullptr) {
        D2MRStoneBack = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRStoneBack", 0);
    }

    CellContext image = { 0 };
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

            D2GFX_DrawCellContext(&image, backBasePositionX, backBasePositionY, RightPanelBackgroundColor.getBGRFormat(), 5, 0);
        }
    }

    // Draw the ribbons only if the user has it enabled AND the game resolution allows the ribbons to be drawn without
    // problems.
    if (!EnableD2MRBackgroundRibbon && ((*D2CLIENT_ScreenSizeY - ((256 + 256 + 40) + 48)) <= (2 * (256 + 28)))) {
        return;
    }

    int basePositionY = (*D2CLIENT_ScreenSizeY / 2) - 300;

    if (D2MRFancyBorderRight == nullptr) {
        D2MRFancyBorderRight = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyBorderRight", 0);
    }

    if (D2MRFancyHorizontalBar == nullptr) {
        D2MRFancyHorizontalBar = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyHorizontalBar", 0);
    }

    if (D2MRFancyVerticalBar == nullptr) {
        D2MRFancyVerticalBar = D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyVerticalBar", 0);
    }

    CellContext borderRight = { 0 };
    borderRight.pCellFile = D2MRFancyBorderRight;
    borderRight.nFrame = 0;

    D2GFX_DrawCellContext(&borderRight, (basePositionX), (basePositionY + 256) + (256 + 256 + 40), RightPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderRight.nFrame++;
    D2GFX_DrawCellContext(&borderRight, (basePositionX), (basePositionY + 256 + 28), RightPanelBorderColor.getBGRFormat(), 5, nullptr);
    D2GFX_DrawCellContext(&borderRight, (basePositionX), (basePositionY), RightPanelBorderColor.getBGRFormat(), 5, nullptr);
    borderRight.nFrame--;
    D2GFX_DrawCellContext(&borderRight, (basePositionX), (basePositionY - 28), RightPanelBorderColor.getBGRFormat(), 5, nullptr);

    CellContext horizontalBar = { 0 };
    horizontalBar.pCellFile = D2MRFancyHorizontalBar;

    for (int i = 0; (basePositionX + 400) + (i * 256) < (*D2CLIENT_ScreenSizeX); i++) {
        horizontalBar.nFrame = i % 2;
        D2GFX_DrawCellContext(&horizontalBar, (basePositionX + 400) + (i * 256), (basePositionY + (256 + 256 + 40)), RightPanelBorderColor.getBGRFormat(), 5, nullptr);
        D2GFX_DrawCellContext(&horizontalBar, (basePositionX + 400) + (i * 256), (basePositionY + 60), RightPanelBorderColor.getBGRFormat(), 5, nullptr);
    }

    CellContext verticalBar = { 0 };
    verticalBar.pCellFile = D2MRFancyVerticalBar;
    verticalBar.nFrame = 2;

    D2GFX_DrawCellContext(&verticalBar, (basePositionX + 400 - 60), (basePositionY), RightPanelBorderColor.getBGRFormat(), 5, nullptr);

    for (int i = 0; ((basePositionY - 35) - (i * 256)) >= 0; i++) {
        verticalBar.nFrame = std::abs(i - 1) % 2;
        D2GFX_DrawCellContext(&verticalBar, (basePositionX + 400 - 60), ((basePositionY - 35) - (i * 256)), RightPanelBorderColor.getBGRFormat(), 5, nullptr);
    }

    for (int i = 0; ((basePositionY + (256 + 256 + 40)) + (i * 256)) < (*D2CLIENT_ScreenSizeY); i++) {
        verticalBar.nFrame = i % 2;
        D2GFX_DrawCellContext(&verticalBar, (basePositionX + 400 - 60), ((basePositionY + (256 + 256 + 40)) + ((i + 1) * 256)), RightPanelBorderColor.getBGRFormat(), 5, nullptr);
    }
}

void __declspec(naked) HD::STUB_DrawUIControlPanel() {
    __asm {
        PUSHAD
        CALL[HD::DrawUIControlPanel]
        POPAD
        XOR EDI, EDI
        SUB EAX, 02
        RET
    }
}

void HD::DrawUIControlPanel() {
    if (D2MRFancyPanelLeft == nullptr) {
        D2MRFancyPanelLeft = InvertD2MRControlPanel ? D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyPanelInvertLeft", 0) : D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyPanelLeft", 0);
    }
    if (D2MRFancyPanelRight == nullptr) {
        D2MRFancyPanelRight = InvertD2MRControlPanel ? D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyPanelInvertRight", 0) : D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyPanelRight", 0);
    }
    if (D2MRFancyPanelBar == nullptr) {
        D2MRFancyPanelBar = InvertD2MRControlPanel ? D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyPanelInvertBar", 0) : D2WIN_LoadCellFile("data\\global\\ui\\Panel\\D2MRFancyPanelBar", 0);
    }

    CellContext panelLeft = { 0 };
    panelLeft.pCellFile = D2MRFancyPanelLeft;
    panelLeft.nFrame = 0;
    D2GFX_DrawCellContext(&panelLeft, (117 + 48), *D2CLIENT_ScreenSizeY - 1, 0xFFFFFFFF, 5, 0);

    CellContext panelRight = { 0 };
    panelRight.pCellFile = D2MRFancyPanelRight;
    panelRight.nFrame = 0;
    D2GFX_DrawCellContext(&panelRight, (*D2CLIENT_ScreenSizeX - 117 - 48 - 238), *D2CLIENT_ScreenSizeY - 1, 0xFFFFFFFF, 5, 0);

    CellContext panelBar = { 0 };
    panelBar.pCellFile = D2MRFancyPanelBar;
    panelBar.nFrame = 0;

    for (int i = 0; ((i * 254) + (117 + 48 + 238)) < ((*D2CLIENT_ScreenSizeX / 2) - 128); i++) {
        D2GFX_DrawCellContext(&panelBar, ((i * 254) + (117 + 48 + 238)), *D2CLIENT_ScreenSizeY - 1, 0xFFFFFFFF, 5, 0);
    }

    for (int i = 0; ((*D2CLIENT_ScreenSizeX - 117 - 48 - 238) - (i * 254)) > ((*D2CLIENT_ScreenSizeX / 2) + 128); i++) {
        D2GFX_DrawCellContext(&panelBar, ((*D2CLIENT_ScreenSizeX - 117 - 48 - 238) - ((i + 1) * 254)), *D2CLIENT_ScreenSizeY - 1, 0xFFFFFFFF, 5, 0);
    }
}

void UnloadCellFile(CellFile** ppCellFile) {
    if (*ppCellFile != nullptr) {
        D2CMP_FreeCellFile(*ppCellFile);
        FOG_FreeClientMemory(*ppCellFile, __FILE__, __LINE__, nullptr);

        *ppCellFile = nullptr;
    }
}

void UnloadCellFiles() {
    UnloadCellFile(&D2MRStoneBack);
    UnloadCellFile(&D2MRFancyBorderBottom);
    UnloadCellFile(&D2MRFancyBorderCorner);
    UnloadCellFile(&D2MRFancyBorderInterfaceLeft);
    UnloadCellFile(&D2MRFancyBorderInterfaceRight);
    UnloadCellFile(&D2MRFancyBorderLeft);
    UnloadCellFile(&D2MRFancyBorderRight);
    UnloadCellFile(&D2MRFancyBorderTop);
    UnloadCellFile(&D2MRFancyHorizontalBar);
    UnloadCellFile(&D2MRFancyPanelBar);
    UnloadCellFile(&D2MRFancyPanelLeft);
    UnloadCellFile(&D2MRFancyPanelRight);
    UnloadCellFile(&D2MRFancyVerticalBar);
    UnloadCellFile(&Blank);
}

void __declspec(naked) HD::STUB_UnloadCellFiles() {
    __asm {
        CALL [UnloadCellFiles]
        MOV EAX, [D2CLIENT_PanelBorderImage]
        MOV ESI, [EAX]
        RET
    }
}

void __declspec(naked) HD::STUB_DetermineText() {
    __asm {
        MOV ECX, [EAX + ECX * 4 + 0x00000540]
        PUSH EAX
        PUSH EBX
        PUSH EDX
        PUSH ESI
        PUSH EDI
        CALL[HD::DetermineText]
        MOV ECX, EAX
        POP EDI
        POP ESI
        POP EDX
        POP EBX
        POP EAX
        RET
    }
}

void* HD::DetermineText() {
    void* assetValueA;
    DWORD assetValueB;
    void* assetValueC;
    void* returnValue;

    __asm {
        MOV assetValueA, EAX
        MOV assetValueB, ESI
        MOV assetValueC, ECX
    }

    if (Blank == nullptr) {
        Blank = D2WIN_LoadCellFile("data\\local\\UI\\ENG\\Blank", 0);
    }

    if (*D2CLIENT_CurrentRegistryResolutionMode >= 3 && assetValueA == D2CLIENT_VideoOptionCellFileStart && assetValueB == 0x154) {
        returnValue = Blank;
    } else {
        returnValue = assetValueC;
    }

    return returnValue;
}
