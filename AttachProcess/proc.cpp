#include "proc.h"

DWORD Timprocess(const wchar_t* procName) {
	//DWORD: process id la DWORD
	//Ten process la unicode-18

	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	//std::cout << hSnap;
	if (hSnap != INVALID_HANDLE_VALUE) {
		//std::cout << "ok Here" << std::endl;;
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry)) {
			do {
				if (!_wcsicmp(procEntry.szExeFile, procName)) {

					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;

}

uintptr_t TimMemory(DWORD procId, const wchar_t* modName) {
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) {
			do {
				if (!_wcsicmp(modEntry.szModule, modName)) {
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

uintptr_t TimDMA(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offset) {
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offset.size(); i++) {
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr = (unsigned int)addr;
		std::cout << "addr: " << addr << std::endl;
		
		addr += offset[i];
	}

	return addr;
}