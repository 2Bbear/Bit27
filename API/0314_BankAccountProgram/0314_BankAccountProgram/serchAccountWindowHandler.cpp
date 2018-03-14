#include"std.h"

HWND parentsHandle;
HINSTANCE g_hInst2;
TCHAR * localTempID;
BOOL CALLBACK DlgProc3(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
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
		switch (LOWORD(wParam))
		{
			//확인 버튼을 눌렀을 때
		case IDOK:
		{
			TCHAR temp[50];
			//id 가져오기
			GetDlgItemText(hDlg, IDC_EDIT111, temp, _tcslen(temp));
			//id 값으로 Account가져오기
			Account * pAcc = B_FindAccount(temp);
			//밖의 temp 메모리로 id값 내보내기
			_tcscpy(localTempID,pAcc->id);
			//부모에게 오른쪽 리스트를 출력하라고 메세지 보냄
			SendMessage(parentsHandle, WM_USER + 100, (WPARAM)pAcc->id, 0);
			return 0;
		}
		case IDCANCEL:
		{
			EndDialog(hDlg, IDCANCEL);
			return 0;
		}
		}

		return 0;
	}

	}
	return FALSE;

}
void SAWH_CreateDialogWindow(TCHAR * _tempID,HWND hwnd)
{
	parentsHandle = hwnd;
	localTempID = _tempID;
	g_hInst2 = GetModuleHandle(0);
	//이 코드 자체가 새로운 창을 띄우게 함
	UINT ret = DialogBox(g_hInst2,// instance 
		MAKEINTRESOURCE(IDD_DIALOG3), // 다이얼로그 선택 
		0,   // 부모 윈도우 
		DlgProc3);   // Proc..
}
