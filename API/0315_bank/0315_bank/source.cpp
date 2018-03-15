
//You must have make Resource-Dialog 

#include"std.h"

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//초기화 event
	case WM_INITDIALOG:
	{

		return OnInitDialog(hDlg);
	}
	//자식에게서 받은 AccountDetail 출력 메세지 wParam , lParam 양쪽에 id값이 있으니 골라서 가져 가면 됨 이 값은 TCHAR *임
	case MY_ACCOUNTDETAILPRINT:
	{
		
		return OnAccountDetailPrint(hDlg, wParam, lParam);
	}
	
	//메세지 받는 event를 처리하기 위한 영역
	case WM_COMMAND:
	{
	
		//버튼 입력을 받는 event를 처리하기 위한 영역
		switch (LOWORD(wParam))
		{
			//리스트 컨트롤 선택 메세지
		case LVM_GETSELECTIONMARK:
		{
			MessageBox(hDlg, TEXT(""), TEXT(""), 0);
			return 0;
		}
		
		//상단메뉴
			//프로그램 종료
		case ID_40001:
		{
			return 0;
		}
		//계좌생성
		case ID_40002:
		{
			return OnCreateAccountWindow( hDlg,  wParam,  lParam);
		}
		//계좌 검색
		case ID_40003:
		{
			return OnSearchAccountWindow(hDlg,wParam,lParam);
		}
		//버튼메뉴
			//삭제 버튼
		case IDC_DELETEACCBUTTON:
		{
			return OnDeleteAccountButton(hDlg);
		}
			//입출금 버튼
		case IDC_BUTTON2:
		{

			return OnBankStatement(hDlg);
		}
		//라디오버튼
			//입금 버튼
		case IDC_RADIO1:
		{
			
			return OnDeposit();
		}
			//출금 버튼
		case IDC_RADIO2:
		{
			return OnWithdraw();
		}
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
