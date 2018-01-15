/*****************************************************************************
 *                                                                           *
 *   D2HDPatchesInterception.S                                               *
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
 *   Defines interception functions with low-level x86 code to safely allow  *
 *   modifying Diablo II's internal code.                                    *
 *                                                                           *
 *   Used by GCC as a replacement for __declspec(naked).                     *
 *                                                                           *
 *****************************************************************************/

.intel_syntax
.global _repositionPanelsInterception
.global _getPatchedResolutionModeInterception
.global _resizeGameLogicResolutionInterception
.global _setResolutionModeEAXInterception
.global _setResolutionModeEDIInterception
.global _setResolutionModeFromMenuInterception
.global _setGDIRenderResolutionInterception
.global _setGDIForegroundRenderWidthInterception
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

_resizeGameLogicResolutionInterception:
    pushad
    push esi
    call _resizeGameLogicResolution@4
    popad
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
