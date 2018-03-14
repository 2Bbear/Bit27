#include"std.h"

extern vector<Account> g_AccountList;
extern vector<AccountDetail> g_AccountDetailList;
BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//ListControl Init
	ui_GetHandle(hDlg);
	ui_SetListViewColumnHeader(hDlg);
	//=======================================
	
	return TRUE;
	return 0;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{

	//버튼 입력을 받는 event를 처리하기 위한 영역
	switch (LOWORD(wParam))
	{
	//상단메뉴-프로그램 종료
	case ID_40002:
	{
		return 0;
	}
	//상단메뉴-계좌검색
	case ID_40005:
	{
		//윈도우 띄우기
		ui_PopUpSerchAccountWindow(hDlg);
		
		return 0;
	}
	//상단메뉴-계좌생성
	case ID_40004:
	{
		//윈도우 띄우기
		ui_PopUpCreateAccountWindow(hDlg);
		
		return 0;
	}

	case IDCANCEL:
	{
		EndDialog(hDlg, IDCANCEL);	
		return 0;
	}

	}
	return TRUE;
}

BOOL OnRightListControlPrint(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//오른쪽 ListControl 출력
	ui_processAccountDetailListPrint(&g_AccountDetailList, g_AccountDetailList.size());
	
	return 0;
}
