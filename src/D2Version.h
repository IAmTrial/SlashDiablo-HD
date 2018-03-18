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
 *---------------------------------------------------------------------------*
 *                                                                           *
 *   This file is used to declare the Diablo II versions that are to be      *
 *   detected from Game.exe and the methods used to detect it.               *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2VERSION_H
#define _D2VERSION_H

#include <windows.h>
#include <string>

enum class GameVersion : int {
    INVALID,
    VERSION_107,
    VERSION_108,
    VERSION_109, VERSION_109b, VERSION_109c, VERSION_109d,
    VERSION_110,
    VERSION_111, VERSION_111b,
    VERSION_112,
    VERSION_113c, VERSION_113d,
    VERSION_114a, VERSION_114b, VERSION_114c, VERSION_114d
};

enum class Glide3xVersion : int {
    INVALID,
    VERSION_14e,
    RESURGENCE
};

namespace D2Version {
GameVersion getGameVersion();
GameVersion getGameVersion(std::string_view versionString);
bool isGameVersion114Plus();
Glide3xVersion getGlide3xVersion();
Glide3xVersion getGlide3xVersion(std::string_view versionString);
std::string determineVersionString(std::wstring_view filePath);
}

#endif
