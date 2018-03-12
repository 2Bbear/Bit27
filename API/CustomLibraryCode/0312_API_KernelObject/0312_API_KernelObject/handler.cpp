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
	/* PROCESS_INFORMATION 설명

	hProcess 새로 생성된 프로세스에 대한 핸들
	hThread 새로 생성된 프로세스의에 대한 기본 스레드 핸들
	dwProcessId 프로세스를 식별하는 데 사용할 ID값
	dwThreadId 스레드를 식별하는데 사용할 ID값
	*/

	/*STARTUPINFO

	DWORD cb; 구조체 총 크기
   LPTSTR lpReserved; 예약된 자리라는데 반드시 Null을 주어야 함
   LPTSTR lpDesktop; window station과 desktop객체의 이름을 전달한다
   LPTSTR lpTitle; consol application을 실행 할 경우 새로운 console 창의 caption에 전달할 문자열 
                   GUI application의 경우 NULL을 전달 해야한다.
   DWORD dwX;	 
   DWORD dwY;      consol application의 경우 console 창의 위치를 지정한다.
                 GUI application을 실행할 경우 createWindow 함수의 CW_USEDEFAUT값으로 전달 된다.
				 dwFlags 인자로 STARTF_USEPOSION 를 지정할 때만 적용된다.
                
   DWORD dwXSize;
   DWORD dwYSize;	Console Application을 실행할 경우 Console 창의 크기를 지정한다.
					GUI Application을 실행할 경우 CreateWindow() 함수의 CW_USEDEFAULT값으로 전달된다. 
					dwFlags 인자로 STARTF_USESIZE 를 지정할 때만 적용된다.

   DWORD dwXCountChars;
   DWORD dwYCountChars;	Console Application을 실행할 때 새로운 Console 창의 스크린 버퍼의 너비와 높이를 지정한다. 
						dwFlags 인자로 STARTF_USECOUNTCHARS 를 지정할 때만 적용된다.

   DWORD dwFillAttribute;	dwFlags, 의 인자로 STARTF_USEFILLATTRIBUTE가 지정할 때만 적용된다.
							Console Application을 실행할 때 새롭게 생성되는 Console 창의 글자 색과 배경색을 지정한다
							FOREGROUND_BLUE, FOREGROUND_GREEN, FOREGROUND_RED,
							FOREGROUND_INTENSITY, BACKGROUND_BLUE, BACKGROUND_GREEN,
							BACKGROUND_RED, BACKGROUND_INTENSITY
							exaple :
							FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE


   DWORD dwFlags;			STARTUPINFO 구조체중에서 어떤 맴버를 적용할 지를 지정한다.
   WORD wShowWindow;		dwFlags 의 인자로 STARTF_USESHOWWINDOW 가 지정될 때만 적용된다.
							GUI Application 에서 첫 번째로 ShowWindow() 를 호출할 때 2번째 인자로 지정된다. 

   WORD cbReserved2;
   LPBYTE lpReserved2;		C Runtime 에 의해 예약되어 있다. 반드시 0을 지정한다.
   HANDLE hStdInput;
   HANDLE hStdOutput;
   HANDLE hStdError;		새롭게 생성되는 프로세스의 표준 입력, 출력, 에러 핸들을 지정한다.
							dwFlags 의 인자로 STARTF_USESTDHANDLES 가 지정될 때만 적용된다.


	*/
	//실행 할 exe 파일 경로??이름 정도..
	TCHAR name[] = TEXT("notepad.exe");
	//생성되는 Process와 기본 스레드에 대한 정보를 담을 수 있는 구조체
	PROCESS_INFORMATION pi;
	
	//생성되는 Process의 정보를 담을 수 있는 구조체
	STARTUPINFO			si = { sizeof(si) };
	//process를 생성하는 함수
	BOOL b = CreateProcess(0, name, 0, 0,FALSE, NORMAL_PRIORITY_CLASS, 0, 0,&si, &pi);

	//부모 객체에서 자식 process의 제어를 해제하는 코드
	if (b) 
	{
		//잠깐의 대기 시간 , 지정된 프로세스가 초기 입력 처리를 완료하고 대기중인 입력이 없거나 제한 시간이 경과 할 때까지 사용자 입력을 기다릴 때까지 대기함
		WaitForInputIdle(pi.hProcess, INFINITE);
		//현재 핸들 테이블에서 자식 process의 커널 핸들을 제거함
		CloseHandle(pi.hProcess);
		//현재 핸들 테이블에서 자식 process의 Thread 핸들을 제거함
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
	//강제 종료 함수
	TerminateProcess(hDlg, 0);
	//특정 커널 오브젝트가 시그널 될 때 가지 대기 하는 함수
	DWORD ret = WaitForSingleObject(hDlg, 5000);//마지막 값으로 INFINITY가 있음 시그널 값이 될때 까지 무한 대기
	if (ret == WAIT_TIMEOUT)
		MessageBox(hwnd, TEXT("5초 경과"), TEXT("알림"), MB_OK);
	else if (ret == WAIT_OBJECT_0) 
	{
		MessageBox(hwnd, TEXT("프로그램종료"), TEXT("알림"), MB_OK);
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
	// 진짜 복사 
	DuplicateHandle(GetCurrentProcess(),	// 이 프로세스안의
		pi.hProcess,	// 이 핸들을
		GetCurrentProcess(),	// 이 프로세스에 복사하라. 
		&hProcess2,		// hProcess에 핸들값 저장
		0, FALSE,		// 접근 권한, 상속 
		DUPLICATE_SAME_ACCESS);
	if (b) {
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	return 0;
}

