#pragma once

#include "D2Structs.h"

#ifdef _D2VARS_H
#define VAR(Type, Name)         Type Name;
#else
#define VAR(Type, Name)         extern Type Name;
#endif

/****************************************************************************
*                                                                           *
*   D2Vars.h                                                                *
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
*   This file is used to declare your own global variables to use           *
*   within your code. These variables can be used anywhere in your code     *
*                                                                           *
*****************************************************************************/

VAR(DWORD, LeftPanelBackgroundColor)
VAR(DWORD, LeftPanelBorderColor)
VAR(DWORD, RightPanelBorderColor)
VAR(DWORD, RightPanelBackgroundColor)

VAR(BOOL, EnableCinematicsFix)
VAR(BOOL, EnableD2MRPanelBorderStyle)
VAR(BOOL, InvertD2MRControlPanel)
VAR(BOOL, EnableD2MRBackgroundRibbon)
VAR(BOOL, Enable800ControlPanel)

VAR(HANDLE, D2MRArchive)

VAR(CellFile*, D2MRStoneBack)

VAR(CellFile*, D2MRFancyBorderBottom)
VAR(CellFile*, D2MRFancyBorderCorner)
VAR(CellFile*, D2MRFancyBorderInterfaceLeft)
VAR(CellFile*, D2MRFancyBorderInterfaceRight)
VAR(CellFile*, D2MRFancyBorderLeft)
VAR(CellFile*, D2MRFancyBorderRight)
VAR(CellFile*, D2MRFancyBorderTop)
VAR(CellFile*, D2MRFancyHorizontalBar)
VAR(CellFile*, D2MRFancyPanelBar)
VAR(CellFile*, D2MRFancyPanelLeft)
VAR(CellFile*, D2MRFancyPanelRight)
VAR(CellFile*, D2MRFancyVerticalBar)

// end of file ---------------------------------------------------------------
#undef _D2VARS_H