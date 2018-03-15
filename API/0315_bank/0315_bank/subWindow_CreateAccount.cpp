#include"std.h"

BOOL CALLBACK SW_CreateAccountProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static Account * pTemp = 0;
	switch (msg)
	{
	
		//초기화 event
	case WM_INITDIALOG:
	{
		pTemp = (Account*)lParam;
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

			//저장 =====================================
			//계좌번호
			//GetDlgItemInt(hDlg, IDC_SW_CA_EDIT1, pTemp->accountNum, 0);
			pTemp->accountNum=GetDlgItemInt(hDlg, IDC_SW_CA_EDIT1,0,0);
			//이름
			GetDlgItemText(hDlg, IDC_SW_CA_EDIT2, pTemp->name, _tcslen(pTemp->name));
			//아이디
			GetDlgItemText(hDlg, IDC_SW_CA_EDIT3, pTemp->id, _tcslen(pTemp->id));
			//비밀번호
			GetDlgItemText(hDlg, IDC_SW_CA_EDIT4, pTemp->password, _tcslen(pTemp->password));
			//잔액
			pTemp->balance = 0;

			//=======================================
			EndDialog(hDlg, IDOK);
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
