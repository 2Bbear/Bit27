#include"std.h"

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//ListControl Init
	ui_GetHandle(hDlg);
	ui_SetListViewColumnHeader(hDlg);
	//=======================================
	//초기 프로세스 리스트를 출력
	GetProcessList(hDlg);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//버튼 입력을 받는 event를 처리하기 위한 영역
	switch (LOWORD(wParam))
	{
	//갱신 출력
	case IDC_BUTTON1:
	{
		OnPrint(hDlg);
		return 0;
	}
	case IDCANCEL:
	{
		OnCancel(hDlg);
		return 0;
	}

	}
	return TRUE;
}

BOOL OnPrint(HWND hDlg)
{
	//리스트 초기화

	GetProcessList(hDlg);
	return 0;
}

void OnCancel(HWND hDlg)
{
	EndDialog(hDlg, IDCANCEL);
}


void GetProcessList(HWND hDlg)
{
	
	vector<PROINFO> datalist;
	int size;
	pro_getProcessList(&datalist, &size);
	//리스트 저장
	coll_proListSave(&datalist, size);

	//화면에 출력
	ui_processListPrint(&datalist, size);
}
