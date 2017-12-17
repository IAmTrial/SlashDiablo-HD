/****************************************************************************
*                                                                           *
*   D2Structs.h                                                             *
*   Copyright (C) Olivier Verville                                          *
*                                                                           *
*   D2Ex: Copyright (c) 2011-2014 Bartosz Jankowski                         *
*   /r/SlashDiablo HD Modifications: Copyright (C) 2017 Mir Drualga         *
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

struct CellContext      //sizeof 0x48
{
    int nFrame; // 0x00
    int dw1[12];    // 0x04
    const CellFile* pCellFile;  // 0x34
    int dw2[2]; // 0x38
    int dw3;    // 0x40
    int dw4;    // 0x44
};

struct InventorySize // sizeof 0x10
{
    DWORD dwLeft;		//0x00
    DWORD dwRight;		//0x04
    DWORD dwTop;		//0x08
    DWORD dwBottom;		//0x0C
};

struct InventoryGrid // sizeof 0x18
{
    BYTE nGridX;		//0x00
    BYTE nGridY;		//0x01
    WORD _align;		//0x02
    DWORD dwLeft;		//0x04
    DWORD dwRight;		//0x08
    DWORD dwTop;		//0x0C
    DWORD dwBottom;		//0x10
    BYTE nGridWidth;	//0x14
    BYTE nGridHeight;	//0x15
    WORD _align2;		//0x16
};

// end of file --------------------------------------------------------------
#pragma pack()
#endif