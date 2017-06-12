#pragma once

#ifndef _D2STRUCTS_H
#define _D2STRUCTS_H

#include "D2DataTables.h"
#include "D2PacketDef.h"
#pragma pack(1)

/****************************************************************************
*                                                                           *
*   D2Structs.h                                                             *
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

// end of file --------------------------------------------------------------
#pragma pack()
#endif