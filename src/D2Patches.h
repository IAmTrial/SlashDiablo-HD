/*****************************************************************************
 *                                                                           *
 *   D2Patches.h                                                             *
 *   Copyright (C) Olivier Verville                                          *
 *   SlashDiablo-Tools Modifications: Copyright (C) 2017 Mir Drualga         *
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
 *   This file is where you declare all your patches, in order to inject     *
 *   your own code into the game. Each patch should be declared in the       *
 *   array, in order to be handled by D2Template's patcher                   *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2PATCHES_H
#define _D2PATCHES_H

#include <memory>
#include <vector>

#include "D2Patch/D2AnyPatch.h"
#include "D2Patch/D2Patch.h"
#include "DLLmain.h"

 static const std::vector<std::shared_ptr<D2Patch>> gptTemplatePatches = {
     std::make_shared<D2AnyPatch>(D2Offset(D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, {
         {GameVersion::VERSION_113c, 0},
     }), (BYTE)OpCode::NOP, false, 0),
 };

// end of file --------------------------------------------------------------
#endif
