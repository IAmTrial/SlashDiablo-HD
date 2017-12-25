/*****************************************************************************
 *                                                                           *
 *   D2Offset.cpp                                                            *
 *   Copyright (C) 2017 Mir Drualga                                          *
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
 *   This file defines the functions that correctly manages returning the    *
 *   correct offset for the requested Diablo II variable, function, or       *
 *   pointer.                                                                *
 *                                                                           *
 *****************************************************************************/

#include "D2Offset.h"
#include "DLLmain.h"

D2Offset::D2Offset() {
    // Intended to be empty.
}

D2Offset::D2Offset(Offsets offsets) {
    D2Offset::offsets = offsets;
}

int D2Offset::getCurrentOffset() {
    return *(&offsets._107 + (int) D2Version::getGameVersionID());
}
