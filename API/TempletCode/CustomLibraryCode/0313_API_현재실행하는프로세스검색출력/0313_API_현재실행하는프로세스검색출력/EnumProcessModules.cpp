#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "psapi.h"		
void PrintProcessNameAndID(DWORD processID) {
	TCHAR szProcessName[MAX_PATH] = TEXT("unknown");
	// 프로세스의 핸들 얻기
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ, FALSE, processID);
	// process 이름 가져오기
	if (NULL != hProcess) {
		HMODULE hMod;
		DWORD	cbNeeded;
		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
		}
		else
			return;
	}
	else return;
	//print
	_tprintf(TEXT("%s ( PROCESS ID : %u )\n"), szProcessName, processID);
	CloseHandle(hProcess);
}
void main()
{
	// process list 가져오기(id값)
	DWORD aProcess[1024], cbNeeded, cProcesses;
	unsigned int i;
	//지정된 프로세스의 각 모듈에 대한 핸들을 검색하는 함수
	if (!EnumProcesses(aProcess, sizeof(aProcess), &cbNeeded))
		// 배열 수, 리턴되는 바이트 수 
		// 배열에 id값들이 들어간다.
		return;
	// 얼마나 많은 프로세스들이 리턴되었나 계산
	cProcesses = cbNeeded / sizeof(DWORD);
	// process 이름 출력
	for (i = 0; i < cbNeeded; i++)
		PrintProcessNameAndID(aProcess[i]);
}
