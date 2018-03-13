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
 *   Defines interception functions with low-level x86 code to safely      *
 *   allow modifying Diablo II's internal code.                            *
 *                                                                         *
 *   Used by GCC as a replacement for __declspec(naked).                   *
 *                                                                         *
 ***************************************************************************/

.intel_syntax

.text
.global _repositionPanelsInterception
.global _getPatchedResolutionModeInterception
.global _getModeParamsInterception107
.global _getModeParamsInterception111
.global _resizeGameLogicResolutionInterception
.global _resizeGameWindowResizeWidthInterception
.global _resizeGameWindowResizeHeightInterception
.global _setResolutionModeEAXInterception
.global _setResolutionModeEDIInterception
.global _setResolutionModeFromMenuInterception
.global _isMouseOverStatsButtonInterception
.global _isMouseOverSkillButtonInterception
.global _setGDIRenderResolutionInterception
.global _setGDIForegroundRenderWidthInterception
.global _setDirectDrawRenderResolutionInterception
.global _setDirect3DRenderResolutionInterception
.global _setGlideRenderResolutionInterception
.global _setupGlideWindowSizeInterception

_repositionPanelsInterception:
    pushad
    call _repositionPanels
    popad
    ret

_getPatchedResolutionModeInterception:
    sub esp, 4
    lea eax, dword ptr [esp]
    pushad
    push eax
    call _getPatchedResolutionMode@4
    popad
    mov eax, dword ptr [eax]
    add esp, 4
    ret

_getModeParamsInterception107:
    push ecx
    lea ecx, dword ptr [esp + 18]
    sub esp, 4
    lea eax, dword ptr [esp]
    pushad
    push eax
    push ecx
    push ebx
    call _getModeParams@12
    popad
    mov eax, dword ptr [esp]
    add esp, 4
    pop ecx
    ret

_getModeParamsInterception111:
    pushad
    push eax
    push ecx
    push edx
    call _getModeParams@12
    popad
    ret

_resizeGameLogicResolutionInterception:
    pushad
    push esi
    call _resizeGameLogicResolution@4
    popad
    ret

_resizeGameWindowResizeWidthInterception:
    sub esp, 4
    lea edx, [esp]
    pushad
    push edx
    call _getGameWindowWidth@4
    popad
    add esp, 4

    cmp eax, [edx]
    ret

_resizeGameWindowResizeHeightInterception:
    sub esp, 4
    lea edx, [esp]
    pushad
    push edx
    call _getGameWindowHeight@4
    popad
    add esp, 4

    cmp ecx, [edx]
    ret

_setResolutionModeEAXInterception:
    sub esp, 4
    lea esi, dword ptr [esp]
    pushad
    push eax
    push esi
    call _setResolutionMode@8
    popad
    mov esi, dword ptr [esi]
    add esp, 4
    ret

_setResolutionModeEDIInterception:
    sub esp, 4
    lea esi, dword ptr [esp]
    pushad
    push edi
    push esi
    call _setResolutionMode@8
    popad
    mov esi, dword ptr [esi]
    add esp, 4
    ret

_setResolutionModeFromMenuInterception:
    pushad
    lea ecx, dword ptr [ecx + 0x124]
    push ecx
    call _setResolutionModeFromMenu@4
    popad
    ret

_isMouseOverStatsButtonInterception:
    sub esp, 4
    lea eax, dword ptr [esp]
    pushad
    push eax
    call _isMouseOverStatsButton@4
    popad
    mov eax, dword ptr [esp]
    add esp, 4
    ret

_isMouseOverSkillButtonInterception:
    sub esp, 4
    lea eax, dword ptr [esp]
    pushad
    push eax
    call _isMouseOverSkillButton@4
    popad
    mov eax, dword ptr [esp]
    add esp, 4
    ret

_setGDIRenderResolutionInterception:
    sub esp, 8
    lea esi, dword ptr [esp]
    lea edx, dword ptr [esp + 4]
    pushad
    push edx
    push esi
    push eax
    call _getModeParams@12
    popad
    mov esi, dword ptr [esi]
    mov edx, dword ptr [edx]
    add esp, 8
    ret

_setGDIForegroundRenderWidthInterception:
    pushad
    push esi
    call _setGDIForegroundRenderWidth@4
    popad
    ret

_setDirectDrawRenderResolutionInterception:
    sub esp, 8
    lea ecx, dword ptr [esp]
    lea edx, dword ptr [esp + 4]
    pushad
    push edx
    push ecx
    push eax
    call _setDirectDrawRenderResolution@12
    popad
    mov ecx, dword ptr [ecx]
    mov edx, dword ptr [edx]
    add esp, 8
    ret

_setDirect3DRenderResolutionInterception:
    pushad
    push eax
    call _setDirect3DRenderResolution@4
    popad
    ret

_setGlideRenderResolutionInterception:
    sub esp, 4
    lea ecx, dword ptr [esp]
    pushad
    push ecx
    push esi
    call _setGlideRenderResolution@8
    popad
    mov ecx, dword ptr [ecx]
    add esp, 4

    // Original code
    xor edx, edx
    mov esi, 1
    ret

_setupGlideWindowSizeInterception:
    pushad
    push eax
    call _setupGlideWindowSize@4
    popad
    ret
