#include <Windows.h>
#include<tchar.h>
//You must have make Resource-Dialog 
#include"resource.h"

#include"handler.h"


BOOL OnCreateProcess_1()
{
	WinExec("notepad.exe", SW_SHOW);
	ShellExecute(0, TEXT("open"), TEXT("calc.exe"), 0, 0, SW_SHOW);
	return TRUE;
}

BOOL OnCreateProcess_2()
{
	/* PROCESS_INFORMATION ����

	hProcess ���� ������ ���μ����� ���� �ڵ�
	hThread ���� ������ ���μ����ǿ� ���� �⺻ ������ �ڵ�
	dwProcessId ���μ����� �ĺ��ϴ� �� ����� ID��
	dwThreadId �����带 �ĺ��ϴµ� ����� ID��
	*/

	/*STARTUPINFO

	DWORD cb; ����ü �� ũ��
   LPTSTR lpReserved; ����� �ڸ���µ� �ݵ�� Null�� �־�� ��
   LPTSTR lpDesktop; window station�� desktop��ü�� �̸��� �����Ѵ�
   LPTSTR lpTitle; consol application�� ���� �� ��� ���ο� console â�� caption�� ������ ���ڿ� 
                   GUI application�� ��� NULL�� ���� �ؾ��Ѵ�.
   DWORD dwX;	 
   DWORD dwY;      consol application�� ��� console â�� ��ġ�� �����Ѵ�.
                 GUI application�� ������ ��� createWindow �Լ��� CW_USEDEFAUT������ ���� �ȴ�.
				 dwFlags ���ڷ� STARTF_USEPOSION �� ������ ���� ����ȴ�.
                
   DWORD dwXSize;
   DWORD dwYSize;	Console Application�� ������ ��� Console â�� ũ�⸦ �����Ѵ�.
					GUI Application�� ������ ��� CreateWindow() �Լ��� CW_USEDEFAULT������ ���޵ȴ�. 
					dwFlags ���ڷ� STARTF_USESIZE �� ������ ���� ����ȴ�.

   DWORD dwXCountChars;
   DWORD dwYCountChars;	Console Application�� ������ �� ���ο� Console â�� ��ũ�� ������ �ʺ�� ���̸� �����Ѵ�. 
						dwFlags ���ڷ� STARTF_USECOUNTCHARS �� ������ ���� ����ȴ�.

   DWORD dwFillAttribute;	dwFlags, �� ���ڷ� STARTF_USEFILLATTRIBUTE�� ������ ���� ����ȴ�.
							Console Application�� ������ �� ���Ӱ� �����Ǵ� Console â�� ���� ���� ������ �����Ѵ�
							FOREGROUND_BLUE, FOREGROUND_GREEN, FOREGROUND_RED,
							FOREGROUND_INTENSITY, BACKGROUND_BLUE, BACKGROUND_GREEN,
							BACKGROUND_RED, BACKGROUND_INTENSITY
							exaple :
							FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE


   DWORD dwFlags;			STARTUPINFO ����ü�߿��� � �ɹ��� ������ ���� �����Ѵ�.
   WORD wShowWindow;		dwFlags �� ���ڷ� STARTF_USESHOWWINDOW �� ������ ���� ����ȴ�.
							GUI Application ���� ù ��°�� ShowWindow() �� ȣ���� �� 2��° ���ڷ� �����ȴ�. 

   WORD cbReserved2;
   LPBYTE lpReserved2;		C Runtime �� ���� ����Ǿ� �ִ�. �ݵ�� 0�� �����Ѵ�.
   HANDLE hStdInput;
   HANDLE hStdOutput;
   HANDLE hStdError;		���Ӱ� �����Ǵ� ���μ����� ǥ�� �Է�, ���, ���� �ڵ��� �����Ѵ�.
							dwFlags �� ���ڷ� STARTF_USESTDHANDLES �� ������ ���� ����ȴ�.


	*/
	//���� �� exe ���� ���??�̸� ����..
	TCHAR name[] = TEXT("notepad.exe");
	//�����Ǵ� Process�� �⺻ �����忡 ���� ������ ���� �� �ִ� ����ü
	PROCESS_INFORMATION pi;
	
	//�����Ǵ� Process�� ������ ���� �� �ִ� ����ü
	STARTUPINFO			si = { sizeof(si) };
	//process�� �����ϴ� �Լ�
	BOOL b = CreateProcess(0, name, 0, 0,FALSE, NORMAL_PRIORITY_CLASS, 0, 0,&si, &pi);

	//�θ� ��ü���� �ڽ� process�� ��� �����ϴ� �ڵ�
	if (b) 
	{
		//����� ��� �ð� , ������ ���μ����� �ʱ� �Է� ó���� �Ϸ��ϰ� ������� �Է��� ���ų� ���� �ð��� ��� �� ������ ����� �Է��� ��ٸ� ������ �����
		WaitForInputIdle(pi.hProcess, INFINITE);
		//���� �ڵ� ���̺��� �ڽ� process�� Ŀ�� �ڵ��� ������
		CloseHandle(pi.hProcess);
		//���� �ڵ� ���̺��� �ڽ� process�� Thread �ڵ��� ������
		CloseHandle(pi.hThread);
	}

	return TRUE;
}

BOOL OnExitProcess_1(HWND hDlg)
{
	SendMessage(hDlg, WM_CLOSE, 0, 0);
	return 0;
}

BOOL OnExitProcess_2(HANDLE hDlg,HWND hwnd)
{
	//���� ���� �Լ�
	TerminateProcess(hDlg, 0);
	//Ư�� Ŀ�� ������Ʈ�� �ñ׳� �� �� ���� ��� �ϴ� �Լ�
	DWORD ret = WaitForSingleObject(hDlg, 5000);//������ ������ INFINITY�� ���� �ñ׳� ���� �ɶ� ���� ���� ���
	if (ret == WAIT_TIMEOUT)
		MessageBox(hwnd, TEXT("5�� ���"), TEXT("�˸�"), MB_OK);
	else if (ret == WAIT_OBJECT_0) 
	{
		MessageBox(hwnd, TEXT("���α׷�����"), TEXT("�˸�"), MB_OK);
	}
	return 0;
}

BOOL OnGetProcessIDInWidowHandle(HWND hwnd, LPDWORD lpdwProcessID)
{
	DWORD temp= GetWindowThreadProcessId(hwnd, lpdwProcessID);
	return 0;
}

BOOL OnGetWindowHandleInProcessID(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessID)
{
	HANDLE temp = OpenProcess( dwDesiredAccess,  bInheritHandle, dwProcessID);

	return 0;
}

BOOL OnCopyChildHandle(HANDLE hProcess2, PROCESS_INFORMATION pi,  BOOL b)
{
	// ��¥ ���� 
	DuplicateHandle(GetCurrentProcess(),	// �� ���μ�������
		pi.hProcess,	// �� �ڵ���
		GetCurrentProcess(),	// �� ���μ����� �����϶�. 
		&hProcess2,		// hProcess�� �ڵ鰪 ����
		0, FALSE,		// ���� ����, ��� 
		DUPLICATE_SAME_ACCESS);
	if (b) {
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	return 0;
}

