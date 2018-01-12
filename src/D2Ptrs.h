/*****************************************************************************
 *                                                                           *
 *   D2Ptrs.h                                                                *
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

#pragma once

#ifndef _D2PTRS_H
#define _D2PTRS_H

#include "D2Offset.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  These are the macros used by the template core to declare                                                                                                                                   ///
//  pointers. Do not touch unless you know what you're doing                                                                                                                                    ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define D2FUNC(DLL, NAME, RETURN, CONV, ARGS, OFFSETS) \
    typedef RETURN (CONV * DLL##_##NAME##_t) ARGS; \
    static D2Offset DLL##_##NAME##_FUNC_OFFSET OFFSETS; \
    static DLL##_##NAME##_t DLL##_##NAME = (DLL##_##NAME##_t)(DLL##_##NAME##_FUNC_OFFSET.getCurrentAddress());

#define D2VAR(DLL, NAME, TYPE, OFFSETS) \
    typedef TYPE DLL##_##NAME##_vt; \
    static D2Offset DLL##_##NAME##_VAR_OFFSET OFFSETS; \
    static DLL##_##NAME##_vt * DLL##_##NAME = (DLL##_##NAME##_vt *)(DLL##_##NAME##_VAR_OFFSET.getCurrentAddress());

#define D2PTR(DLL, NAME, OFFSETS) \
    static D2Offset DLL##_##NAME##_PTR_OFFSET OFFSETS; \
    static DWORD DLL##_##NAME = (DLL##_##NAME##_PTR_OFFSET.getCurrentAddress());

/********************************************************************************
 *                                                                               *
 *   D2GAME.DLL POINTERS                                                         *
 *                                                                               *
 *********************************************************************************/

/********************************************************************************
 *                                                                               *
 *   D2CLIENT.DLL POINTERS                                                       *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2CLIENT, ScreenSizeX, int, (D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xDBC48, 0xF7034, 0, 0, 0, 0 }));
D2VAR(D2CLIENT, ScreenSizeY, int, (D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xDBC4C, 0xF7038, 0, 0, 0, 0 }));
D2VAR(D2CLIENT, PanelBorderImage, CellFile*, (D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x11A77C, 0x103B14, 0, 0, 0, 0 }));
D2VAR(D2CLIENT, PanelOffsetX, int, (D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x11B9A0, 0x11D354, 0, 0, 0, 0 }));
D2VAR(D2CLIENT, PanelOffsetY, int, (D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x11B9A4, 0x11D358, 0, 0, 0, 0 }));
D2VAR(D2CLIENT, PanelOpenMode, int, (D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x11C414, 0x11D070, 0, 0, 0, 0 }));
D2VAR(D2CLIENT, InventoryArrangeMode, int, (D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x11B99C, 0x11D2B4, 0, 0, 0, 0 }));

D2VAR(D2CLIENT, VideoOptionCellFileStart, void*, (D2TEMPLATE_DLL_FILES::D2DLL_D2CLIENT, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xEA568, 0xE48D0, 0, 0, 0, 0 }));

/********************************************************************************
*                                                                               *
*   D2CMP.DLL POINTERS                                                          *
*                                                                               *
*********************************************************************************/
D2FUNC(D2CMP, FreeCellFile, bool, __stdcall, (CellFile* pCellFile), (D2TEMPLATE_DLL_FILES::D2DLL_D2CMP, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -10065, -10020, 0, 0, 0, 0 })); // Called at D2Client.dll+26E1C,8022E

/********************************************************************************
 *                                                                               *
 *   D2COMMON.DLL POINTERS                                                       *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2COMMON, InventoryTxt, InventoryTxt*, (D2TEMPLATE_DLL_FILES::D2DLL_D2COMMON, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x9FA5C, 0xA4CAC, 0, 0, 0, 0 }));

/********************************************************************************
 *                                                                               *
 *   D2GDI.DLL POINTERS                                                          *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2GDI, ForegroundRenderWidth, int, (D2TEMPLATE_DLL_FILES::D2DLL_D2GDI, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xCA9C, 0xCA98, 0, 0, 0, 0 }));

/********************************************************************************
*                                                                               *
*   D2GFX.DLL POINTERS                                                          *
*                                                                               *
*********************************************************************************/
D2FUNC(D2GFX, GetResolutionMode, int, __stdcall, (), (D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -10031, -10012, 0, 0, 0, 0 }));
D2FUNC(D2GFX, DrawCellContext, void, __stdcall, (CellContext* pCellContext, int nXpos, int nYpos, unsigned int color, int nTransTbl, unsigned char* pPalette), (D2TEMPLATE_DLL_FILES::D2DLL_D2GFX, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -10041, -10042, 0, 0, 0, 0 }));

/********************************************************************************
*                                                                               *
*   D2WIN.DLL POINTERS                                                          *
*                                                                               *
*********************************************************************************/
D2FUNC(D2WIN, LoadCellFile, CellFile*, __fastcall, (const char* szFile, int Type), (D2TEMPLATE_DLL_FILES::D2DLL_D2WIN, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -10111, -10023, 0, 0, 0, 0 }));
D2PTR(D2WIN, LoadMpq_I, (D2TEMPLATE_DLL_FILES::D2DLL_D2WIN, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7E60, 0x7E50, 0, 0, 0, 0 }));

/********************************************************************************
*                                                                               *
*   FOG.DLL POINTERS                                                            *
*                                                                               *
*********************************************************************************/
D2FUNC(FOG, FreeClientMemory, void, __fastcall, (void* pMemoryToFree, const char* szFile, int nLine, void* pNull), (D2TEMPLATE_DLL_FILES::D2DLL_FOG, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -10043, -10043, 0, 0, 0, 0 }));

// end of file -----------------------------------------------------------------
#endif
