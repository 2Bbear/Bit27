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

	//��ư �Է��� �޴� event�� ó���ϱ� ���� ����
	switch (LOWORD(wParam))
	{
	//��ܸ޴�-���α׷� ����
	case ID_40002:
	{
		return 0;
	}
	//��ܸ޴�-���°˻�
	case ID_40005:
	{
		//������ ����
		ui_PopUpSerchAccountWindow(hDlg);
		
		return 0;
	}
	//��ܸ޴�-���»���
	case ID_40004:
	{
		//������ ����
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
	//������ ListControl ���
	ui_processAccountDetailListPrint(&g_AccountDetailList, g_AccountDetailList.size());
	
	return 0;
}
