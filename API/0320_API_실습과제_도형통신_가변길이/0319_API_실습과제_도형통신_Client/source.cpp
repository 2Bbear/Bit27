#include"std.h"

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//초기화 event
	case WM_INITDIALOG:
	{
		OnInitDialog(hDlg,wParam,lParam);
		return TRUE;
	}
	case WM_LBUTTONDOWN:
	{
		
		return 0;
	}
	//메세지 받는 event를 처리하기 위한 영역
	case WM_COMMAND:
	{
		OnCommand(hDlg, wParam, lParam);
		return TRUE;
	}
	case WM_PAINT:
	{
		return OnPaInt(hDlg, wParam, lParam);
	}

	}
	return FALSE;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd)
{

	//콘솔 출력용
	AllocConsole(); // console 창 생성

	freopen("CONOUT$",   // console 을
		"wt",        // text write 모드로
		stdout);	  // stdout 과 연결..

	UINT	ret = DialogBox(hInst,// instance
		MAKEINTRESOURCE(IDD_DIALOG1),	// 다이얼로그 선택 
		0,			// 부모 윈도우
		DlgProc);			// Proc..
	return 0;
}
