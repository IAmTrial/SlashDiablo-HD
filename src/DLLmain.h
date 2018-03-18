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
 *   DLLmain.h                                                               *
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
 *   D2Template core file, do not modify unless you know what you're doing   *
 *                                                                           *
 *****************************************************************************/
#pragma once

#ifndef _DLLMAIN_H
#define _DLLMAIN_H

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_DEPRECATE

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x600
#endif

#include <windows.h>

#include "D2HD/D2HDResolution.h"
#include "D2HD/D2HDConfig.h"
#include "D2Version.h"
#include "D2Constants.h"
#include "D2Structs.h"
#include "D2Stubs.h"
#include "D2Ptrs.h"
#include "D2Vars.h"

#include "TemplateIncludes.h"

void __fastcall D2TEMPLATE_FatalError(LPCWSTR wszMessage);

#endif
