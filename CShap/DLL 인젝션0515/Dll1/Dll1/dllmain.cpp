// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"


DWORD WINAPI ThreadProc(LPVOID lParam) // Thread, 로드라이브러리를 통해서 이 내용을 실행 시킨다.
{
	MessageBoxA(0, "Dll Injection", "이렇게 성공!", 0);
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved )
{
	HANDLE hThread = NULL;
    switch (ul_reason_for_call)
    {
	case DLL_PROCESS_ATTACH: // DLL이 프로세스에  Attach 되었을 때
	{
		hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
		CloseHandle(hThread);
		break;
	}
    }
    return TRUE;
}


