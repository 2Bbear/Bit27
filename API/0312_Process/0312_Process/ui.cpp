#include"std.h"

HWND g_hCombo;
void ui_GetHandle(HWND hDlg)
{
	g_hCombo = GetDlgItem(hDlg, IDC_COMBO1);
}

void ui_GetProcessName( TCHAR * buf)
{
	GetWindowText(g_hCombo, buf, 50);
}

void ui_SetComboBoxAddProcessName(TCHAR * buf)
{
	SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)buf);
}

int ui_ComboBoxSelChange(HWND hDlg)
{
	//���� ��� ���õǾ� �ִ��� Ȯ��
	int idx = SendMessage(g_hCombo, CB_GETCURSEL, 0, 0);
	return idx;
	

	
}

void ui_ProInfoPrint(HWND hDlg, PROINFO * p)
{
	//�̸� ���
	SetDlgItemText(hDlg, IDC_EDIT1, (LPCWSTR)(p->name));//��ȭâ ������ �ʱ�ȭ �ϴ� �Լ�
	

	//ID ���
	SetDlgItemInt(hDlg, IDC_EDIT2, (p->id),0);//��ȭâ ������ �ʱ�ȭ �ϴ� �Լ�
	//�ڵ� ���
	SetDlgItemInt(hDlg, IDC_EDIT3,(UINT) p->handle,0);//��ȭâ ������ �ʱ�ȭ �ϴ� �Լ�
}

HANDLE ui_GetProcessHandle(HWND hDlg)
{
	return (HANDLE)GetDlgItemInt(hDlg, IDC_EDIT3, 0, 0);
	
}

void ui_ExitCodePrint(HWND hDlg, int  code)
{
	TCHAR buf[256];
	if (code == STILL_ACTIVE)
	{
		wsprintf(buf, TEXT("����ִ�.[code : %d]"), code);
	}
	else
	{
		wsprintf(buf, TEXT("�׾���..[code : %d]"), code);
	
	}
	SetDlgItemText(hDlg, IDC_EDIT4,buf);
}

void ui_FindName(HWND hDlg, TCHAR *name)
{
	
	OPENFILENAME OFN;
	TCHAR str[300];
	TCHAR lpstrFile[MAX_PATH] = TEXT("");
	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hDlg;
	OFN.lpstrFilter = TEXT("���� ����(*.exe)\0*.exe\0 ��� ����(*.*)\0*.*\0");
	OFN.lpstrFile = name;
	OFN.nMaxFile = MAX_PATH;
	if (GetOpenFileName(&OFN) != 0) {

		
	/*	wsprintf(str, TEXT("%s ������ �����߽��ϴ�."), name);
		MessageBox(hDlg, str, TEXT("���� ���� ����"), MB_OK);*/
	}
}

void ui_ComboBoxPrint(HWND hDlg, TCHAR * name)
{
	SetWindowText(g_hCombo, name);
}
