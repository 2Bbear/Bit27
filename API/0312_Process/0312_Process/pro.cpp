#include"std.h"



PROINFO* proc_CreateProcess(TCHAR * buf)
{
	PROCESS_INFORMATION pi;
	STARTUPINFO			si = { sizeof(si) };
	BOOL b = CreateProcess(0, buf, 0, 0,FALSE, NORMAL_PRIORITY_CLASS, 0, 0,&si, &pi);
	//================================================
	PROINFO *p = (PROINFO*)malloc(sizeof(PROINFO));
	_tcscpy_s(p->name, buf);
	p->id = pi.dwProcessId;
	p->handle = pi.hProcess;

	return p;
}

int proc_GetExitCodeProcess(HANDLE p)
{
	DWORD code;
	 GetExitCodeProcess(p, &code);
	 return code;
}

void proc_ExitProcess(HANDLE h)
{
	TerminateProcess(h,-1);//1은 임의의 종료코드
}

