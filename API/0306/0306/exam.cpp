//exam.pp

#include <windows.h>
#include <tchar.h>

#include"exam.h"
#include"Custom_IPC_Protocol.h"

void exma1()
{
	HWND hwnd = FindWindow(0, _TEXT("����"));
	if (hwnd == 0)	{
		MessageBox(0, _TEXT("���� �ڵ��� ���� �� �����ϴ�."),_TEXT("�˸�"), MB_OK | MB_ICONERROR);
	}
	else	{
		TCHAR temp[20];
		wsprintf(temp, _TEXT("���� �ڵ� : %d"), hwnd);
		MessageBox(0, temp, _TEXT("�˸�"), MB_OK);
	}
}

void exam2()
{
	HWND hwnd = FindWindow(0, _TEXT("����"));
	if (hwnd == 0)	{
		MessageBox(0, _TEXT("���� �ڵ��� ���� �� �����ϴ�."), _TEXT("�˸�"), MB_OK | MB_ICONERROR);
	}
	else	{
		ShowWindow(hwnd, SW_HIDE);
	}
	
}

void exam10( WPARAM wParam)
{
	//Ÿ�� �ڵ� �� ã��
	HWND hwnd = FindWindow(0, _TEXT("Hello2"));
	//Ÿ�ٿ� �޼��� ����
	if (hwnd == 0)	{
		MessageBox(0, _TEXT("Ÿ�� �ڵ��� ���� �� �����ϴ�."), _TEXT("�˸�"), MB_OK | MB_ICONERROR);
	}
	else	{
		SendMessage(hwnd, WM_PRINT_WPARAM, 10002, 20);
	}


}