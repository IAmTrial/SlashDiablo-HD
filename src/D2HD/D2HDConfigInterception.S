/*****************************************************************************
 *                                                                           *
 *   D2HDConfigInterception.S                                                *
 *   Copyright (C) 2017 Mir Drualga                                          *
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
 *   Defines the interception functions that are to be used when there is a  *
 *   need to replace Diablo II code with code that is declared under the     *
 *   configurations scope.                                                   *
 *                                                                           *
 *****************************************************************************/

.intel_syntax
.global _getConfigResolutionInterception@4
.global _setConfigResolutionInterception@4

_getConfigResolutionInterception@4:
    push eax
    mov eax, dword ptr [esp + 8]
    pushad
    push eax
    call _getConfigResolution@4
    popad
    pop eax
    ret 4

_setConfigResolutionInterception@4:
    push eax
    mov eax, dword ptr [esp + 8]
    pushad
    push eax
    call _setConfigResolution@4
    popad
    pop eax
    ret 4
