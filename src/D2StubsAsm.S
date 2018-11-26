/*****************************************************************************
 *                                                                           *
 * SlashDiablo HD                                                            *
 * Copyright (C) 2017  Mir Drualga                                           *
 *                                                                           *
 *  This program is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU Affero General Public License as published *
 *  by the Free Software Foundation, either version 3 of the License, or     *
 *  (at your option) any later version.                                      *
 *                                                                           *
 *  This program is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU Affero General Public License for more details.                      *
 *                                                                           *
 *  You should have received a copy of the GNU Affero General Public License *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
 *                                                                           *
 * This file incorporates work covered by the following copyright and        *
 * permission notice:                                                        *
 *                                                                           *
 *   ==========================================================              *
 *   D2Ex2                                                                   *
 *   https://github.com/lolet/D2Ex2                                          *
 *   ==========================================================              *
 *   Copyright (c) 2011-2014 Bartosz Jankowski                               *
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
 *   ==========================================================              *
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

