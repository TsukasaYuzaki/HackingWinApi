#include "Myinclude.h"

DWORD Timprocess(const wchar_t* procName);

uintptr_t TimMemory(DWORD procId, const wchar_t* modName);

uintptr_t TimDMA(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offset);
