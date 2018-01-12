/*****************************************************************************
 *                                                                           *
 *   D2DataTables.h                                                          *
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
 *   This file is an expansion of D2Structs.h, meant to be used to declare   *
 *   structs representing the record of a data table once loaded in memory   *
 *   by the game, such as Monstats.txt or Charstats.txt                      *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2DATATABLES_H
#define _D2DATATABLES_H

#pragma pack(1)

/****************************************************************************
 *                                                                           *
 * DECLARATIONS                                                              *
 *                                                                           *
 *****************************************************************************/

struct InventoryLayout;
struct InventoryTxt;
struct BeltBox;
struct BeltsTxt;

/****************************************************************************
 *                                                                           *
 * DEFINITIONS                                                               *
 *                                                                           *
 *****************************************************************************/

/*
Time-saving credit goes to Mnw1995
http://d2mods.info/forum/viewtopic.php?f=8&t=61189
Isn't simpler now?
*/

struct InventoryLayout //sizeof 0x14
{
    DWORD dwLeft;		//0x00
    DWORD dwRight;		//0x04
    DWORD dwTop;		//0x08
    DWORD dwBottom;		//0x0C
    union
    {
        struct
        {
            BYTE nGridX;		//0x10
            BYTE nGridY;		//0x11
        };
        struct
        {
            BYTE nWidth;	//0x10
            BYTE nHeight;	//0x11
        };
    };
    WORD _align;		//0x12
};

struct InventoryTxt //sizeof 0xF0
{
    InventoryLayout Inventory;		//0x00
    InventoryLayout Grid;			//0x14
    union
    {
        struct
        {
            InventoryLayout RightArm;		//0x28
            InventoryLayout Torso;			//0x3C
            InventoryLayout LeftArm;		//0x50
            InventoryLayout Head;			//0x64
            InventoryLayout Neck;			//0x78
            InventoryLayout RightHand;		//0x8C
            InventoryLayout LeftHand;		//0xA0
            InventoryLayout Belt;			//0xB4
            InventoryLayout Feet;			//0xC8
            InventoryLayout Gloves;			//0xDC
        };
        InventoryLayout hItem[9];
    };
};

struct BeltBox
{
    DWORD dwBoxLeft;			//0x00
    DWORD dwBoxRight;			//0x04
    DWORD dwBoxTop;				//0x08
    DWORD dwBoxBottom;			//0x0C
};

struct BeltsTxt //sizeof 0x108
{
    DWORD _unusedName;			    //0x00 placeholder for name field
    DWORD dwNumBoxes;               //0x04
    BeltBox hBox[16];				//0x08
};

// end of file --------------------------------------------------------------
#pragma pack()
#endif
