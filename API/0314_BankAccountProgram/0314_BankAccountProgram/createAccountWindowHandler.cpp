#include"std.h"

HINSTANCE g_hInst;

//전역리스트의  포인터
vector<Account> * pAcc;

BOOL CALLBACK DlgProc2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
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
		
			//저장 =====================================
			Account temp;
			//이름
			GetDlgItemText(hDlg, IDC_EDIT11, temp.name, _tcslen(temp.name));
			//패스워드
			GetDlgItemText(hDlg, IDC_EDIT22, temp.password, _tcslen(temp.password));
			//계좌번호
			temp.accountNum=GetDlgItemInt(hDlg, IDC_EDIT33,0,0);
			//아이디
			GetDlgItemText(hDlg, IDC_EDIT55, temp.id, _tcslen(temp.id));
			//잔액
			_tcscpy(temp.balance,TEXT("0원"));
			//전역 리스트에 저장
			pAcc->push_back(temp);

			//
			//윈도우 창 종료
			EndDialog(hDlg, IDCANCEL);
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

void CAWH_CreateDialogWindow(vector<Account> * _pAcc, HWND hDlg)
{
	pAcc = _pAcc;
	g_hInst = GetModuleHandle(0);
	////이 코드 자체가 새로운 창을 띄우게 함
	//UINT ret = DialogBox(g_hInst,// instance 
	//	MAKEINTRESOURCE(IDD_DIALOG2), // 다이얼로그 선택 
	//	0,   // 부모 윈도우 
	//	DlgProc2);   // Proc..
	UINT ret = DialogBoxParam(g_hInst,// hinstance
		MAKEINTRESOURCE(IDD_DIALOG2),
		hDlg,		// 부모
		DlgProc2, // 메세지 함수.
		(LPARAM)11); // WM_INITDIALOG의 lParam로 전달된다. //이 함수가 끝날 때까지 메인 윈도우는 아무것도 못한다



}
