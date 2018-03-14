#include"std.h"


BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//custom message 
	//오른쪽 리스트 출력하기 메세지
	case WM_USER + 100:
	{
		//빡쳐서 여기다 적음
		TCHAR * c = (TCHAR*)wParam;
		Account * acc=B_FindAccount(c);
		setEditControls(acc->accountNum, acc->name, acc->balance);
		return OnRightListControlPrint(hDlg,wParam,lParam);
	}
		//초기화 event
	case WM_INITDIALOG:
	{
		return OnInitDialog(hDlg, wParam, lParam);
	}
	//메세지 받는 event를 처리하기 위한 영역
	case WM_COMMAND:
	{
		return OnCommand(hDlg,wParam, lParam);
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
