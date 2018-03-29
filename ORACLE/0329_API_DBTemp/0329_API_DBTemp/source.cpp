#include"std.h"

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//초기화 event
	case WM_INITDIALOG:
	{
		OnInitDialog(hDlg);
		return TRUE;
	}
	//메세지 받는 event를 처리하기 위한 영역
	case WM_COMMAND:
	{
		return OnCommand(hDlg,wParam,lParam);
		
	}
	case WN_CANCEL:
	{
		if (wbdb_DBDConnect() == FALSE)
		{
			MessageBox(0, TEXT("끊기 실패"), TEXT(""), 0);
		}
		else
		{
			MessageBox(0, TEXT("끊기 성공"), TEXT(""), 0);
		}
		
		return 0;
	}
	}
	return FALSE;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd)
{
	UINT	ret = DialogBox(hInst,// instance
		MAKEINTRESOURCE(IDD_MAINDLG),	// 다이얼로그 선택 
		0,			// 부모 윈도우
		DlgProc);			// Proc..
	return 0;
}
