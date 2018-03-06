//exam.pp

#include <windows.h>
#include <tchar.h>

#include"exam.h"
#include"Custom_IPC_Protocol.h"

void exma1()
{
	HWND hwnd = FindWindow(0, _TEXT("계산기"));
	if (hwnd == 0)	{
		MessageBox(0, _TEXT("계산기 핸들을 얻을 수 없습니다."),_TEXT("알림"), MB_OK | MB_ICONERROR);
	}
	else	{
		TCHAR temp[20];
		wsprintf(temp, _TEXT("계산기 핸들 : %d"), hwnd);
		MessageBox(0, temp, _TEXT("알림"), MB_OK);
	}
}

void exam2()
{
	HWND hwnd = FindWindow(0, _TEXT("계산기"));
	if (hwnd == 0)	{
		MessageBox(0, _TEXT("계산기 핸들을 얻을 수 없습니다."), _TEXT("알림"), MB_OK | MB_ICONERROR);
	}
	else	{
		ShowWindow(hwnd, SW_HIDE);
	}
	
}

void exam10( WPARAM wParam)
{
	//타겟 핸들 값 찾기
	HWND hwnd = FindWindow(0, _TEXT("Hello2"));
	//타겟에 메세지 전송
	if (hwnd == 0)	{
		MessageBox(0, _TEXT("타겟 핸들을 얻을 수 없습니다."), _TEXT("알림"), MB_OK | MB_ICONERROR);
	}
	else	{
		SendMessage(hwnd, WM_PRINT_WPARAM, 10002, 20);
	}


}