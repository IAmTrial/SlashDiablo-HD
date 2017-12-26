/****************************************************************************
 *                                                                           *
 *   DLLmain.h                                                               *
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
 *   D2Template core file, do not modify unless you know what you're doing   *
 *                                                                           *
 *****************************************************************************/
#pragma once

#ifndef _DLLMAIN_H
#define _DLLMAIN_H

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_DEPRECATE
#define _WIN32_WINNT 0x600

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

static const DWORD DLLBASE_BNCLIENT = (DWORD) LoadLibraryW(L"Bnclient.dll");
static const DWORD DLLBASE_D2CLIENT = (DWORD) LoadLibraryW(L"D2Client.dll");
static const DWORD DLLBASE_D2CMP = (DWORD) LoadLibraryW(L"D2CMP.dll");
static const DWORD DLLBASE_D2COMMON = (DWORD) LoadLibraryW(L"D2Common.dll");
static const DWORD DLLBASE_D2DDRAW = (DWORD) LoadLibraryW(L"D2DDraw.dll");
static const DWORD DLLBASE_D2DIRECT3D = (DWORD) LoadLibraryW(L"D2Direct3D.dll");
static const DWORD DLLBASE_D2GAME = (DWORD) LoadLibraryW(L"D2Game.dll");
static const DWORD DLLBASE_D2GDI = (DWORD) LoadLibraryW(L"D2Gdi.dll");
static const DWORD DLLBASE_D2GFX = (DWORD) LoadLibraryW(L"D2Gfx.dll");
static const DWORD DLLBASE_D2GLIDE = (DWORD) LoadLibraryW(L"D2Glide.dll");
static const DWORD DLLBASE_D2LANG = (DWORD) LoadLibraryW(L"D2Lang.dll");
static const DWORD DLLBASE_D2LAUNCH = (DWORD) LoadLibraryW(L"D2Launch.dll");
static const DWORD DLLBASE_D2MCPCLIENT = (DWORD) LoadLibraryW(
        L"D2MCPClient.dll");
static const DWORD DLLBASE_D2MULTI = (DWORD) LoadLibraryW(L"D2Multi.dll");
static const DWORD DLLBASE_D2NET = (DWORD) LoadLibraryW(L"D2Net.dll");
static const DWORD DLLBASE_D2SOUND = (DWORD) LoadLibraryW(L"D2Sound.dll");
static const DWORD DLLBASE_D2WIN = (DWORD) LoadLibraryW(L"D2Win.dll");
static const DWORD DLLBASE_FOG = (DWORD) LoadLibraryW(L"Fog.dll");
static const DWORD DLLBASE_STORM = (DWORD) LoadLibraryW(L"Storm.dll");
static const DWORD DLLBASE_IJL11 = (DWORD) LoadLibraryW(L"ijl11.dll");
static const DWORD DLLBASE_BINKW32 = (DWORD) LoadLibraryW(L"binkw32.dll");
static const DWORD DLLBASE_SMACKW32 = (DWORD) LoadLibraryW(L"SmackW32.dll");

#include "D2Version.h"
#include "D2Constants.h"
#include "D2Structs.h"
#include "D2Ptrs.h"
#include "D2Vars.h"

#include "TemplateIncludes.h"

struct DLLBaseStrc {
    LPCWSTR wszName;
    HMODULE dwAddress;
};

extern DLLBaseStrc gptDllFiles[];

void __fastcall D2TEMPLATE_FatalError(LPCWSTR wszMessage);

#endif
