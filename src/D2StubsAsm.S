/*****************************************************************************
 *                                                                           *
 *   D2StubsAsm.S                                                            *
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
 *   Defines the x86 functions that are used to help call functions in       *
 *   Diablo II that do not conform to standard calling conventions.          *
 *                                                                           *
 *****************************************************************************/
.intel_syntax

.global _loadMPQStub@28

_loadMPQStub@28:
    push dword ptr [esp + 0x18]
    push dword ptr [esp + 0x18]
    push dword ptr [esp + 0x18]
    push dword ptr [esp + 0x18]
    push dword ptr [esp + 0x18]
    mov eax, dword ptr [esp + 0x18]
    call dword ptr [esp + 0x30]
    ret 0x1C

