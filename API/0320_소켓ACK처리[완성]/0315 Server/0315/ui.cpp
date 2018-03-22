//ui.cpp

#include "std.h"

HWND g_hEdit1, g_hList;

void ui_InitControl(HWND hDlg)
{
	g_hEdit1 = GetDlgItem(hDlg, IDC_EDIT2);
	g_hList  = GetDlgItem(hDlg, IDC_LIST1);

	SetDlgItemText(hDlg, IDC_IPADDRESS1, TEXT("192.168.0.22"));
	SetDlgItemInt(hDlg, IDC_EDIT1, 9000, 0);

	//============ ����Ʈ �� ��Ʈ�� �ʱ�ȭ ==================================	
	LVCOLUMN COL;

	// ����� �߰��Ѵ�.
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 100;
	COL.pszText = TEXT("�̸�");				// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = TEXT("���̵�");			// �� ��° ���
	COL.iSubItem = 1;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.cx = 90;
	COL.pszText = TEXT("�н�����");				// �� ��° ���
	COL.iSubItem = 2;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.cx = 100;
	COL.pszText = TEXT("�α���");				// �� ��° ���
	COL.iSubItem = 3;
	SendMessage(g_hList, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);
	//========================================================================
}

int ui_getPort(HWND hDlg)
{
	return GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
}

void ui_LogMessage(TCHAR *msg)
{
	SendMessage(g_hEdit1, EM_REPLACESEL, 0, (LPARAM)msg);
	SendMessage(g_hEdit1, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
}


void ui_AddListData(int idx, MEMBER mem)
{

	LVITEM LI;
	LI.mask = LVIF_TEXT;

	LI.iItem = 0;
	LI.iSubItem = 0;
	LI.pszText = mem.name;		// ù ��° ������
	SendMessage(g_hList, LVM_INSERTITEM, 0, (LPARAM)&LI);

	LI.iSubItem = 1;
	LI.pszText = mem.id;
	SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

	LI.iSubItem = 2;
	LI.pszText = mem.pw;
	SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);

	TCHAR buf[20];
	wsprintf(buf, TEXT("%s"), mem.islogin ? TEXT("�α���") : TEXT("�α׾ƿ�"));
	LI.iSubItem = 3;
	LI.pszText = buf;			// �� ��° ������
	SendMessage(g_hList, LVM_SETITEM, 0, (LPARAM)&LI);
}

void ui_MemberPrintALL(vector<MEMBER> *memlist)
{
	ListView_DeleteAllItems(g_hList);
	for (int i = 0; i < (int)memlist->size(); i++)
	{
		ui_AddListData(i, (*memlist)[i]);
	}
}