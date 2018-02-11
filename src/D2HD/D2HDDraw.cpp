/*****************************************************************************
 *                                                                           *
 *   D2HDDraw.cpp                                                            *
 *   Copyright (C) 2017 Mir Drualga                                          *
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

/*==========================================================
* D2Ex2
* https://github.com/lolet/D2Ex2
* ==========================================================
* Copyright (c) 2011-2014 Bartosz Jankowski
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
* ==========================================================
*/

#include "D2HDDraw.h"

HANDLE D2HD::Draw::d2mrArchive = nullptr;
D2HD::D2HDCellContext D2HD::Draw::blankCellFile("data\\local\\UI\\ENG\\Blank");

D2HD::D2HDCellContext D2HD::Draw::d2mrFancyBorderCorner("data\\global\\ui\\Panel\\D2MRFancyBorderCorner");
D2HD::D2HDCellContext D2HD::Draw::neoD2MRFancyBorderCornerBottomLeft("data\\global\\ui\\Panel\\NeoD2MRFancyBorderCornerBottomLeft");
D2HD::D2HDCellContext D2HD::Draw::neoD2MRFancyBorderCornerBottomRight("data\\global\\ui\\Panel\\NeoD2MRFancyBorderCornerBottomRight");
D2HD::D2HDCellContext D2HD::Draw::neoD2MRFancyBorderCornerTopLeft("data\\global\\ui\\Panel\\NeoD2MRFancyBorderCornerTopLeft");
D2HD::D2HDCellContext D2HD::Draw::neoD2MRFancyBorderCornerTopRight("data\\global\\ui\\Panel\\NeoD2MRFancyBorderCornerTopRight");

D2HD::D2HDCellContext D2HD::Draw::d2mrFancyBorderInterfaceLeft("data\\global\\ui\\Panel\\D2MRFancyBorderInterfaceLeft");
D2HD::D2HDCellContext D2HD::Draw::d2mrFancyBorderInterfaceRight("data\\global\\ui\\Panel\\D2MRFancyBorderInterfaceRight");
D2HD::D2HDCellContext D2HD::Draw::neoD2MRFancyBorderInterfaceLeft("data\\global\\ui\\Panel\\NeoD2MRFancyBorderInterfaceLeft");
D2HD::D2HDCellContext D2HD::Draw::neoD2MRFancyBorderInterfaceRight("data\\global\\ui\\Panel\\NeoD2MRFancyBorderInterfaceRight");

D2HD::D2HDCellContext D2HD::Draw::d2mrFancyBorderLeft("data\\global\\ui\\Panel\\D2MRFancyBorderLeft");
D2HD::D2HDCellContext D2HD::Draw::d2mrFancyBorderRight("data\\global\\ui\\Panel\\D2MRFancyBorderRight");

D2HD::D2HDCellContext D2HD::Draw::d2mrFancyBorderBottom("data\\global\\ui\\Panel\\D2MRFancyBorderBottom");
D2HD::D2HDCellContext D2HD::Draw::d2mrFancyBorderTop("data\\global\\ui\\Panel\\D2MRFancyBorderTop");
D2HD::D2HDCellContext D2HD::Draw::neoD2MRFancyBorderBottomLeft("data\\global\\ui\\Panel\\NeoD2MRFancyBorderBottomLeft");
D2HD::D2HDCellContext D2HD::Draw::neoD2MRFancyBorderBottomRight("data\\global\\ui\\Panel\\NeoD2MRFancyBorderBottomRight");
D2HD::D2HDCellContext D2HD::Draw::neoD2MRFancyBorderTopLeft("data\\global\\ui\\Panel\\NeoD2MRFancyBorderTopLeft");
D2HD::D2HDCellContext D2HD::Draw::neoD2MRFancyBorderTopRight("data\\global\\ui\\Panel\\NeoD2MRFancyBorderTopRight");

D2HD::D2HDCellContext D2HD::Draw::d2mrFancyHorizontalBar("data\\global\\ui\\Panel\\D2MRFancyHorizontalBar");
D2HD::D2HDCellContext D2HD::Draw::d2mrFancyVerticalBar("data\\global\\ui\\Panel\\D2MRFancyVerticalBar");

D2HD::D2HDCellContext D2HD::Draw::d2mrFancyPanelHorizontalBar("data\\global\\ui\\Panel\\D2MRFancyPanelHorizontalBar");
D2HD::D2HDCellContext D2HD::Draw::d2mrFancyPanelVerticalBar("data\\global\\ui\\Panel\\D2MRFancyPanelVerticalBar");
D2HD::D2HDCellContext D2HD::Draw::d2mrFancyPanelFlipHorizontalBar("data\\global\\ui\\Panel\\D2MRFancyPanelFlipHorizontalBar");
D2HD::D2HDCellContext D2HD::Draw::d2mrFancyPanelFlipVerticalBar("data\\global\\ui\\Panel\\D2MRFancyPanelFlipVerticalBar");

D2HD::D2HDCellContext D2HD::Draw::d2mrFancyPanelLeft("data\\global\\ui\\Panel\\D2MRFancyPanelLeft");
D2HD::D2HDCellContext D2HD::Draw::d2mrFancyPanelRight("data\\global\\ui\\Panel\\D2MRFancyPanelRight");
D2HD::D2HDCellContext D2HD::Draw::d2mrFancyPanelFlipLeft("data\\global\\ui\\Panel\\D2MRFancyPanelFlipLeft");
D2HD::D2HDCellContext D2HD::Draw::d2mrFancyPanelFlipRight("data\\global\\ui\\Panel\\D2MRFancyPanelFlipRight");

D2HD::D2HDCellContext D2HD::Draw::d2mrStoneBack("data\\global\\ui\\Panel\\D2MRStoneBack");
D2HD::D2HDCellContext D2HD::Draw::resolution1068x600Text("data\\local\\UI\\ENG\\1068x600");
D2HD::D2HDCellContext D2HD::Draw::resolution1344x700Text("data\\local\\UI\\ENG\\1344x700");

void __stdcall D2HD::Draw::determineVideoOptionText(struct CellFile**
        outCellFile, void* baseAddress, unsigned int offset,
        struct CellFile* defaultCellFile) {

    blankCellFile.loadFileSafely();
    resolution1068x600Text.loadFileSafely();
    resolution1344x700Text.loadFileSafely();

    if (baseAddress == D2CLIENT_VideoOptionCellFileStart && offset == 0x154) {
        if ((*D2CLIENT_WindowWidth == 640 && *D2CLIENT_WindowHeight == 480)
                || (*D2CLIENT_WindowWidth == 800 && *D2CLIENT_WindowHeight == 600)) {
            *outCellFile = defaultCellFile;
        } else if (*D2CLIENT_WindowWidth == 1068 && *D2CLIENT_WindowHeight == 600) {
            *outCellFile = resolution1068x600Text.getCellFilePtr();
        } else if (*D2CLIENT_WindowWidth == 1344 && *D2CLIENT_WindowHeight == 700) {
            *outCellFile = resolution1344x700Text.getCellFilePtr();
        } else {
            *outCellFile = blankCellFile.getCellFilePtr();
        }
    } else {
        *outCellFile = defaultCellFile;
    }
}

void D2HD::Draw::drawControlPanelBackground() {
    D2HD::D2HDCellContext& panelLeft = config.isFlipD2MRControlPanel() ? d2mrFancyPanelFlipLeft : d2mrFancyPanelLeft;
    D2HD::D2HDCellContext& panelRight = config.isFlipD2MRControlPanel() ? d2mrFancyPanelFlipRight : d2mrFancyPanelRight;
    D2HD::D2HDCellContext& panelHorizontalBar = config.isFlipD2MRControlPanel() ? d2mrFancyPanelFlipHorizontalBar : d2mrFancyPanelHorizontalBar;

    panelLeft.loadFileSafely();
    panelRight.loadFileSafely();
    panelHorizontalBar.loadFileSafely();

    panelLeft.draw((117 + 48), *D2CLIENT_WindowHeight - 1, 0xFFFFFFFF, 5, 0);
    panelRight.draw((*D2CLIENT_WindowWidth - 117 - 48 - 238), *D2CLIENT_WindowHeight - 1, 0xFFFFFFFF, 5, nullptr);

    for (int i = 0; ((i * 254) + (117 + 48 + 238)) < ((*D2CLIENT_WindowWidth / 2) - 128); i++) {
        panelHorizontalBar.draw(((i * 254) + (117 + 48 + 238)), *D2CLIENT_WindowHeight - 1, 0xFFFFFFFF, 5, nullptr);
    }

    for (int i = 0; ((*D2CLIENT_WindowWidth - 117 - 48 - 238) - (i * 254)) > ((*D2CLIENT_WindowWidth / 2) + 128); i++) {
        panelHorizontalBar.draw(((*D2CLIENT_WindowWidth - 117 - 48 - 238) - ((i + 1) * 254)), *D2CLIENT_WindowHeight - 1, 0xFFFFFFFF, 5, nullptr);
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
    d2mrStoneBack.loadFileSafely();

    int basePositionX = (*D2CLIENT_WindowWidth / 2);

    // Draw background pieces
    const int backWidth = 256;
    const int backHeight = 256;

    for (int row = 0; (row * backHeight) < *D2CLIENT_WindowHeight; row++) {
        int backBasePositionY = ((row + 1) * backHeight);

        for (int col = 0; (int)(basePositionX - (col * backWidth)) >= 0; col++) {
            d2mrStoneBack.setFrame(((row % 2) * 2) + (col % 2));
            int backBasePositionX = basePositionX - ((col + 1) * backWidth);

            d2mrStoneBack.draw(backBasePositionX, backBasePositionY, config.getLeftPanelBackgroundColor().getBGRFormat(), 5, nullptr);
        }
    }

    // Draw the ribbons only if the user has it enabled AND the game resolution allows the ribbons to be drawn without
    // problems.
    if (!config.isEnableD2MRBackgroundRibbon()
            && ((*D2CLIENT_WindowHeight - ((256 + 256 + 40) + 48)) <= (2 * (256 + 28)))) {
        return;
    }

    int basePositionY = (*D2CLIENT_WindowHeight / 2) - 300;

    d2mrFancyBorderLeft.loadFileSafely();
    d2mrFancyHorizontalBar.loadFileSafely();
    d2mrFancyVerticalBar.loadFileSafely();

    d2mrFancyBorderLeft.setFrame(0);
    d2mrFancyBorderLeft.draw((basePositionX - 60), (basePositionY + 256) + (256 + 256 + 40), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    d2mrFancyBorderLeft.setFrame(1);
    d2mrFancyBorderLeft.draw((basePositionX - 60), (basePositionY + 256 + 28) + (256 + 256 + 40), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);

    d2mrFancyBorderLeft.draw((basePositionX - 60), (basePositionY), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    d2mrFancyBorderLeft.setFrame(0);
    d2mrFancyBorderLeft.draw((basePositionX - 60), (basePositionY - 28), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);

    if (!config.isEnableD2MRPanelBorderStyle()) {
        basePositionX += 2;
    }

    d2mrFancyHorizontalBar.setFrame(2);

    d2mrFancyHorizontalBar.draw((basePositionX - 400 - 35), (basePositionY + (256 + 256 + 40)), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    d2mrFancyHorizontalBar.draw((basePositionX - 400 - 35), (basePositionY + 60), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);

    for (int i = 0; (basePositionX - 400 - 35) - (i * 256) >= 0; i++) {
        d2mrFancyHorizontalBar.setFrame(std::abs(i - 1) % 2);
        d2mrFancyHorizontalBar.draw((basePositionX - 400 - 35) - ((i + 1) * 256), (basePositionY + (256 + 256 + 40)), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
        d2mrFancyHorizontalBar.draw((basePositionX - 400 - 35) - ((i + 1) * 256), (basePositionY + 60), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    }

    d2mrFancyVerticalBar.setFrame(2);

    d2mrFancyVerticalBar.draw((basePositionX - 400), (basePositionY), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);

    for (int i = 0; ((basePositionY - 35) - (i * 256)) >= 0; i++) {
        d2mrFancyVerticalBar.setFrame(std::abs(i - 1) % 2);
        d2mrFancyVerticalBar.draw((basePositionX - 400), ((basePositionY - 35) - (i * 256)), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    }

    for (int i = 0; ((basePositionY + (256 + 256 + 40)) + (i * 256)) < (*D2CLIENT_WindowHeight); i++) {
        d2mrFancyVerticalBar.setFrame(i % 2);
        d2mrFancyVerticalBar.draw((basePositionX - 400), ((basePositionY + (256 + 256 + 40)) + ((i + 1) * 256)), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    }
}

void D2HD::Draw::drawLeftPanelBorders() {
    D2HD::D2HDCellContext& borderLeft = config.isEnableD2MRPanelBorderStyle() ? d2mrFancyBorderInterfaceLeft : neoD2MRFancyBorderInterfaceLeft;
    D2HD::D2HDCellContext& borderBottomLeft = config.isEnableD2MRPanelBorderStyle() ? d2mrFancyBorderBottom : neoD2MRFancyBorderBottomLeft;
    D2HD::D2HDCellContext& borderTopLeft = config.isEnableD2MRPanelBorderStyle() ? d2mrFancyBorderTop : neoD2MRFancyBorderTopLeft;
    D2HD::D2HDCellContext& borderCornerBottomLeft = config.isEnableD2MRPanelBorderStyle() ? d2mrFancyBorderCorner : neoD2MRFancyBorderCornerBottomLeft;
    D2HD::D2HDCellContext& borderCornerTopLeft = config.isEnableD2MRPanelBorderStyle() ? d2mrFancyBorderCorner : neoD2MRFancyBorderCornerTopLeft;

    borderLeft.loadFileSafely();
    borderBottomLeft.loadFileSafely();
    borderTopLeft.loadFileSafely();
    borderCornerBottomLeft.loadFileSafely();
    borderCornerTopLeft.loadFileSafely();

    int basePositionX = (*D2CLIENT_WindowWidth / 2) - 400;
    int basePositionY = (*D2CLIENT_WindowHeight / 2) - 300;

    if (!config.isEnableD2MRPanelBorderStyle()) {
        basePositionX += 2;
    }

    // Draw top border pieces
    borderTopLeft.setFrame(0);
    borderTopLeft.draw((basePositionX + 56), (basePositionY + 60), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    borderTopLeft.setFrame(1);
    borderTopLeft.draw((basePositionX + 56) + 256, (basePositionY + 60), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);

    // Draw bottom border pieces
    borderBottomLeft.setFrame(0);
    borderBottomLeft.draw((basePositionX + 56), (basePositionY + 256) + (256 + 40), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    borderBottomLeft.setFrame(1);
    borderBottomLeft.draw((basePositionX + 56) + 256, (basePositionY + 256) + (256 + 40), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);

    // Draw top left corner border pieces
    borderCornerTopLeft.setFrame(0);
    borderCornerTopLeft.draw((basePositionX + 56) + 284, (basePositionY + 60), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);

    // Draw bottom left corner border pieces
    borderCornerBottomLeft.setFrame(0);
    borderCornerBottomLeft.draw((basePositionX + 56) + 284, (basePositionY) + (256 + 256 + 40), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);

    // Draw left border pieces
    borderLeft.setFrame(0);
    borderLeft.draw(basePositionX, (basePositionY + 256), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    borderLeft.setFrame(1);
    borderLeft.draw(basePositionX, (basePositionY + 256) + 256, config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
    borderLeft.setFrame(2);
    borderLeft.draw(basePositionX, (basePositionY + 256) + (256 + 40), config.getLeftPanelBorderColor().getBGRFormat(), 5, nullptr);
}

void D2HD::Draw::drawRightPanelBackground() {
    d2mrStoneBack.loadFileSafely();
    d2mrStoneBack.setFrame(0);

    int basePositionX = (*D2CLIENT_WindowWidth / 2);

    // Draw background pieces
    const int backWidth = 256;
    const int backHeight = 256;

    for (int row = 0; (row * backHeight) < *D2CLIENT_WindowHeight; row++) {
        int backBasePositionY = ((row + 1) * backHeight);

        for (int col = 0; basePositionX + (col * backWidth) < *D2CLIENT_WindowWidth; col++) {
            d2mrStoneBack.setFrame(((row % 2) * 2) + ((col + 1) % 2));
            int backBasePositionX = basePositionX + (col * backWidth);

            d2mrStoneBack.draw(backBasePositionX, backBasePositionY, config.getRightPanelBackgroundColor().getBGRFormat(), 5, 0);
        }
    }

    // Draw the ribbons only if the user has it enabled AND the game resolution allows the ribbons to be drawn without
    // problems.
    if (!config.isEnableD2MRBackgroundRibbon()
            && ((*D2CLIENT_WindowHeight - ((256 + 256 + 40) + 48)) <= (2 * (256 + 28)))) {
        return;
    }

    d2mrFancyBorderRight.loadFileSafely();
    d2mrFancyHorizontalBar.loadFileSafely();
    d2mrFancyVerticalBar.loadFileSafely();

    int basePositionY = (*D2CLIENT_WindowHeight / 2) - 300;

    d2mrFancyBorderRight.setFrame(0);
    d2mrFancyBorderRight.draw((basePositionX), (basePositionY + 256) + (256 + 256 + 40), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    d2mrFancyBorderRight.setFrame(1);
    d2mrFancyBorderRight.draw((basePositionX), (basePositionY + 256 + 28) + (256 + 256 + 40), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);

    d2mrFancyBorderRight.draw((basePositionX), (basePositionY), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    d2mrFancyBorderRight.setFrame(0);
    d2mrFancyBorderRight.draw((basePositionX), (basePositionY - 28), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);

    for (int i = 0; (basePositionX + 400) + (i * 256) < (*D2CLIENT_WindowWidth); i++) {
        d2mrFancyHorizontalBar.setFrame(i % 2);
        d2mrFancyHorizontalBar.draw((basePositionX + 400) + (i * 256), (basePositionY + (256 + 256 + 40)), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
        d2mrFancyHorizontalBar.draw((basePositionX + 400) + (i * 256), (basePositionY + 60), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    }

    d2mrFancyVerticalBar.setFrame(2);
    d2mrFancyVerticalBar.draw((basePositionX + 400 - 60), (basePositionY), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);

    for (int i = 0; ((basePositionY - 35) - (i * 256)) >= 0; i++) {
        d2mrFancyVerticalBar.setFrame(std::abs(i - 1) % 2);
        d2mrFancyVerticalBar.draw((basePositionX + 400 - 60), ((basePositionY - 35) - (i * 256)), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    }

    for (int i = 0;
            ((basePositionY + (256 + 256 + 40)) + (i * 256)) < (*D2CLIENT_WindowHeight);
            i++) {
        d2mrFancyVerticalBar.setFrame(i % 2);
        d2mrFancyVerticalBar.draw((basePositionX + 400 - 60), ((basePositionY + (256 + 256 + 40)) + ((i + 1) * 256)), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    }
}

void D2HD::Draw::drawRightPanelBorders() {
    D2HD::D2HDCellContext& borderRight = config.isEnableD2MRPanelBorderStyle() ? d2mrFancyBorderInterfaceRight : neoD2MRFancyBorderInterfaceRight;
    D2HD::D2HDCellContext& borderBottomRight = config.isEnableD2MRPanelBorderStyle() ? d2mrFancyBorderBottom : neoD2MRFancyBorderBottomRight;
    D2HD::D2HDCellContext& borderTopRight = config.isEnableD2MRPanelBorderStyle() ? d2mrFancyBorderTop : neoD2MRFancyBorderTopRight;
    D2HD::D2HDCellContext& borderCornerBottomRight = config.isEnableD2MRPanelBorderStyle() ? d2mrFancyBorderCorner : neoD2MRFancyBorderCornerBottomRight;
    D2HD::D2HDCellContext& borderCornerTopRight = config.isEnableD2MRPanelBorderStyle() ? d2mrFancyBorderCorner : neoD2MRFancyBorderCornerTopRight;

    borderRight.loadFileSafely();
    borderBottomRight.loadFileSafely();
    borderTopRight.loadFileSafely();
    borderCornerBottomRight.loadFileSafely();
    borderCornerTopRight.loadFileSafely();

    int basePositionX = (*D2CLIENT_WindowWidth / 2);
    int basePositionY = (*D2CLIENT_WindowHeight / 2) - 300;

    // Draw top border pieces
    borderTopRight.setFrame(0);
    borderTopRight.draw((basePositionX + 60), (basePositionY + 60), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    borderTopRight.setFrame(1);
    borderTopRight.draw((basePositionX + 60) + 256, (basePositionY + 60), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);

    // Draw bottom border pieces
    borderBottomRight.setFrame(0);
    borderBottomRight.draw((basePositionX + 60), (basePositionY + 256) + (256 + 40), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    borderBottomRight.setFrame(1);
    borderBottomRight.draw((basePositionX + 60) + 256, (basePositionY + 256) + (256 + 40), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);

    // Draw top right corner border pieces
    borderCornerTopRight.setFrame(0);
    borderCornerTopRight.draw((basePositionX), (basePositionY + 60), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);

    // Draw bottom right corner border pieces
    borderCornerBottomRight.setFrame(0);
    borderCornerBottomRight.draw((basePositionX), (basePositionY + 256) + (256 + 40), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);

    // Draw left border pieces
    borderRight.setFrame(0);
    borderRight.draw((basePositionX + 320), (basePositionY + 256), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    borderRight.setFrame(1);
    borderRight.draw((basePositionX + 320), (basePositionY + 256) + 256, config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
    borderRight.setFrame(2);
    borderRight.draw((basePositionX + 320), (basePositionY + 256) + (256 + 40), config.getRightPanelBackgroundColor().getBGRFormat(), 5, nullptr);
}

void __stdcall D2HD::Draw::unloadCellFiles(CellFile** original) {
    blankCellFile.unloadFileSafely();

    d2mrFancyBorderCorner.unloadFileSafely();
    neoD2MRFancyBorderCornerBottomLeft.unloadFileSafely();
    neoD2MRFancyBorderCornerBottomRight.unloadFileSafely();
    neoD2MRFancyBorderCornerTopLeft.unloadFileSafely();
    neoD2MRFancyBorderCornerTopRight.unloadFileSafely();

    d2mrFancyBorderInterfaceLeft.unloadFileSafely();
    d2mrFancyBorderInterfaceRight.unloadFileSafely();
    neoD2MRFancyBorderInterfaceLeft.unloadFileSafely();
    neoD2MRFancyBorderInterfaceRight.unloadFileSafely();

    d2mrFancyBorderLeft.unloadFileSafely();
    d2mrFancyBorderRight.unloadFileSafely();

    d2mrFancyBorderBottom.unloadFileSafely();
    d2mrFancyBorderTop.unloadFileSafely();
    neoD2MRFancyBorderBottomLeft.unloadFileSafely();
    neoD2MRFancyBorderBottomRight.unloadFileSafely();
    neoD2MRFancyBorderTopLeft.unloadFileSafely();
    neoD2MRFancyBorderTopRight.unloadFileSafely();

    d2mrFancyHorizontalBar.unloadFileSafely();
    d2mrFancyVerticalBar.unloadFileSafely();
    d2mrFancyPanelFlipHorizontalBar.unloadFileSafely();
    d2mrFancyPanelFlipVerticalBar.unloadFileSafely();

    d2mrFancyPanelHorizontalBar.unloadFileSafely();
    d2mrFancyPanelVerticalBar.unloadFileSafely();

    d2mrFancyPanelLeft.unloadFileSafely();
    d2mrFancyPanelRight.unloadFileSafely();
    d2mrFancyPanelFlipLeft.unloadFileSafely();
    d2mrFancyPanelFlipRight.unloadFileSafely();

    d2mrStoneBack.unloadFileSafely();
    resolution1068x600Text.unloadFileSafely();
    resolution1344x700Text.unloadFileSafely();

    *original = *D2CLIENT_PanelBorderImage;
}
