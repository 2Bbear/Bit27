//modal.cpp

#include "std.h"

static LOGIN *pinfo;
static HWND g_hModalDlg;

// ��� ���ν��� ============================================================================
BOOL CALLBACK Acc_DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg)
	{
	case WM_INITDIALOG:	Acc_InitDialog(hDlg, lParam);		break;
	case WM_COMMAND:	Acc_Command(hDlg, wParam, lParam);	break;
	}
	return FALSE;
}


//=========================================================================================
void Acc_InitDialog(HWND hDlg, LPARAM lParam)
{
	g_hModalDlg = hDlg;
	// �θ�� �����ϴ� ����ü
	pinfo = (LOGIN*)lParam;

	// �ڽ��� ���� �� ����Ʈ�� �ʱ�ȭ	
	modal_ui_InitPrint(hDlg, pinfo);
	// ���� ��¥ ����
	modal_ui_DataPrint(hDlg);
	// �ش� ID�� ������ ����list�ҷ�����
	modal_ui_ListPrintALL(wbcon_GetAccountList());
}

BOOL Acc_Command(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_ACCCREATE:	Acc_Create(hDlg);		return TRUE;
	case IDC_ACCDELETE: Acc_Delete(hDlg);		return TRUE;
	case IDC_ADDMONEY:	Acc_AddMoney(hDlg);		return TRUE;	
	case IDC_MINMONEY:	Acc_SubMoney(hDlg);		return TRUE;
	case IDCANCEL:
		EndDialog(hDlg, IDCANCEL);
		return TRUE;
	}

	return TRUE;
}

void Acc_Create(HWND hDlg)
{
	TCHAR id[20];
	int accnum;
	int balance;
	TCHAR date[50];
	modal_ui_GetAccount(hDlg,id, &accnum, &balance,date);
	ADDACCOUNT packet = pack_SetAddAccount(id,accnum, balance, date);
	wbnet_SendMessage((TCHAR*)&packet, sizeof(ADDACCOUNT));
}

void Acc_Delete(HWND hDlg)
{
	TCHAR id[20];
	int accnum;
	int balance;
	TCHAR date[50];
	modal_ui_GetAccount(hDlg, id, &accnum, &balance, date);
	ADDACCOUNT packet = pack_SetDelAccount(id, accnum, balance, date);
	wbnet_SendMessage((TCHAR*)&packet, sizeof(ADDACCOUNT));
}

void Acc_AddMoney(HWND hDlg)
{
	int accnum;
	int money;

	modal_ui_GetAddMoney(hDlg, &accnum, &money);
	ADDMONEY packet = pack_SetAddMoney(accnum, money);
	wbnet_SendMessage((TCHAR*)&packet, sizeof(ADDMONEY));
}

void Acc_SubMoney(HWND hDlg)
{
	int accnum;
	int money;
	
	modal_ui_GetSubMoney(hDlg, &accnum, &money);
	SUBMONEY packet = pack_SetSubMoney(accnum, money);
	wbnet_SendMessage((TCHAR*)&packet, sizeof(SUBMONEY));
}


//���� OnMessage==============================================================
void Acc_OnAddcount_s(char* buf)
{
	ADDACCOUNT *p = (ADDACCOUNT*)buf;
	con_InsertAccount(*p);
	modal_ui_ListPrintALL(wbcon_GetAccountList());
}
void Acc_OnAddcount_f()
{
	ui_LogMessage(TEXT("ȸ������ ����"));
	MessageBox(g_hModalDlg, TEXT("ȸ������ ����"), TEXT(""), MB_OK);
}


void Acc_OnDelcount_s(char* buf)
{
	ADDACCOUNT *p = (ADDACCOUNT*)buf;
	con_DeleteAccount(*p);
	modal_ui_ListPrintALL(wbcon_GetAccountList());

}
void Acc_OnDelcount_f()
{
	ui_LogMessage(TEXT("���»��� ����"));
	MessageBox(g_hModalDlg, TEXT("���»��� ����"), TEXT(""), MB_OK);
}

void Acc_OnAddMoney(char* buf)
{
	ADDMONEY *p = (ADDMONEY*)buf;

	con_AddMoney(p);
	modal_ui_ListPrintALL(wbcon_GetAccountList());

}

void Acc_OnSubMoney_s(char* buf)
{
	SUBMONEY *p = (SUBMONEY*)buf;
	con_SubMoney(p);
	modal_ui_ListPrintALL(wbcon_GetAccountList());
}

void Acc_OnSubMoney_f()
{
	ui_LogMessage(TEXT("��� ���� : �ܾ� ����"));
	MessageBox(g_hModalDlg, TEXT("��� ���� : �ܾ� ����"), TEXT(""), MB_OK);
}





