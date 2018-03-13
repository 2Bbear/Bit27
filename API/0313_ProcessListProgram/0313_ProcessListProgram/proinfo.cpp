#include"std.h"

PROINFO PrintProcessNameAndID(DWORD processID) {
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
			throw TEXT("����");
	}
	else throw TEXT("������");
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

	// process list ��������(id��)
	DWORD aProcess[1024], cbNeeded, cProcesses;
	unsigned int i;
	//���μ����� ������ ����
	if (!EnumProcesses(aProcess, sizeof(aProcess), &cbNeeded))
		// �迭 ��, ���ϵǴ� ����Ʈ �� 
		// �迭�� id������ ����.
		return;
	// �󸶳� ���� ���μ������� ���ϵǾ��� ���
	cProcesses = cbNeeded / sizeof(DWORD);
	// process �̸� ���
	for (i = 0; i < cProcesses; i++)
	{
		try
		{
		datalist->push_back(PrintProcessNameAndID(aProcess[i]));//data ����
		}
		catch (TCHAR * str) 
		{
			
		}
	}
		

	//���μ��� ���� �ѱ��
	*size = datalist->size();

	//print
	//printf("%d", cProcesses);

}
