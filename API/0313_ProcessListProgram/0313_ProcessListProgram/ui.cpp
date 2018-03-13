#include"std.h"

HWND g_hListView;

void ui_GetHandle(HWND hDlg)
{
	g_hListView = GetDlgItem(hDlg, IDC_LIST1);
}

void ui_SetListViewColumnHeader(HWND hDlg)
{
	LVCOLUMN COL;
	// 헤더를 추가한다.
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 150;
	COL.pszText = TEXT("이름");				// 첫 번째 헤더
	COL.iSubItem = 0;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = TEXT("PID");			// 두 번째 헤더
	COL.iSubItem = 1;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

}

void ui_processListPrint(vector<PROINFO>* datalist, int size)
{
	//List 초기화
	ListView_DeleteAllItems(g_hListView);
	//하나의 list 아이템 삭제
	//ListView_DeleteItem(hList,idx)
	//정보 추출
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


	LI.iItem = _idx;// 행

	LI.iSubItem = 0;//열
	LI.pszText = _info.name;			// 첫 번째 아이템
	SendMessage(g_hListView, LVM_INSERTITEM, 0, (LPARAM)&LI);

	TCHAR buf[20];
	wsprintf(buf,TEXT("%d"),_info.id);

	LI.iSubItem = 1;
	LI.pszText = buf;
	SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

	//===========================================================
	
}
