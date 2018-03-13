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
 *   The file defines a set of functions that comes from D2Ex2 and are     *
 *   used for correcting the position of items in the inventory.           *
 *                                                                         *
 ***************************************************************************/

/*==========================================================
* D2Ex2
* https://github.com/lolet/D2Ex2
* ==========================================================
* Copyright (c) 2011-2014 Bartosz Jankowski
* SlashDiablo-Tools Modifications: Copyright (C) 2017 Mir Drualga
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

#pragma once

#ifndef D2HDINVENTORY_H
#define D2HDINVENTORY_H

#include "../DLLmain.h"

namespace D2HD {
namespace Inventory {
    void __stdcall getBeltPos(int nIndex, int nMode, BeltBox *out, int nBox);
    void __stdcall getBeltsTxtRecord(int nIndex, int nMode, BeltsTxt *out);
    void __stdcall getInventorySize(int nRecord, int nScreenMode, InventorySize *pOutRect);
    void __stdcall getInventoryGrid(int nRecord, int nScreenMode, InventoryGrid *pOut);
    void __stdcall getInventoryField(int nRecord, int nScreenMode, InventoryLayout *pOut, int nField);
}
}

#endif
