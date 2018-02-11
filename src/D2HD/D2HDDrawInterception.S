.intel_syntax

.text
.global _determineVideoOptionTextInterception
.global _drawControlPanel800ForegroundInterception
.global _drawControlPanelBackgroundInterception
.global _drawPanelBackgroundInterception
.global _drawStatsButtonInterception
.global _drawSkillButtonInterception
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

_drawStatsButtonInterception:
    pushad
    call _drawStatsButton
    popad
    ret

_drawSkillButtonInterception:
    pushad
    call _drawSkillButton
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
