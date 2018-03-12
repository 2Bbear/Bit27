#pragma once
typedef struct tagPROINFO
{
	TCHAR name[50];
	int id;
	HANDLE handle;

}PROINFO;


PROINFO* proc_CreateProcess(TCHAR * buf);

int proc_GetExitCodeProcess(HANDLE p);

void proc_ExitProcess(HANDLE h);