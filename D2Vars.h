/****************************************************************************
*                                                                           *
*   D2Vars.h                                                                *
*   Copyright (C) Olivier Verville                                          *
*                                                                           *
*   /r/SlashDiablo HD Modifications: Copyright (C) 2017 Mir Drualga         *
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

#pragma once

#include "D2Structs.h"
#include "HD/D2HDColor.h"

#ifdef _D2VARS_H
#define VAR(Type, Name)         Type Name;
#else
#define VAR(Type, Name)         extern Type Name;
#endif

VAR(HD::D2HDColor, LeftPanelBackgroundColor)
VAR(HD::D2HDColor, LeftPanelBorderColor)
VAR(HD::D2HDColor, RightPanelBorderColor)
VAR(HD::D2HDColor, RightPanelBackgroundColor)

VAR(BOOL, EnableD2MRPanelBorderStyle)
VAR(BOOL, InvertD2MRControlPanel)
VAR(BOOL, EnableD2MRBackgroundRibbon)
VAR(BOOL, Enable800ControlPanel)

VAR(unsigned int, CustomWidth)
VAR(unsigned int, CustomHeight)

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
VAR(CellFile*, Blank)

// end of file ---------------------------------------------------------------
#undef _D2VARS_H