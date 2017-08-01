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

struct PointerOffset {
    int Pointer_113c;
    int Pointer_113d;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  These are the macros used by the template core to declare                                                                                                                                   ///
//  pointers. Do not touch unless you know what you're doing                                                                                                                                    ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define OFFSET(DLL, NAME, DEFTYPE) *(&##DLL##_##NAME##_##DEFTYPE##_POINTERS.Pointer_113c + D2Version::GetGameVersionID())

#define D2FUNC(DLL, NAME, RETURN, CONV, ARGS, ...) \
    static PointerOffset DLL##_##NAME##_D2FUNC_POINTERS = { __VA_ARGS__ }; \
    typedef RETURN (##CONV##* DLL##_##NAME##_t ) ARGS; \
    static DLL##_##NAME##_t DLL##_##NAME = (OFFSET(DLL, NAME, D2FUNC) < 0) ? ((DLL##_##NAME##_t )GetProcAddress((HMODULE)DLLBASE_##DLL, (LPCSTR) -(OFFSET(DLL, NAME, D2FUNC)))) : (DLL##_##NAME##_t )( DLLBASE_##DLL + OFFSET(DLL, NAME, D2FUNC));

#define D2VAR(DLL, NAME, TYPE, ...) \
    static PointerOffset DLL##_##NAME##_D2VAR_POINTERS = { __VA_ARGS__ }; \
    typedef TYPE DLL##_##NAME##_vt; \
    static DLL##_##NAME##_vt * DLL##_##NAME = (DLL##_##NAME##_vt *)( DLLBASE_##DLL + OFFSET(DLL, NAME, D2VAR));

#define D2PTR(DLL, NAME, ...) \
    static PointerOffset DLL##_##NAME##_D2PTR_POINTERS = { __VA_ARGS__ }; \
    static DWORD NAME = (OFFSET(DLL, NAME, D2PTR) < 0) ? ((DWORD)GetProcAddress((HMODULE)DLLBASE_##DLL, (LPCSTR) -(OFFSET(DLL, NAME, D2PTR)))) : (DLLBASE_##DLL + OFFSET(DLL, NAME, D2PTR));

/********************************************************************************
*                                                                               *
*   D2CMP.DLL POINTERS                                                          *
*                                                                               *
*********************************************************************************/
D2FUNC(D2CMP, FreeCellFile, BOOL, __stdcall, (CellFile* pCellFile), -10065, -10020); // Called at D2Client.dll+26E1C,8022E

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
D2VAR(D2CLIENT, ScreenSizeX, DWORD, 0xDBC48, 0xF7034);
D2VAR(D2CLIENT, ScreenSizeY, DWORD, 0xDBC4C, 0xF7038);
D2VAR(D2CLIENT, PanelOffsetX, int, 0x11B9A0, 0x11D354);
D2VAR(D2CLIENT, PanelOffsetY, int, 0x11B9A4, 0x11D358);
D2VAR(D2CLIENT, InventoryArrangeMode, int, 0x11B99C, 0x11D2B4);
D2VAR(D2CLIENT, PanelBorderImage, CellFile*, 0x11A77C, 0x103B14);
D2VAR(D2CLIENT, PanelOpenMode, int, 0x11C414, 0x11D070);
D2VAR(D2CLIENT, MaxRegistryResolutionMode, int, 0xEABD8, -1); // Unused by D2HD
D2VAR(D2CLIENT, CurrentRegistryResolutionMode, int, 0xEABDC, 0xE4F44);
D2VAR(D2CLIENT, SelectedMenuOption, int, 0x11C058, -1); // Unused by D2HD
D2VAR(D2CLIENT, VideoOptionCellFileStart, void*, 0xEA568, 0xE48D0);

// Do not call this function directly unless you insert arg0 into EDI
D2FUNC(D2CLIENT, LoadUIImage, CellFile*, __fastcall, (const char* szImage), 0xBF6C0, 0x191F0);

// Only use as a reference! Called inside of D2client.dll+C39E0! All unused by D2HD!
D2FUNC(D2CLIENT, DrawMercenaryInventoryPanel, void*, __fastcall, (), 0x9AE80, -1);
D2FUNC(D2CLIENT, DrawInfusScrollPanel, void*, __fastcall, (), 0x7DE00, -1);
D2FUNC(D2CLIENT, DrawInventoryPanel, void*, __fastcall, (), 0x99440, -1);
D2FUNC(D2CLIENT, DrawQuestPanel, void*, __fastcall, (), 0x1EF10, -1);
D2FUNC(D2CLIENT, DrawSkillPanel, void*, __fastcall, (), 0x78F20, -1);
D2FUNC(D2CLIENT, DrawStatPanel, void*, __fastcall, (), 0xBCEA0, -1);


/********************************************************************************
*                                                                               *
*   D2COMMON.DLL POINTERS                                                       *
*                                                                               *
*********************************************************************************/
D2VAR(D2COMMON, InventoryTxt, InventoryTxt*, 0x9FA5C, 0xA4CAC);

/********************************************************************************
*                                                                               *
*   D2DDRAW.DLL POINTERS                                                        *
*                                                                               *
*********************************************************************************/
D2VAR(D2DDRAW, GameWindowSizeY, DWORD*, 0x101D8, -1);

/********************************************************************************
*                                                                               *
*   D2GDI.DLL POINTERS                                                          *
*                                                                               *
*********************************************************************************/
D2VAR(D2GDI, ForegroundRenderWidth, DWORD, 0xCA9C, 0xCA98);

/********************************************************************************
*                                                                               *
*   D2GFX.DLL POINTERS                                                          *
*                                                                               *
*********************************************************************************/
D2VAR(D2GFX, GfxMode, int, 0x11258, -1); // Unused by D2HD
D2VAR(D2GFX, ResolutionMode, int, 0x11260, 0x14A40);

D2FUNC(D2GFX, GetResolutionMode, int, __stdcall, (), -10031, -10012);
D2FUNC(D2GFX, DrawCellContext, void, __stdcall, (CellContext* pCellContext, int nXpos, int nYpos, DWORD color, int nTransTbl, unsigned char* pPalette), -10041, -10042);

/********************************************************************************
*                                                                               *
*   D2GLIDE.DLL POINTERS                                                        *
*                                                                               *
*********************************************************************************/
D2VAR(D2GLIDE, ScreenSizeX, DWORD, 0x15A68, 0x15A78);
D2VAR(D2GLIDE, ScreenSizeY, DWORD, 0x15B04, 0x15B14);

/********************************************************************************
*                                                                               *
*   D2WIN.DLL POINTERS                                                          *
*                                                                               *
*********************************************************************************/
D2FUNC(D2WIN, LoadCellFile, CellFile*, __fastcall, (const char* szFile, int Type), -10111, -10023);
D2PTR(D2WIN, LoadMpq_I, 0x7E60, 0x7E50);

/********************************************************************************
*                                                                               *
*   GLIDE3X.DLL POINTERS                                                        *
*                                                                               *
*********************************************************************************/
D2VAR(GLIDE3X, GameWindowSizeX, DWORD*, 0x1C9A0, 0x1C9A0);
D2VAR(GLIDE3X, GameWindowSizeY, DWORD*, 0x1C82C, 0x1C82C);

/********************************************************************************
*                                                                               *
*   FOG.DLL POINTERS                                                            *
*                                                                               *
*********************************************************************************/
D2VAR(FOG, InGame, BOOL, 0x4C804, 0xF79E0);

D2FUNC(FOG, FreeClientMemory, void, __fastcall, (void* pMemoryToFree, const char* szFile, int nLine, void* pNull), -10043, -10043);

/********************************************************************************
*                                                                               *
*   STORM.DLL POINTERS                                                          *
*                                                                               *
*********************************************************************************/
D2FUNC(STORM, CloseArchive, BOOL, __stdcall, (HANDLE hArchive), -252, -252) // Storm.Ordinal252

// end of file -----------------------------------------------------------------
#endif