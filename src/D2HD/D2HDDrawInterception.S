.intel_syntax
.global _determineVideoOptionTextInterception
.global _drawControlPanelInterception
.global _drawPanelBackgroundInterception
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

_drawControlPanelInterception:
    pushad
    call _drawControlPanel
    popad

    //Original code
    xor edi, edi
    sub eax, 2
    ret

_drawPanelBackgroundInterception:
    pushad
    call _drawPanelBackground
    popad

    //Original code
    add esp, 0x128
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
