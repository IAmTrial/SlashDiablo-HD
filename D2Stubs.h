#pragma once

#ifndef _D2STUBS_H
#define _D2STUBS_H

#include "DLLmain.h"
#include "D2Ptrs.h"

CellFile* __stdcall STUB_D2CLIENT_LoadCellFile(const char* szBuffer);
HANDLE __stdcall STUB_D2WIN_LoadMPQ(DWORD OrderFlag, const char* szDllFile, const char* szMpqFile, const char* szName, DWORD _1, BOOL(__stdcall *fnMPQMissing)());

#endif