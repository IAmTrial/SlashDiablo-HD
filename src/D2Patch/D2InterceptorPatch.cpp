/*****************************************************************************
 *                                                                           *
 *   D2IntercerptorPatch.cpp                                                 *
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
 *   This file defines the D2InterceptorPatch class, which is specifically   *
 *   designed to simplify replacing Diablo II code with interception         *
 *   functions.                                                              *
 *                                                                           *
 *****************************************************************************/

#include "D2InterceptorPatch.h"

#include <windows.h>
#include <memory>

#include "../D2Offset.h"
#include "D2BasePatch.h"

D2InterceptorPatch::D2InterceptorPatch(const D2Offset& d2Offset,
                                       const OpCode& opCode, void* const pFunc,
                                       const size_t patchSize) : D2BasePatch(d2Offset, patchSize), opCode(opCode),
    pFunc(pFunc) {
}

bool D2InterceptorPatch::applyPatch() const {
    HANDLE gameHandle = GetCurrentProcess();

    // Do not patch if the no patch flag is set.
    if ((getD2Offset().getCurrentOffset() & D2Patch::NO_PATCH) ==
            D2Patch::NO_PATCH) {
        return true;
    }

    // Grab the address for the correct version.
    LPVOID targetAddress = (LPVOID) getD2Offset().getCurrentAddress();

    if (targetAddress == 0) {
        return false;
    }

    // Get the relative address of the function pointer. Add one due to opcode.
    void* pRelativeFunc = (void*)((size_t) pFunc - ((DWORD)targetAddress + sizeof(
                                      pFunc) + 1));

    // Cannot patch a function call with less than 5 bytes.
    if (getPatchSize() < 5) {
        return false;
    }

    // Create the buffer that will store the patch code, and the fill the rest
    // with NOP.
    std::unique_ptr<BYTE[]> buffer(new BYTE[getPatchSize()]);
    buffer[0] = (int) getOpCode();
    *((void**)&buffer[1]) = pRelativeFunc;

    for (size_t i = sizeof(pFunc) + 1; i < getPatchSize(); i++) {
        buffer[i] = (BYTE) OpCode::NOP;
    }

    // Write the patch into the game's memory region.
    DWORD oldProtect;
    VirtualProtect(targetAddress, getPatchSize(), PAGE_EXECUTE_READWRITE, &oldProtect);
    bool writeSuccess = WriteProcessMemory(gameHandle, targetAddress,
                                           buffer.get(), getPatchSize(), nullptr);
    VirtualProtect(targetAddress, getPatchSize(), oldProtect, &oldProtect);

    if (!writeSuccess) {
        return false;
    }

    return true;
}

OpCode D2InterceptorPatch::getOpCode() const {
    return opCode;
}
