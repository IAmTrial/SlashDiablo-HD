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
 *   Used by GCC as a replacement for __declaspec(naked).                    *
 *                                                                           *
 *****************************************************************************/

.intel_syntax
.global _repositionPanelsInterception

_repositionPanelsInterception:
    pushad
    call _repositionPanels
    popad
    ret
