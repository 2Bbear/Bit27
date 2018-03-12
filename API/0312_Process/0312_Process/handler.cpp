#include"std.h"


extern vector< PROINFO* >g_prolist;

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	//���μ�������-Ȯ��
	case IDOK:
	{
		OnCheck(hDlg);
		return TRUE;
	}
	//Check ��ư
	case IDC_BUTTON2:
	{
		OnGetExitCode(hDlg);
		return TRUE;
	}
	//���� ��ư
	case IDC_BUTTON3:
	{
	
		OnExitProcess(hDlg);
		return TRUE;
	}
	//ã�ƺ��� ��ư
	case IDC_BUTTON1:
	{
		OnFindName(hDlg);
		return TRUE;
	}
	case IDC_COMBO1:
	{
		if (HIWORD(wParam)==CBN_SELCHANGE)
		{
			OnComboBoxSelChange(hDlg);
		}
		return TRUE;
	}
	case IDCANCEL:
	{
		EndDialog(hDlg, IDCANCEL);	return 0;
	}

	}
	return true;
	
}
BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	ui_GetHandle(hDlg); 
	return TRUE;
}
BOOL OnExitProcess(HWND hDlg)
{
	HANDLE h = ui_GetProcessHandle(hDlg);
	proc_ExitProcess(h);
	int code = proc_GetExitCodeProcess(h);
	ui_ExitCodePrint(hDlg, code);

	return 0;
}
BOOL OnFindName(HWND hDlg)
{
	TCHAR name[256] = {'\0'};
	ui_FindName(hDlg,name);
	ui_SetComboBoxAddProcessName(name);
	ui_ComboBoxPrint(hDlg,name);
	return 0;
}
BOOL OnComboBoxSelChange(HWND hDlg)
{
	int idx= ui_ComboBoxSelChange(hDlg);
	//�ش� ��ġ�� �ִ� ���� ���� ��������
	PROINFO* p = g_prolist[idx];
	//static control�� ��� �� �� �ֵ��� �޼��� ����
	ui_ProInfoPrint(hDlg,p);

	return 0;
}
BOOL OnGetExitCode(HWND hDlg)
{
	HANDLE h=ui_GetProcessHandle(hDlg);
	int code = proc_GetExitCodeProcess(h);
	ui_ExitCodePrint(hDlg,code);
	
	return 0;
}
void OnCheck(HWND hDlg)
{
	//�ش� ��ġ�� �ִ� ���� ���� ��������
	TCHAR buf[50];
	//�ؽ�Ʈ ��������
	ui_GetProcessName(buf);
	//�ؽ�Ʈ �޺� �ڽ��� �����ϱ�
	ui_SetComboBoxAddProcessName(buf);
	//�ؽ�Ʈ�� �´� ���μ��� ����
	proc_CreateProcess(buf);
	//���μ����� ���� ��������
	//���μ����� ���� �����ϱ�
	PROINFO *pInfo = proc_CreateProcess(buf);
	g_prolist.push_back(pInfo);

	ui_ProInfoPrint(hDlg, g_prolist[g_prolist.size() - 1]);
	

	//MessageBox(NULL,buf,TEXT(""),MB_OK);
	
	//���� ��� ���õǾ� �ִ��� Ȯ��
	//int idx = SendMessage(g_hComboBox1, CB_GETCURSEL, 0, 0);
	//
	//SendMessage(g_hComboBox1, CB_GETLBTEXT, idx, LPARAM(buf));
	////static control�� �޼��� ������
	//SetWindowText(g_hStatic2, (LPCWSTR)buf);//��ȭâ ������ �ʱ�ȭ �ϴ� �Լ�
}
