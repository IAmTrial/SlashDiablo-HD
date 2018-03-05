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
#include "D2Version.h"

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
D2VAR(D2CLIENT, WindowWidth, int,
      ({ GameVersion::VERSION_112, 0xDC6E0 },
       { GameVersion::VERSION_113c, 0xDBC48 },
       { GameVersion::VERSION_113d, 0xF7034 },
       { GameVersion::VERSION_114d, 0x31146C }));
D2VAR(D2CLIENT, WindowHeight, int,
      ({ GameVersion::VERSION_112, 0xDC6E4 },
       { GameVersion::VERSION_113c, 0xDBC4C },
       { GameVersion::VERSION_113d, 0xF7038 },
       { GameVersion::VERSION_114d, 0x311470 }));
D2VAR(D2CLIENT, MousePositionX, int,
      ({ GameVersion::VERSION_112, 0x101638 },
       { GameVersion::VERSION_113c, 0x11B828 }));
D2VAR(D2CLIENT, MousePositionY, int,
      ({ GameVersion::VERSION_112, 0x101634 },
       { GameVersion::VERSION_113c, 0x11B824 }));

D2VAR(D2CLIENT, StatsButtonClicked, bool,
      ({ GameVersion::VERSION_112, 0x11C344 }));
D2VAR(D2CLIENT, SkillButtonClicked, bool,
      ({ GameVersion::VERSION_112, 0x11C348 }));

D2VAR(D2CLIENT, PanelBorderImage, CellFile*,
      ({ GameVersion::VERSION_112, 0x102C08 },
       { GameVersion::VERSION_113c, 0x11A77C },
       { GameVersion::VERSION_113d, 0x103B14 }));
D2VAR(D2CLIENT, PanelOffsetX, int,
      ({ GameVersion::VERSION_107, 0x12D7FC },
       { GameVersion::VERSION_108, 0x122B3C },
       { GameVersion::VERSION_109, 0 },
       { GameVersion::VERSION_109b, 0 },
       { GameVersion::VERSION_109c, 0 },
       { GameVersion::VERSION_109d, 0x124954 },
       { GameVersion::VERSION_110, 0x11A748 },
       { GameVersion::VERSION_111, 0x11BD24 },
       { GameVersion::VERSION_111b, 0x11BEF8 },
       { GameVersion::VERSION_112, 0x11BD28 },
       { GameVersion::VERSION_113c, 0x11B9A0 },
       { GameVersion::VERSION_113d, 0x11D354 },
       { GameVersion::VERSION_114a, 0x442F58 },
       { GameVersion::VERSION_114b, 0x39A8E0 },
       { GameVersion::VERSION_114c, 0x3998E0 },
       { GameVersion::VERSION_114d, 0x3A2858 }));
D2VAR(D2CLIENT, PanelOffsetY, int,
      ({ GameVersion::VERSION_107, 0x12D800 },
       { GameVersion::VERSION_108, 0x122B40 },
       { GameVersion::VERSION_109, 0 },
       { GameVersion::VERSION_109b, 0 },
       { GameVersion::VERSION_109c, 0 },
       { GameVersion::VERSION_109d, 0x124958 },
       { GameVersion::VERSION_110, 0x11A74C },
       { GameVersion::VERSION_111, 0x11BD28 },
       { GameVersion::VERSION_111b, 0x11BEFC },
       { GameVersion::VERSION_112, 0x11BD2C },
       { GameVersion::VERSION_113c, 0x11B9A4 },
       { GameVersion::VERSION_113d, 0x11D358 },
       { GameVersion::VERSION_114a, 0x442F5C },
       { GameVersion::VERSION_114b, 0x39A8E4 },
       { GameVersion::VERSION_114c, 0x3998E4 },
       { GameVersion::VERSION_114d, 0x3A285C }));
D2VAR(D2CLIENT, PanelOpenMode, int,
      ({ GameVersion::VERSION_112, 0x11C1D0 },
       { GameVersion::VERSION_113c, 0x11C414 },
       { GameVersion::VERSION_113d, 0x11D070 }));
D2VAR(D2CLIENT, InventoryArrangeMode, int,
      ({ GameVersion::VERSION_112, 0x11B980 },
       { GameVersion::VERSION_113c, 0x11B99C },
       { GameVersion::VERSION_113d, 0x11D2B4 },
       { GameVersion::VERSION_114d, 0x3A5218 }));
D2VAR(D2CLIENT, EscMenuOpened, bool,
      ({ GameVersion::VERSION_112, 0x102B7C },
       { GameVersion::VERSION_113c, 0xFADA4 },
       { GameVersion::VERSION_113d, 0x11C8B4 },
       { GameVersion::VERSION_114d, 0 }));

D2VAR(D2CLIENT, VideoOptionCellFileStart, void*,
      ({ GameVersion::VERSION_112, 0xEC550 },
       { GameVersion::VERSION_113c, 0xEA568 },
       { GameVersion::VERSION_113d, 0xE48D0 }));

D2FUNC(D2CLIENT, ClickStatsButton, void, __stdcall, (),
      ({ GameVersion::VERSION_112, 0x3C6A0 }));
D2FUNC(D2CLIENT, ClickSkillButton, void, __stdcall, (),
      ({ GameVersion::VERSION_112, 0x3C5D0 }));

/*********************************************************************************
 *                                                                               *
 *   D2CMP.DLL POINTERS                                                          *
 *                                                                               *
 *********************************************************************************/
// Called at D2Client.dll+26E1C,8022E
D2FUNC(D2CMP, FreeCellFile, bool, __stdcall, (CellFile* pCellFile),
      ({ GameVersion::VERSION_112, -10106 },
       { GameVersion::VERSION_113c, -10065 },
       { GameVersion::VERSION_113d, -10020 }));

/*********************************************************************************
 *                                                                               *
 *   D2COMMON.DLL POINTERS                                                       *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2COMMON, InventoryTxt, InventoryTxt*,
      ({ GameVersion::VERSION_112, 0xA13F8 },
       { GameVersion::VERSION_113c, 0x9FA5C },
       { GameVersion::VERSION_113d, 0xA4CAC }));

/*********************************************************************************
 *                                                                               *
 *   D2DDRAW.DLL POINTERS                                                        *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2DDRAW, WindowHeight, int,
      ({ GameVersion::VERSION_112, 0xFDD8 },
       { GameVersion::VERSION_113c, 0x101D8 },
       { GameVersion::VERSION_113d, 0x100E8 }));

/*********************************************************************************
 *                                                                               *
 *   D2DIRECT3D.DLL POINTERS                                                     *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2DIRECT3D, WindowWidth, int,
      ({ GameVersion::VERSION_112, 0x19264 },
       { GameVersion::VERSION_113c, 0x1AB44 },
       { GameVersion::VERSION_113d, 0x3296C }));
D2VAR(D2DIRECT3D, WindowHeight, int,
      ({ GameVersion::VERSION_112, 0x196F4 },
       { GameVersion::VERSION_113c, 0x1AFD4 },
       { GameVersion::VERSION_113d, 0x32DFC }));

/*********************************************************************************
 *                                                                               *
 *   D2GDI.DLL POINTERS                                                          *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2GDI, ForegroundRenderWidth, int,
      ({ GameVersion::VERSION_112, 0xC044 },
       { GameVersion::VERSION_113c, 0xCA9C },
       { GameVersion::VERSION_113d, 0xCA98 }));

/*********************************************************************************
 *                                                                               *
 *   D2GFX.DLL POINTERS                                                          *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2GFX, WindowWidth, int,
      ({ GameVersion::VERSION_112, 0x1D314 },
       { GameVersion::VERSION_113c, 0x1477C },
       { GameVersion::VERSION_113d, 0x14324 }));
D2VAR(D2GFX, WindowHeight, int,
      ({ GameVersion::VERSION_112, 0x1D674 },
       { GameVersion::VERSION_113c, 0x14780 },
       { GameVersion::VERSION_113d, 0x14328 }));

D2FUNC(D2GFX, GetRenderMode, D2RenderModes, __stdcall, (),
      ({ GameVersion::VERSION_112, -10019 },
       { GameVersion::VERSION_113c, -10078 },
       { GameVersion::VERSION_113d, -10022 }));
D2FUNC(D2GFX, GetResolutionMode, int, __stdcall, (),
      ({ GameVersion::VERSION_112, -10043 },
       { GameVersion::VERSION_113c, -10031 },
       { GameVersion::VERSION_113d, -10012 },
       { GameVersion::VERSION_114d, 0xF5160 }));
D2FUNC(D2GFX, DrawCellContext, void, __stdcall, (CellContext* pCellContext, int nXpos, int nYpos, unsigned int color, int nTransTbl, unsigned char* pPalette),
      ({ GameVersion::VERSION_112, -10024 },
       { GameVersion::VERSION_113c, -10041 },
       { GameVersion::VERSION_113d, -10042 }));

/*********************************************************************************
 *                                                                               *
 *   D2GLIDE.DLL POINTERS                                                        *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2GLIDE, WindowWidth, int,
      ({ GameVersion::VERSION_112, 0x16DF0 },
       { GameVersion::VERSION_113c, 0x15A68 },
       { GameVersion::VERSION_113d, 0x15A78 }));
D2VAR(D2GLIDE, WindowHeight, int,
      ({ GameVersion::VERSION_112, 0x16E8C },
       { GameVersion::VERSION_113c, 0x15B04 },
       { GameVersion::VERSION_113d, 0x15B14 }));

D2VAR(D2GLIDE, SpritesInited, bool,
      ({ GameVersion::VERSION_112, 0x17B54 },
       { GameVersion::VERSION_113c, 0x17B44 },
       { GameVersion::VERSION_113d, 0x17B54 }));

/*********************************************************************************
 *                                                                               *
 *   D2LANG.DLL POINTERS                                                         *
 *                                                                               *
 *********************************************************************************/
D2FUNC(D2LANG, GetLocaleText, wchar_t*, __fastcall, (short nLocaleTxtNo),
      ({ GameVersion::VERSION_112, -10005 },
       { GameVersion::VERSION_113c, 0 },
       { GameVersion::VERSION_113d, -10004 }));

/*********************************************************************************
 *                                                                               *
 *   D2WIN.DLL POINTERS                                                          *
 *                                                                               *
 *********************************************************************************/
D2FUNC(D2WIN, DrawFramedText, void, __fastcall, (const wchar_t * wStr, int X, int Y, int nColor, int Centered),
      ({ GameVersion::VERSION_112, -10031 },
       { GameVersion::VERSION_113c, 0 },
       { GameVersion::VERSION_113d, -10137 }));

D2FUNC(D2WIN, LoadCellFile, CellFile*, __fastcall, (const char* szFile, int Type),
      ({ GameVersion::VERSION_112, -10186 },
       { GameVersion::VERSION_113c, -10111 },
       { GameVersion::VERSION_113d, -10023 }));

D2PTR(D2WIN, LoadMpq_I,
      ({ GameVersion::VERSION_112, 0x7E40 },
       { GameVersion::VERSION_113c, 0x7E60 },
       { GameVersion::VERSION_113d, 0x7E50 }));

/*********************************************************************************
 *                                                                               *
 *   FOG.DLL POINTERS                                                            *
 *                                                                               *
 *********************************************************************************/
D2FUNC(FOG, FreeClientMemory, void, __fastcall, (void* pMemoryToFree, const char* szFile, int nLine, void* pNull),
      ({ GameVersion::VERSION_112, -10043 },
       { GameVersion::VERSION_113c, -10043 },
       { GameVersion::VERSION_113d, -10043 }));

/*********************************************************************************
 *                                                                               *
 *   GLIDE3X.DLL POINTERS                                                        *
 *                                                                               *
 *********************************************************************************/
D2VAR(GLIDE3X, WindowWidthPtr, int*,
      ({ GameVersion::VERSION_107, 0x1C9A0 },
       { GameVersion::VERSION_108, 0x1C9A0 },
       { GameVersion::VERSION_109, 0x1C9A0 },
       { GameVersion::VERSION_109b, 0x1C9A0 },
       { GameVersion::VERSION_109c, 0x1C9A0 },
       { GameVersion::VERSION_109d, 0x1C9A0 },
       { GameVersion::VERSION_110, 0x1C9A0 },
       { GameVersion::VERSION_111, 0x1C9A0 },
       { GameVersion::VERSION_111b, 0x1C9A0 },
       { GameVersion::VERSION_112, 0x1C9A0 },
       { GameVersion::VERSION_113c, 0x1C9A0 },
       { GameVersion::VERSION_113d, 0x1C9A0 },
       { GameVersion::VERSION_114a, 0x1C9A0 },
       { GameVersion::VERSION_114b, 0x1C9A0 },
       { GameVersion::VERSION_114c, 0x1C9A0 },
       { GameVersion::VERSION_114d, 0x1C9A0 }));
D2VAR(GLIDE3X, WindowHeightPtr, int*,
      ({ GameVersion::VERSION_107, 0x1C82C },
       { GameVersion::VERSION_108, 0x1C82C },
       { GameVersion::VERSION_109, 0x1C82C },
       { GameVersion::VERSION_109b, 0x1C82C },
       { GameVersion::VERSION_109c, 0x1C82C },
       { GameVersion::VERSION_109d, 0x1C82C },
       { GameVersion::VERSION_110, 0x1C82C },
       { GameVersion::VERSION_111, 0x1C82C },
       { GameVersion::VERSION_111b, 0x1C82C },
       { GameVersion::VERSION_112, 0x1C82C },
       { GameVersion::VERSION_113c, 0x1C82C },
       { GameVersion::VERSION_113d, 0x1C82C },
       { GameVersion::VERSION_114a, 0x1C82C },
       { GameVersion::VERSION_114b, 0x1C82C },
       { GameVersion::VERSION_114c, 0x1C82C },
       { GameVersion::VERSION_114d, 0x1C82C }));

// end of file -----------------------------------------------------------------
#endif
