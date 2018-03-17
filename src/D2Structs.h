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
 *****************************************************************************/

/*****************************************************************************
 *                                                                           *
 *   D2Structs.h                                                             *
 *   Copyright (C) Olivier Verville                                          *
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
 *   https://github.com/olivier-verville/D2Template                          *
 *                                                                           *
 *   This file is used to declare data structures used by the game to        *
 *   represent various entities, such as the data structure representing     *
 *   a unit entity, or a game entity                                         *
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

#pragma once

#ifndef _D2STRUCTS_H
#define _D2STRUCTS_H

#include "D2DataTables.h"
#include "D2PacketDef.h"
#pragma pack(1)

/****************************************************************************
 *                                                                           *
 * DECLARATIONS                                                              *
 *                                                                           *
 *****************************************************************************/

struct CellFile;

/****************************************************************************
 *                                                                           *
 * DEFINITIONS                                                               *
 *                                                                           *
 *****************************************************************************/

struct CellContext {
};

struct CellContext_112 : CellContext { //sizeof 0x48
    int dw1[15];                        // 0x00
    CellFile* pCellFile;                // 0x3C
    int nFrame;                         // 0x40
    int dw2;                            // 0x44
};

struct CellContext_113 : CellContext {      //sizeof 0x48;
    int nFrame; // 0x00
    int dw1[12];    // 0x04
    CellFile* pCellFile;  // 0x34
    int dw2[2]; // 0x38
    int dw3;    // 0x40
    int dw4;    // 0x44
};

struct InventorySize { // sizeof 0x10
    long int left;      //0x00
    long int right;     //0x04
    long int top;       //0x08
    long int bottom;        //0x0C
};

struct InventoryGrid { // sizeof 0x18
    BYTE nGridX;        //0x00
    BYTE nGridY;        //0x01
    WORD _align;        //0x02
    long int left;      //0x04
    long int right;     //0x08
    long int top;       //0x0C
    long int bottom;        //0x10
    BYTE nGridWidth;    //0x14
    BYTE nGridHeight;   //0x15
    WORD _align2;       //0x16
};

// end of file --------------------------------------------------------------
#pragma pack()
#endif
