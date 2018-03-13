#include"std.h"

HWND g_hListView;

void ui_GetHandle(HWND hDlg)
{
	g_hListView = GetDlgItem(hDlg, IDC_LIST1);
}

void ui_SetListViewColumnHeader(HWND hDlg)
{
	LVCOLUMN COL;
	// ����� �߰��Ѵ�.
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 150;
	COL.pszText = TEXT("�̸�");				// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = TEXT("PID");			// �� ��° ���
	COL.iSubItem = 1;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

}

void ui_processListPrint(vector<PROINFO>* datalist, int size)
{
	//List �ʱ�ȭ
	ListView_DeleteAllItems(g_hListView);
	//�ϳ��� list ������ ����
	//ListView_DeleteItem(hList,idx)
	//���� ����
	for (int i =0;i<size;i++)
	{
		PROINFO info = (*datalist)[i];
		//
		//======================================
		ListPrint(info, i);
		//======================================
	}
}

void ListPrint(PROINFO _info, int _idx)
{
	LVITEM LI;

	LI.mask = LVIF_TEXT;


	LI.iItem = _idx;// ��

	LI.iSubItem = 0;//��
	LI.pszText = _info.name;			// ù ��° ������
	SendMessage(g_hListView, LVM_INSERTITEM, 0, (LPARAM)&LI);

	TCHAR buf[20];
	wsprintf(buf,TEXT("%d"),_info.id);

	LI.iSubItem = 1;
	LI.pszText = buf;
	SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

	//===========================================================
	
}
