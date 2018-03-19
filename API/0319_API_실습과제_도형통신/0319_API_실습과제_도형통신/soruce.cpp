//소스.cpp
#include "std.h"

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		return OnInitDialog(hDlg,wParam,lParam);// OnInitDialog(hDlg);
	}
	case WM_COMMAND:
	{
		return OnCommand(hDlg, wParam, lParam);
		
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

	UINT ret = DialogBox(
		hInst,							// instance 
		MAKEINTRESOURCE(IDD_DIALOG1),	// 다이얼로그 선택 
		0,								// 부모 윈도우 
		DlgProc);						// Proc.. 

	return 0;
}