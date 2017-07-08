#pragma once

#ifndef _D2PTRS_H
#define _D2PTRS_H

/****************************************************************************
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  These are the macros used by the template core to declare                                                                                                                                   ///
//  pointers. Do not touch unless you know what you're doing                                                                                                                                    ///
//                                                                                                                                                                                              ///
#define D2FUNC(DLL, NAME, RETURN, CONV, ARGS, OFFSET) typedef RETURN (##CONV##* DLL##_##NAME##_t ) ARGS; static DLL##_##NAME##_t DLL##_##NAME = (DLL##_##NAME##_t )( DLLBASE_##DLL + OFFSET);   ///
#define D2VAR(DLL, NAME, TYPE, OFFSET) typedef TYPE DLL##_##NAME##_vt; static DLL##_##NAME##_vt * DLL##_##NAME = (DLL##_##NAME##_vt *)( DLLBASE_##DLL + OFFSET);                                ///
#define D2PTR(DLL, NAME, OFFSET) static DWORD NAME = (DLLBASE_##DLL + OFFSET);                                                                                                                  ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
*                                                                               *
*   D2CMP.DLL POINTERS                                                          *
*                                                                               *
*********************************************************************************/
D2FUNC(D2CMP, FreeCellFile, BOOL, __stdcall, (CellFile* pCellFile), 0x11520); // Called at D2Client.dll+26E1C,8022E

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
D2VAR(D2CLIENT, ScreenSizeX, DWORD, 0xDBC48);
D2VAR(D2CLIENT, ScreenSizeY, DWORD, 0xDBC4C);
D2VAR(D2CLIENT, PanelOffsetX, int, 0x11B9A0);
D2VAR(D2CLIENT, PanelOffsetY, int, 0x11B9A4);
D2VAR(D2CLIENT, InventoryArrangeMode, int, 0x11B99C);
D2VAR(D2CLIENT, PanelBorderImage, CellFile*, 0x11A77C);
D2VAR(D2CLIENT, PanelOpenMode, int, 0x11C414);
D2VAR(D2CLIENT, MaxRegistryResolutionMode, int, 0xEABD8);
D2VAR(D2CLIENT, CurrentRegistryResolutionMode, int, 0xEABDC);
D2VAR(D2CLIENT, SelectedMenuOption, int, 0x11C058);

// Do not call this function directly unless you insert arg0 into EDI
D2FUNC(D2CLIENT, LoadUIImage, CellFile*, __fastcall, (const char* szImage), 0xBF6C0);

// Only use as a reference! Called inside of D2client.dll+C39E0
D2FUNC(D2CLIENT, DrawMercenaryInventoryPanel, void*, __fastcall, (), 0x9AE80);
D2FUNC(D2CLIENT, DrawInfusScrollPanel, void*, __fastcall, (), 0x7DE00);
D2FUNC(D2CLIENT, DrawInventoryPanel, void*, __fastcall, (), 0x99440);
D2FUNC(D2CLIENT, DrawQuestPanel, void*, __fastcall, (), 0x1EF10);
D2FUNC(D2CLIENT, DrawSkillPanel, void*, __fastcall, (), 0x78F20);
D2FUNC(D2CLIENT, DrawStatPanel, void*, __fastcall, (), 0xBCEA0);


/********************************************************************************
*                                                                               *
*   D2COMMON.DLL POINTERS                                                       *
*                                                                               *
*********************************************************************************/
D2VAR(D2COMMON, InventoryTxt, InventoryTxt*, 0x9FA5C);

/********************************************************************************
*                                                                               *
*   D2DDRAW.DLL POINTERS                                                        *
*                                                                               *
*********************************************************************************/
D2VAR(D2DDRAW, GameWindowSizeY, DWORD*, 0x101D8);

/********************************************************************************
*                                                                               *
*   D2GDI.DLL POINTERS                                                          *
*                                                                               *
*********************************************************************************/
D2VAR(D2GDI, ForegroundRenderWidth, DWORD, 0xCA9C);

/********************************************************************************
*                                                                               *
*   D2GFX.DLL POINTERS                                                          *
*                                                                               *
*********************************************************************************/
D2VAR(D2GFX, GfxMode, int, 0x11258);
D2VAR(D2GFX, ResolutionMode, int, 0x11260);

D2FUNC(D2GFX, GetResolutionMode, int, __stdcall, (), 0xB320);
D2FUNC(D2GFX, DrawImage, void, __stdcall, (CellContext* pCellContext, int nXpos, int nYpos, DWORD color, int nTransTbl, unsigned char* pPalette), 0xB080);

/********************************************************************************
*                                                                               *
*   D2GLIDE.DLL POINTERS                                                        *
*                                                                               *
*********************************************************************************/
D2VAR(D2GLIDE, ScreenSizeX, DWORD, 0x15A68);
D2VAR(D2GLIDE, ScreenSizeY, DWORD, 0x15B04);

/********************************************************************************
*                                                                               *
*   D2WIN.DLL POINTERS                                                          *
*                                                                               *
*********************************************************************************/
D2FUNC(D2WIN, LoadCellFile, CellFile*, __fastcall, (const char* szFile, int Type), 0xA7A0);

D2PTR(D2WIN, LoadMpq_I, 0x7E60);

/********************************************************************************
*                                                                               *
*   GLIDE3X.DLL POINTERS                                                        *
*                                                                               *
*********************************************************************************/
D2VAR(GLIDE3X, GameWindowSizeX, DWORD*, 0x1C9A0);
D2VAR(GLIDE3X, GameWindowSizeY, DWORD*, 0x1C82C);

/********************************************************************************
*                                                                               *
*   FOG.DLL POINTERS                                                            *
*                                                                               *
*********************************************************************************/
D2VAR(FOG, InGame, BOOL, 0x4C804);

D2FUNC(FOG, FreeClientMemory, void, __fastcall, (void* pMemoryToFree, const char* szFile, int nLine, void* pNull), 0x1CCF0);

/********************************************************************************
*                                                                               *
*   STORM.DLL POINTERS                                                          *
*                                                                               *
*********************************************************************************/
D2VAR(STORM, IsCinematic, BOOL, 0x54D74);

D2FUNC(STORM, CloseArchive, BOOL, __stdcall, (HANDLE hArchive), 0x26CB0) // Storm.Ordinal252

// end of file -----------------------------------------------------------------
#endif