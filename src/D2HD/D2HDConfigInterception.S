/*****************************************************************************
 *                                                                           *
 *  SlashDiablo HD                                                           *
 *  Copyright (C) 2017  Mir Drualga                                          *
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
 *---------------------------------------------------------------------------*
 *                                                                           *
 *   Defines the interception functions that are to be used when there is    *
 *   a need to replace Diablo II code with code that is declared under the   *
 *   configurations scope.                                                   *
 *                                                                           *
 *****************************************************************************/

.intel_syntax
.global _getConfigResolutionInterception@4
.global _setConfigResolutionInterception@4

_getConfigResolutionInterception@4:
    mov eax, dword ptr [esp + 4]
    pushad
    push eax
    call _getConfigResolution@4
    popad

    mov eax, 1
    ret 4

_setConfigResolutionInterception@4:
    mov eax, dword ptr [esp + 4]
    pushad
    push eax
    call _setConfigResolution@4
    popad

    mov eax, 1
    ret 4
