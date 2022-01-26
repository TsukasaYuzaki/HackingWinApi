#include "D:\\HackingGameWinAPi\\Myinclude.h"

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


void _displayProcess(){

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if(hSnap != INVALID_HANDLE_VALUE){

		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(PROCESSENTRY32);

		if(Process32First(hSnap, &procEntry)){
			do{
				#undef UNICODE
				std::wcout << procEntry.szExeFile << std::endl;
				
			}
			while(Process32Next(hSnap, &procEntry));
		}
			
	}

	CloseHandle(hSnap);

}


int _terminateProcess(const wchar_t* procName){
 
	DWORD procId = 0;
	procId = Timprocess(procName);

	if(procId != 0){
		HANDLE hProcess = 0;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

		TerminateProcess(hProcess, 0);

		CloseHandle(hProcess);

		return 1;
	}

	else return 0;
}



int main(){


	std::cout << "\nFirst list: \n";
	
	_displayProcess();

	std::cout << "\nAfter terminating: \n";

	while(_terminateProcess(L"Calculator.exe") == 1){
		
	}
  
	_displayProcess();
	return 0;
}
