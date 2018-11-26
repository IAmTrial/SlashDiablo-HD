/*****************************************************************************
 *                                                                           *
 * SlashDiablo HD                                                            *
 * Copyright (C) 2017  Mir Drualga                                           *
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
 * This file incorporates work covered by the following copyright and        *
 * permission notice:                                                        *
 *                                                                           *
 *   ==========================================================              *
 *   D2Ex2                                                                   *
 *   https://github.com/lolet/D2Ex2                                          *
 *   ==========================================================              *
 *   Copyright (c) 2011-2014 Bartosz Jankowski                               *
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
 *   ==========================================================              *
 *                                                                           *
 * In addition, the file also incorporates work covered by the following     *
 * copyright and permission notice:                                          *
 *                                                                           *
 *   D2Constants.h                                                           *
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
 *   This file is meant to declare various constant data. As you add more    *
 *   custom code to your library, you will be using many constant values     *
 *   used by the game's internal code. Unit types are a good example.        *
 *   Declaring constants allows you to assign a name to these constants      *
 *   which are more convenient to use in your source code.                   *
 *                                                                           *
 *   Another advantage is smaller impact in cases where these values would   *
 *   need to change. Rather than revising every single piece of code using   *
 *   this value, you only need to change your constant's value               *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2CONSTANTS_H
#define _D2CONSTANTS_H

enum D2C_UnitTypes
{
    UNIT_PLAYER,        // 0 - Players
    UNIT_MONSTER,       // 1 - Monsters
    UNIT_OBJECT,        // 2 - Objects
    UNIT_MISSILE,       // 3 - Missiles
    UNIT_ITEM,          // 4 - Items
    UNIT_TILE           // 5 - Tiles
};

/*
Dump of Records from Inventory.Txt
*/
enum InventoryTxtRows
{
    INV_REC_AMAZON = 0,
    INV_REC_SORCERESS,
    INV_REC_NECROMANCER,
    INV_REC_PALADIN,
    INV_REC_BARB,
    INV_REC_MONSTER,
    INV_REC_TRADE_I,
    INV_REC_TRADE_II,
    INV_REC_BANK,
    INV_REC_CUBE,
    INV_REC_GUILD_VAULT,
    INV_REC_TROPY_CASE,
    INV_REC_BIG_BANK,
    INV_REC_HIRELING,
    INV_REC_DRUID,
    INV_REC_ASSASSIN,
    //--Expansion
    INV_REC_EXP_AMAZON = 16,
    INV_REC_EXP_SORCERESS,
    INV_REC_EXP_NECROMANCER,
    INV_REC_EXP_PALADIN,
    INV_REC_EXP_BARB,
    INV_REC_EXP_MONSTER,
    INV_REC_EXP_TRADE_I,
    INV_REC_EXP_TRADE_II,
    INV_REC_EXP_BANK,
    INV_REC_EXP_CUBE,
    INV_REC_EXP_GUILD_VAULT,
    INV_REC_EXP_TROPY_CASE,
    INV_REC_EXP_BIG_BANK,
    INV_REC_EXP_HIRELING,
    INV_REC_EXP_DRUID,
    INV_REC_EXP_ASSASSIN
};

enum class D2RenderModes {
	VIDEO_MODE_GDI = 1,
	VIDEO_MODE_SOFTWARE = 2,
	VIDEO_MODE_DDRAW = 3,
	VIDEO_MODE_GLIDE = 4,
	VIDEO_MODE_OPENGL = 5, // UNUSED
	VIDEO_MODE_D3D = 6,
	VIDEO_MODE_RAVE = 7, // UNUSED
};

// end of file ---------------------------------------------------------------
#endif
