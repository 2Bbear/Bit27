//�ҽ�.cpp
#include "std.h"
//File���� ���� ��Ʈ : 8000
//File���� ���� ������ : 192,168,0.52

extern HANDLE hThread;

void OnLogMessage(TCHAR *msg)
{
	wprintf(TEXT("%s\n"), msg);
	wprintf(TEXT("%s:%d\n"), TEXT("192.168.0.33"), 8000);
}

int main()
{
	_wsetlocale(LC_ALL, L"korean");

	wbnet_StartServer(8000);

	WaitForSingleObject(hThread, INFINITE);

	return 0;
}