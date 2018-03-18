#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "psapi.h"		
void PrintProcessNameAndID(DWORD processID) {
	TCHAR szProcessName[MAX_PATH] = TEXT("unknown");
	// ���μ����� �ڵ� ���
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ, FALSE, processID);
	// process �̸� ��������
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
	// process list ��������(id��)
	DWORD aProcess[1024], cbNeeded, cProcesses;
	unsigned int i;
	//������ ���μ����� �� ��⿡ ���� �ڵ��� �˻��ϴ� �Լ�
	if (!EnumProcesses(aProcess, sizeof(aProcess), &cbNeeded))
		// �迭 ��, ���ϵǴ� ����Ʈ �� 
		// �迭�� id������ ����.
		return;
	// �󸶳� ���� ���μ������� ���ϵǾ��� ���
	cProcesses = cbNeeded / sizeof(DWORD);
	// process �̸� ���
	for (i = 0; i < cbNeeded; i++)
		PrintProcessNameAndID(aProcess[i]);
}
