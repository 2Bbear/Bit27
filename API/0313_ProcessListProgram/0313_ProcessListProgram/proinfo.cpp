#include"std.h"

PROINFO PrintProcessNameAndID(DWORD processID) {
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
			throw TEXT("에러");
	}
	else throw TEXT("에러당");
	////print
	//_tprintf(TEXT("%s ( PROCESS ID : %u )\n"), szProcessName, processID);
	PROINFO info;
	_tcscpy_s(info.name, szProcessName);
	info.id = processID;

	CloseHandle(hProcess);

	return info;
}

void pro_getProcessList(vector<PROINFO> * datalist, int * size)
{

	// process list 가져오기(id값)
	DWORD aProcess[1024], cbNeeded, cProcesses;
	unsigned int i;
	//프로세스의 정보를 나열
	if (!EnumProcesses(aProcess, sizeof(aProcess), &cbNeeded))
		// 배열 수, 리턴되는 바이트 수 
		// 배열에 id값들이 들어간다.
		return;
	// 얼마나 많은 프로세스들이 리턴되었나 계산
	cProcesses = cbNeeded / sizeof(DWORD);
	// process 이름 출력
	for (i = 0; i < cProcesses; i++)
	{
		try
		{
		datalist->push_back(PrintProcessNameAndID(aProcess[i]));//data 저장
		}
		catch (TCHAR * str) 
		{
			
		}
	}
		

	//프로세스 갯수 넘기기
	*size = datalist->size();

	//print
	//printf("%d", cProcesses);

}
