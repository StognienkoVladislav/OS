#include <windows.h>
#include <tlhelp32.h>
#include "psapi.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <iostream>

using namespace std;

VOID PrintProcessList(HANDLE CONST hStdOut) {
	PROCESSENTRY32 peProcessEntry; //Cтруктура с инфой о процессе

	HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //Снимок о процессах 

	peProcessEntry.dwSize = sizeof(PROCESSENTRY32); //Размер структуры
	Process32First(hSnapshot, &peProcessEntry);

	do {
		wcout << "Name : " << peProcessEntry.szExeFile << " id : " << peProcessEntry.th32ProcessID << endl;

		HANDLE nameProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, peProcessEntry.th32ProcessID);

	} while (Process32Next(hSnapshot, &peProcessEntry));

	CloseHandle(hSnapshot);
}

INT main() {
	HANDLE CONST hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	PrintProcessList(hStdOut);

	cout << "\n////////////////////////////////////////////////////////////////////////////////\n";

	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);
	
	cout << " OEM ID : " << siSysInfo.dwOemId << endl;
	cout << " Number of processors " << siSysInfo.dwNumberOfProcessors << endl;
	cout << " Page size : " << siSysInfo.dwPageSize << endl;
	cout << " Processor type : " << siSysInfo.dwProcessorType << endl;
	cout << " Minimum application address : " << siSysInfo.lpMinimumApplicationAddress << endl;
	cout << " Maximum application address : " << siSysInfo.lpMaximumApplicationAddress << endl;
	cout << " Active processor mask : " << siSysInfo.dwActiveProcessorMask << endl;

	cout << endl;
	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);
	cout << " " << statex.dwMemoryLoad << "% in use " << endl;
	cout << " " << statex.ullTotalPhys / 1048576 << "  MB at all " << endl;
	cout << " " << statex.ullAvailPhys / 1048576 << "MB is Free " << endl;
	cout << " " << statex.ullAvailPhys / 1048576 << "MB of total padding file " << endl;
	cout << " " << statex.ullAvailPageFile / 1048576 << "MB of free padding file " << endl;
	cout << " " << statex.ullTotalVirtual / 1048576 << "MB of total virtual file " << endl;
	cout << " " << statex.ullAvailVirtual / 1048576 << "MB of free virtual file  " << endl;
	cout << " " << statex.ullAvailExtendedVirtual / 1048576 << "MB extended memoru free " << endl;

	system("PAUSE");
	ExitProcess(0);	
}
