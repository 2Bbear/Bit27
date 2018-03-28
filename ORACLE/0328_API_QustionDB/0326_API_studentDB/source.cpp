#include"std.h"

//vector<PROINFO*>g_pList;

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	AllocConsole(); // console 창 생성
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "wt", stdout);
	

	switch (msg)
	{
		//초기화 event
	case WM_INITDIALOG:
	{
		return OnInitDialog(hDlg, wParam, lParam);
	}
	//메세지 받는 event를 처리하기 위한 영역
	case WM_COMMAND:
	{
		return OnCommand(hDlg, wParam, lParam);
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
