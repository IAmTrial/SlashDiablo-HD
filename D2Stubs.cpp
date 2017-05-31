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