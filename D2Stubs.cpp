#include "D2Stubs.h"

__declspec(naked) void* __stdcall STUB_D2CLIENT_LoadCellFile(const char* szBuffer) {
    __asm
    {
        PUSH ESI
            MOV ESI, [ESP + 8]
            CALL[D2CLIENT_LoadUIImage]
            POP ESI
            RETN 4
    }
}

__declspec(naked) HANDLE __stdcall STUB_D2WIN_LoadMPQ(DWORD OrderFlag, const char* szDllFile, const char* szMpqFile, const char* szName, DWORD _1, BOOL(__stdcall *fnMPQMissing)()) {
    __asm
    {
        push[esp + 0x18]
            push[esp + 0x18]
            push[esp + 0x18]
            push[esp + 0x18]
            push[esp + 0x18]
            mov eax, [esp + 0x18]
            call[LoadMpq_I]
            ret 0x18
    }
}
