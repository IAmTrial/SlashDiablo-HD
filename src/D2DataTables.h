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
    long int left;		//0x00
    long int right;		//0x04
    long int top;		//0x08
    long int bottom;		//0x0C
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
    long int boxLeft;			//0x00
    long int boxRight;			//0x04
    long int boxTop;				//0x08
    long int boxBottom;			//0x0C
};

struct BeltsTxt //sizeof 0x108
{
    DWORD _unusedName;			    //0x00 placeholder for name field
    BYTE dwNumBoxes;               //0x04 uses DWORD space, but interpreted as unsigned byte
    BYTE unknown[3];
    BeltBox hBox[16];				//0x08
};

// end of file --------------------------------------------------------------
#pragma pack()
#endif
