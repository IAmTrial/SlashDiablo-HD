/****************************************************************************
*                                                                           *
*   D2Stubs.h                                                               *
*   Copyright (C) 2017 Mir Drualga                                          *
*                                                                           *
*   D2Ex: Copyright (c) 2011-2014 Bartosz Jankowski                         *
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
*   This file is used to declare stubs that will be used to call game       *
*   functions that do not conform to STDCALL or FASTCALL conventions.       *
*                                                                           *
*   For example, a function that would need a stub function to be called    *
*   would be one that puts the first parameter into register ESI.           *
*                                                                           *
*****************************************************************************/

#pragma once

#ifndef D2STUBS_H
#define D2STUBS_H

#include "DLLmain.h"
#include "D2Ptrs.h"

CellFile* __stdcall STUB_D2CLIENT_LoadCellFile(const char* szBuffer);
HANDLE __stdcall STUB_D2WIN_LoadMPQ(DWORD OrderFlag, const char* szDllFile, const char* szMpqFile, const char* szName, DWORD _1, BOOL(__stdcall *fnMPQMissing)());

#endif
