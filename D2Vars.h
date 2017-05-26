#pragma once

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

VAR(DWORD, SampleVariable1)

VAR(void*, SampleVariable2)

VAR(char, SampleVariable3[256])

VAR(DWORD, LeftPanelBackgroundColor)
VAR(DWORD, LeftPanelBorderColor)
VAR(DWORD, RightPanelBorderColor)
VAR(DWORD, RightPanelBackgroundColor)

VAR(BOOL, EnableCinematicsFix)
VAR(BOOL, EnableD2MRPanelBorderStyle)
VAR(BOOL, InvertD2MRControlPanel)

VAR(void*, D2MRArchive)

VAR(void*, D2MRStoneBack)

VAR(void*, D2MRFancyBorderCorner)
VAR(void*, D2MRFancyBorderBottom)
VAR(void*, D2MRFancyBorderInterfaceLeft)
VAR(void*, D2MRFancyBorderInterfaceRight)
VAR(void*, D2MRFancyBorderTop)
VAR(void*, D2MRFancyPanelBar)
VAR(void*, D2MRFancyPanelLeft)
VAR(void*, D2MRFancyPanelRight)

// end of file ---------------------------------------------------------------
#undef _D2VARS_H