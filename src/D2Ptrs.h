/*****************************************************************************
 *                                                                           *
 *   D2Ptrs.h                                                                *
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
 *   This file is used to declare pointers, be it function or variable       *
 *   pointers, from the game's libraries.                                    *
 *                                                                           *
 *   It is recommended that you keep this file organized by which dll the    *
 *   pointer is imported from, what type of pointer it is, etc. Ordering     *
 *   them by address can also end up being very useful                       *
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

#ifndef _D2PTRS_H
#define _D2PTRS_H

#include "D2Offset.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  These are the macros used by the template core to declare                                                                                                                                   ///
//  pointers. Do not touch unless you know what you're doing                                                                                                                                    ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ESCAPE_PARENTHESES(...) __VA_ARGS__

#define D2FUNC(DLL, NAME, RETURN, CONV, ARGS, OFFSETS) \
    typedef RETURN (CONV * DLL##_##NAME##_t) ARGS; \
    static D2Offset DLL##_##NAME##_FUNC_OFFSET (D2TEMPLATE_DLL_FILES::D2DLL_##DLL, { ESCAPE_PARENTHESES OFFSETS }); \
    static DLL##_##NAME##_t DLL##_##NAME = (DLL##_##NAME##_t)(DLL##_##NAME##_FUNC_OFFSET.getCurrentAddress());

#define D2VAR(DLL, NAME, TYPE, OFFSETS) \
    typedef TYPE DLL##_##NAME##_vt; \
    static D2Offset DLL##_##NAME##_VAR_OFFSET (D2TEMPLATE_DLL_FILES::D2DLL_##DLL, { ESCAPE_PARENTHESES OFFSETS }); \
    static DLL##_##NAME##_vt * DLL##_##NAME = (DLL##_##NAME##_vt *)(DLL##_##NAME##_VAR_OFFSET.getCurrentAddress());

#define D2PTR(DLL, NAME, OFFSETS) \
    static D2Offset DLL##_##NAME##_PTR_OFFSET (D2TEMPLATE_DLL_FILES::D2DLL_##DLL, { ESCAPE_PARENTHESES OFFSETS }); \
    static DWORD DLL##_##NAME = (DLL##_##NAME##_PTR_OFFSET.getCurrentAddress());

/*********************************************************************************
 *                                                                               *
 *   D2GAME.DLL POINTERS                                                         *
 *                                                                               *
 *********************************************************************************/

/*********************************************************************************
 *                                                                               *
 *   D2CLIENT.DLL POINTERS                                                       *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2CLIENT, WindowWidth, int, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xDBC48, 0xF7034, 0, 0, 0, 0));
D2VAR(D2CLIENT, WindowHeight, int, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xDBC4C, 0xF7038, 0, 0, 0, 0));
D2VAR(D2CLIENT, PanelBorderImage, CellFile*, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x11A77C, 0x103B14, 0, 0, 0, 0));
D2VAR(D2CLIENT, PanelOffsetX, int, (0x12D7FC, 0x122B3C, 0, 0, 0, 0x124954, 0x11A748, 0x11BD24, 0x11BEF8, 0x11BD28, 0x11B9A0, 0x11D354, 0x442F58, 0x39A8E0, 0x3998E0, 0x3A2858));
D2VAR(D2CLIENT, PanelOffsetY, int, (0x12D800, 0x122B40, 0, 0, 0, 0x124958, 0x11A74C, 0x11BD28, 0x11BEFC, 0x11BD2C, 0x11B9A4, 0x11D358, 0x442F5C, 0x39A8E4, 0x3998E4, 0x3A285C));
D2VAR(D2CLIENT, PanelOpenMode, int, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x11C414, 0x11D070, 0, 0, 0, 0));
D2VAR(D2CLIENT, InventoryArrangeMode, int, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x11B99C, 0x11D2B4, 0, 0, 0, 0));

D2VAR(D2CLIENT, VideoOptionCellFileStart, void*, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xEA568, 0xE48D0, 0, 0, 0, 0));

/*********************************************************************************
 *                                                                               *
 *   D2CMP.DLL POINTERS                                                          *
 *                                                                               *
 *********************************************************************************/
D2FUNC(D2CMP, FreeCellFile, bool, __stdcall, (CellFile* pCellFile), (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -10065, -10020, 0, 0, 0, 0)); // Called at D2Client.dll+26E1C,8022E

/*********************************************************************************
 *                                                                               *
 *   D2COMMON.DLL POINTERS                                                       *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2COMMON, InventoryTxt, InventoryTxt*, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x9FA5C, 0xA4CAC, 0, 0, 0, 0));

/*********************************************************************************
 *                                                                               *
 *   D2DDRAW.DLL POINTERS                                                        *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2DDRAW, WindowHeight, int, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x101D8, 0x100E8, 0, 0, 0, 0));

/*********************************************************************************
 *                                                                               *
 *   D2DIRECT3D.DLL POINTERS                                                     *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2DIRECT3D, WindowWidth, int, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1AB44, 0x3296C, 0, 0, 0, 0));
D2VAR(D2DIRECT3D, WindowHeight, int, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1AFD4, 0X32DFC, 0, 0, 0, 0));

/*********************************************************************************
 *                                                                               *
 *   D2GDI.DLL POINTERS                                                          *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2GDI, ForegroundRenderWidth, int, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xCA9C, 0xCA98, 0, 0, 0, 0));

/*********************************************************************************
 *                                                                               *
 *   D2GFX.DLL POINTERS                                                          *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2GFX, WindowWidth, int, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1477C, 0x14324, 0, 0, 0, 0));
D2VAR(D2GFX, WindowHeight, int, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x14780, 0x14328, 0, 0, 0, 0));

D2FUNC(D2GFX, GetRenderMode, D2RenderModes, __stdcall, (), (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -10078, -10022, 0, 0, 0, 0));
D2FUNC(D2GFX, GetResolutionMode, int, __stdcall, (), (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -10031, -10012, 0, 0, 0, 0));
D2FUNC(D2GFX, DrawCellContext, void, __stdcall, (CellContext* pCellContext, int nXpos, int nYpos, unsigned int color, int nTransTbl, unsigned char* pPalette), (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -10041, -10042, 0, 0, 0, 0));

/*********************************************************************************
 *                                                                               *
 *   D2GLIDE.DLL POINTERS                                                        *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2GLIDE, WindowWidth, int, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x15A68, 0x15A78, 0, 0, 0, 0));
D2VAR(D2GLIDE, WindowHeight, int, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x15B04, 0x15B14, 0, 0, 0, 0));

D2VAR(D2GLIDE, SpritesInited, bool, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x17B44, 0x17B54, 0, 0, 0, 0));

/*********************************************************************************
 *                                                                               *
 *   D2WIN.DLL POINTERS                                                          *
 *                                                                               *
 *********************************************************************************/
D2FUNC(D2WIN, LoadCellFile, CellFile*, __fastcall, (const char* szFile, int Type), (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -10111, -10023, 0, 0, 0, 0));
D2PTR(D2WIN, LoadMpq_I, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7E60, 0x7E50, 0, 0, 0, 0));

/*********************************************************************************
 *                                                                               *
 *   FOG.DLL POINTERS                                                            *
 *                                                                               *
 *********************************************************************************/
D2FUNC(FOG, FreeClientMemory, void, __fastcall, (void* pMemoryToFree, const char* szFile, int nLine, void* pNull), (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -10043, -10043, 0, 0, 0, 0));

/*********************************************************************************
 *                                                                               *
 *   GLIDE3X.DLL POINTERS                                                        *
 *                                                                               *
 *********************************************************************************/
D2VAR(GLIDE3X, WindowWidth, int*, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1C9A0, 0x1C9A0, 0, 0, 0, 0));
D2VAR(GLIDE3X, WindowHeight, int*, (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1C82C, 0x1C82C, 0, 0, 0, 0));

// end of file -----------------------------------------------------------------
#endif
