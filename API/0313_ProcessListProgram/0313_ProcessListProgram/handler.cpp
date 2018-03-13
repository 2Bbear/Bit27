#include"std.h"

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//ListControl Init
	ui_GetHandle(hDlg);
	ui_SetListViewColumnHeader(hDlg);
	//=======================================
	//�ʱ� ���μ��� ����Ʈ�� ���
	GetProcessList(hDlg);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//��ư �Է��� �޴� event�� ó���ϱ� ���� ����
	switch (LOWORD(wParam))
	{
	//���� ���
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
	//����Ʈ �ʱ�ȭ

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
	//����Ʈ ����
	coll_proListSave(&datalist, size);

	//ȭ�鿡 ���
	ui_processListPrint(&datalist, size);
}
