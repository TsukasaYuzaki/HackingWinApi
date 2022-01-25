#include "proc.h" 
//g++ -DUNICODE Hackgame.cpp proc.cpp -o FULL.exe
int main() {
	DWORD procId = Timprocess(L"ac_client.exe");

	std::cout << procId << std::endl;

	uintptr_t moduleBase = TimMemory(procId, L"ac_client.exe");

	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	uintptr_t dynamicPtrBaseAddr = moduleBase + 0x187C0C;

	std::cout << "dynamicPtrBaseAddr: " << "0x" << std::hex << dynamicPtrBaseAddr << std::endl;

	std::vector<unsigned int> ammoOffset = { 0x364, 0x14, 0x0 };

	uintptr_t ammoAddr = TimDMA(hProcess, dynamicPtrBaseAddr, ammoOffset);

	std::cout << "ammoOffset = " << "0x" << std::hex << ammoAddr << std::endl;

	int ammoValue = 0;

	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);

	std::cout << "Current ammo = " << std::dec << ammoValue << std::endl;

	int newAmmo = 500;
	WriteProcessMemory(hProcess, (BYTE*)ammoAddr, &newAmmo, sizeof(newAmmo), nullptr);

	ReadProcessMemory(hProcess, (BYTE*)ammoAddr, &ammoValue, sizeof(ammoValue), nullptr);
	std::cout << "New ammo = " << std::dec << ammoValue << std::endl;

	getchar();
	return 0;
}
