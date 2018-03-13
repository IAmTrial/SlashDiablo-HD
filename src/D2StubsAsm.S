/***************************************************************************
 *                                                                         *
 *   SlashDiablo HD                                                        *
 *   Copyright (C) 2017  Mir Drualga                                       *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 *-------------------------------------------------------------------------*
 *                                                                         *
 *   Defines the x86 functions that are used to help call functions in     *
 *   Diablo II that do not conform to standard calling conventions.        *
 *                                                                         *
 ***************************************************************************/
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

