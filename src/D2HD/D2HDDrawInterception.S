.intel_syntax

.text
.global _determineVideoOptionTextInterception
.global _drawControlPanel800ForegroundInterception
.global _drawControlPanelBackgroundInterception
.global _drawPanelBackgroundInterception

.global _drawActiveStatsButtonInterception
.global _drawInactiveStatsButtonInterception
.global _drawStatsButtonTextInterception

.global _drawActiveSkillButtonInterception
.global _drawInactiveSkillButtonInterception
.global _drawSkillButtonTextInterception

.global _unloadCellFilesInterception

_determineVideoOptionTextInterception:
    // Original code
    mov ecx, dword ptr [eax + ecx * 4 + 0x540]

    push edx
    sub esp, 4
    lea edx, dword ptr [esp]
    pushad
    push ecx
    push esi
    push eax
    push edx
    call _determineVideoOptionText@16
    popad
    mov ecx, dword ptr [edx]
    add esp, 4
    pop edx
    ret

_drawControlPanel800ForegroundInterception:
    pushad
    call _drawControlPanel800Foreground
    popad
    ret

_drawControlPanelBackgroundInterception:
    pushad
    call _drawControlPanelBackground
    popad

    //Original code
    mov ecx, 18
    ret

_drawPanelBackgroundInterception:
    pushad
    call _drawPanelBackground
    popad

    //Original code
    add esp, 0x128
    ret

_drawActiveStatsButtonInterception:
    pushad
    call _drawActiveStatsButton@0
    popad
    ret

_drawInactiveStatsButtonInterception:
    pushad
    call _drawInactiveStatsButton@0
    popad
    ret

_drawStatsButtonTextInterception:
    pushad
    call _drawStatsButtonText@0
    popad
    ret

_drawActiveSkillButtonInterception:
    pushad
    call _drawActiveSkillButton@0
    popad
    ret

_drawInactiveSkillButtonInterception:
    pushad
    call _drawInactiveSkillButton@0
    popad
    ret

_drawSkillButtonTextInterception:
    pushad
    call _drawSkillButtonText@0
    popad
    ret

_unloadCellFilesInterception:
    sub esp, 4
    lea esi, dword ptr [esp]
    pushad
    push esi
    call _unloadCellFiles@4
    popad
    mov esi, dword ptr [esi]
    add esp, 4
    ret
