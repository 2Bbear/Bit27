#include"std.h"
extern HWND mainhwnd;

//static TCHAR temp[50];
BOOL CALLBACK SW_SearchAccountProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
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
			//id가져오기
			GetDlgItemText(hDlg, IDC_SW_SA_EDIT1, temp, _tcslen(temp));
			
			//부모에게 메세지 보내기
			SendMessage(mainhwnd, MY_ACCOUNTDETAILPRINT, (WPARAM)temp, (LPARAM)temp);
		
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