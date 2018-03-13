/***************************************************************************
 *                                                                         *
 *   SlashDiablo HD                                                        *
 *   Copyright (C) 2017  Mir Drualga                                       *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 *-------------------------------------------------------------------------*
 *                                                                         *
 *   Defines a class that provides higher level abstraction for            *
 *   CellContext, for the purpose of allowing it to work on different      *
 *   versions of the game.                                                 *
 *                                                                         *
 ***************************************************************************/

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

#include "D2HDCellContext.h"

#include <memory>
#include <string>

D2HD::D2HDCellContext::D2HDCellContext(const std::string& fileName) : fileName(fileName) {
    switch (D2Version::getGameVersion()) {
    case GameVersion::VERSION_112:
        pCellContext = std::unique_ptr<struct CellContext>(new CellContext_112);
        memset(pCellContext.get(), 0, sizeof(CellContext_112));
        break;

    case GameVersion::VERSION_113c:
    case GameVersion::VERSION_113d:
        pCellContext = std::unique_ptr<struct CellContext>(new CellContext_113);
        memset(pCellContext.get(), 0, sizeof(CellContext_113));
        break;

    default:
        MessageBoxW(nullptr, L"D2HDContext not set up to handle this version.", L"Version not supported yet.", MB_OK);
        break;
    }
}

D2HD::D2HDCellContext::~D2HDCellContext() {
    unloadFileSafely();
}

void D2HD::D2HDCellContext::draw(int x, int y, unsigned int color, int transTable, unsigned char* pPalette) const {
    D2GFX_DrawCellContext(pCellContext.get(), x, y, color, transTable, pPalette);
}

void D2HD::D2HDCellContext::loadFileSafely() {
    if (isFileLoaded()) {
        return;
    }

    setCellFilePtr(D2WIN_LoadCellFile(fileName.c_str(), 0));
    if (getCellFilePtr() == nullptr || (unsigned int)getCellFilePtr() == 1) {
        MessageBoxW(nullptr, L"CellFile asset failed to load.", L"Diablo II Error", MB_OK | MB_ICONERROR);
        std::exit(0);
    }
}

void D2HD::D2HDCellContext::unloadFileSafely() {
    if (isFileLoaded()) {
        D2CMP_FreeCellFile(getCellFilePtr());
        FOG_FreeClientMemory(getCellFilePtr(), __FILE__, __LINE__, nullptr);

        setCellFilePtr(nullptr);
    }
}

bool D2HD::D2HDCellContext::isFileLoaded() const {
    return getCellFilePtr() != nullptr;
}

int D2HD::D2HDCellContext::getFrame() const {
    int frame = 0;

    switch (D2Version::getGameVersion()) {
    case GameVersion::VERSION_112:
        frame = ((CellContext_112*) pCellContext.get())->nFrame;
        break;

    case GameVersion::VERSION_113c:
    case GameVersion::VERSION_113d:
        frame = ((CellContext_113*) pCellContext.get())->nFrame;
        break;

    default:
        MessageBoxW(nullptr, L"D2HDContext not set up to handle this version.", L"Version not supported yet.", MB_OK);
        break;
    }

    return frame;
}

void D2HD::D2HDCellContext::setFrame(int frame) {
    switch (D2Version::getGameVersion()) {
    case GameVersion::VERSION_112:
        ((CellContext_112*) pCellContext.get())->nFrame = frame;
        break;

    case GameVersion::VERSION_113c:
    case GameVersion::VERSION_113d:
        ((CellContext_113*) pCellContext.get())->nFrame = frame;
        break;

    default:
        MessageBoxW(nullptr, L"D2HDContext not set up to handle this version.", L"Version not supported yet.", MB_OK);
        break;
    }
}

CellFile* D2HD::D2HDCellContext::getCellFilePtr() const {
    CellFile* pCellFile = nullptr;

    switch (D2Version::getGameVersion()) {
    case GameVersion::VERSION_112:
        pCellFile = ((CellContext_112*) pCellContext.get())->pCellFile;
        break;

    case GameVersion::VERSION_113c:
    case GameVersion::VERSION_113d:
        pCellFile = ((CellContext_113*) pCellContext.get())->pCellFile;
        break;

    default:
        MessageBoxW(nullptr, L"D2HDContext not set up to handle this version.", L"Version not supported yet.", MB_OK);
        break;
    }

    return pCellFile;
}

void D2HD::D2HDCellContext::setCellFilePtr(CellFile* pCellFile) {
    switch (D2Version::getGameVersion()) {
    case GameVersion::VERSION_112:
        ((CellContext_112*) pCellContext.get())->pCellFile = pCellFile;
        break;

    case GameVersion::VERSION_113c:
    case GameVersion::VERSION_113d:
        ((CellContext_113*) pCellContext.get())->pCellFile = pCellFile;
        break;

    default:
        MessageBoxW(nullptr, L"D2HDContext not set up to handle this version.", L"Version not supported yet.", MB_OK);
        break;
    }
}
