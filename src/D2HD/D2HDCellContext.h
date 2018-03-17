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
 *   Declares a class that provides higher level abstraction for             *
 *   CellContext, for the purpose of allowing it to work on different        *
 *   versions of the game.                                                   *
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

#include <memory>
#include <string>

#include "../DLLmain.h"

#pragma once

#ifndef D2HDCELLCONTEXT_H
#define D2HDCELLCONTEXT_H

namespace D2HD {
class D2HDCellContext {
public:
    D2HDCellContext(const std::string& fileName);
    ~D2HDCellContext();

    void draw(int x, int y, unsigned int color, int transTable, unsigned char* pPalette) const;
    void loadFileSafely();
    void unloadFileSafely();
    bool isFileLoaded() const;

    int getFrame() const;
    void setFrame(int frame);
    CellFile* getCellFilePtr() const;


private:
    std::unique_ptr<struct CellContext> pCellContext;
    std::string fileName;

    void setCellFilePtr(CellFile* pCellFile);

    D2HDCellContext() = delete;
};
}

#endif // D2HDCELLCONTEXT_H
