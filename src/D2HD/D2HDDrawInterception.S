.intel_syntax
.global _determineVideoOptionTextInterception

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
