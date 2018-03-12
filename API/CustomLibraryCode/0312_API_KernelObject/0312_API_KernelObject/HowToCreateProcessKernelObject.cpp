#include <Windows.h>
#include<tchar.h>
//You must have make Resource-Dialog 
#include"resource.h"

#include"handler.h"

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//초기화 event
	case WM_INITDIALOG:
	{
		return TRUE;
	}	
	//메세지 받는 event를 처리하기 위한 영역
	case WM_COMMAND:
	{
		//버튼 입력을 받는 event를 처리하기 위한 영역
		switch (LOWORD(wParam))
		{
		//프로그램 종료 관련 버튼
		case IDC_BUTTON1:
		{
			
			//Process 종료 첫번째 
			//OnExitProcess_1(hDlg);
			//process 종료 두번째
			//OnExitProcess_2(GetCurrentProcess(),hDlg);
			//process 종료 세번째
			
			return 0;
		}

		//OK 버튼
		case IDOK:
		{
			//Process 생성 첫번째 방법
			//OnCreateProcess_1();
			//Process 생성 두번째 방법
			OnCreateProcess_2();
			return 0;
		}
		//Cancel 버튼
		case IDCANCEL:
		{
			EndDialog(hDlg, IDCANCEL);	return 0;
		}
	
		}
		return TRUE;
	}
		
	}
	return FALSE;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd)
{
	UINT	ret = DialogBox(hInst,// instance
		MAKEINTRESOURCE(IDD_DIALOG1),	// 다이얼로그 선택 
		0,			// 부모 윈도우
		DlgProc);			// Proc..
	return 0;
}
