//modal_ui.cpp

#include "std.h"

HWND g_hList;

void modal_ui_InitPrint(HWND hDlg, LOGIN* info)
{
	TCHAR pw[20];
	GetDlgItemText(GetParent(hDlg), IDC_EDIT6, pw, 20);
	SetDlgItemText(hDlg, IDC_NAME, info->pw);
	SetDlgItemText(hDlg, IDC_ID, info->id);
	SetDlgItemText(hDlg, IDC_PW, pw);

	g_hList = GetDlgItem(hDlg, IDC_LIST2);

	//============ 리스트 뷰 컨트롤 초기화 ==================================   
	LVCOLUMN COL;

	// 헤더를 추가한다. #include <commctrl.h>
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 100;
	COL.pszText = TEXT("회원ID");            // 첫 번째 헤더
	COL.iSubItem = 0;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = TEXT("계좌번호");         // 두 번째 헤더
	COL.iSubItem = 1;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.cx = 90;
	COL.pszText = TEXT("잔   액");            // 세 번째 헤더
	COL.iSubItem = 2;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.cx = 100;
	COL.pszText = TEXT("계좌 개설일");            // 세 번째 헤더
	COL.iSubItem = 3;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);
	//========================================================================
}

void modal_ui_DataPrint(HWND hDlg)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	TCHAR buf[50];

	GetDateFormat(LOCALE_USER_DEFAULT, 0, &st, TEXT("yyyy-M-d"), buf, 50);
	SetDlgItemText(hDlg, IDC_DATE, buf);
}

void modal_ui_GetAccount(HWND hDlg,TCHAR* id, int* accnum, int* balance, TCHAR* date)
{
	*accnum = GetDlgItemInt(hDlg, IDC_ACCNUM, 0, 0);
	*balance = GetDlgItemInt(hDlg, IDC_BAL, 0, 0);
	GetDlgItemText(hDlg, IDC_ID, id, 20);
	GetDlgItemText(hDlg, IDC_DATE, date, 50);
}

void modal_ui_ListPrint(int idx, ADDACCOUNT acc)
{
	TCHAR buf[20];

	LVITEM LI;
	LI.mask = LVIF_TEXT;

	LI.iItem = idx;
	LI.iSubItem = 0;
	LI.pszText = acc.id;      // 첫 번째 아이템
	SendMessage(g_hList, LVM_INSERTITEM, 0, (LPARAM)&LI);

	wsprintf(buf, TEXT("%d"), acc.accnum);
	LI.iSubItem = 1;
	LI.pszText = buf;
	SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

	wsprintf(buf, TEXT("%d"), acc.balance);
	LI.iSubItem = 2;
	LI.pszText = buf;
	SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

	LI.iSubItem = 3;
	LI.pszText = acc.date;         // 두 번째 아이템
	SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);
}

void modal_ui_ListPrintALL(vector<ADDACCOUNT> *acclist)
{
	ListView_DeleteAllItems(g_hList);
	for (int i = 0; i < (int)acclist->size(); i++)
	{
		modal_ui_ListPrint(i, (*acclist)[i]);
	}
}


void modal_ui_GetAddMoney(HWND hDlg, int* accnum, int* money)
{
	*accnum = GetDlgItemInt(hDlg, IDC_ACCNUM, 0, 0);
	*money = GetDlgItemInt(hDlg, IDC_BAL, 0, 0);
}

void modal_ui_GetSubMoney(HWND hDlg, int* accnum, int* money)
{
	*accnum = GetDlgItemInt(hDlg, IDC_ACCNUM, 0, 0);
	*money = GetDlgItemInt(hDlg, IDC_BAL, 0, 0);
}