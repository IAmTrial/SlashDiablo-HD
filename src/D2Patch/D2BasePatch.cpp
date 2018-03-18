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
 *   This file defines functions used by the base patch, to define some of   *
 *   the functions used by more specific Diablo II patches.                  *
 *                                                                           *
 *****************************************************************************/

#include "D2BasePatch.h"

#include <memory>
#include <vector>

#include "../D2Offset.h"

D2BasePatch::D2BasePatch(const D2Offset& d2Offset,
                         const size_t patchSize) : d2Offset(d2Offset), patchSize(patchSize) {
}

const D2Offset& D2BasePatch::getD2Offset() const {
    return d2Offset;
}

size_t D2BasePatch::getPatchSize() const {
    return patchSize;
}
