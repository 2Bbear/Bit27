#include"std.h"
HWND g_hRadio1;
HWND g_hComboBox1;
HWND g_hStatic1;
HWND g_hStatic2;

void ui_GetControlHandle(HWND hDlg)
{
	//�ڽ��� �ڵ鰪�� ������ �Լ�
	//radio 
	g_hRadio1= GetDlgItem(hDlg, IDC_RADIO1);
	SendMessage(g_hRadio1, BM_SETCHECK, true, 0);

	//combo
	g_hComboBox1 = GetDlgItem(hDlg, IDC_COMBO1);
	//combo�ڽ��� ���� �߰��ϱ�
	SendMessage(g_hComboBox1, CB_ADDSTRING, 0, (LPARAM)TEXT("R"));
	SendMessage(g_hComboBox1, CB_ADDSTRING, 0, (LPARAM)TEXT("G"));
	SendMessage(g_hComboBox1, CB_ADDSTRING, 0, (LPARAM)TEXT("B"));
	SendMessage(g_hComboBox1, WM_SETCURSOR,0,0);
	
	//static 1
	g_hStatic1= GetDlgItem(hDlg, IDC_STATIC1);
	//static 2
	g_hStatic2 = GetDlgItem(hDlg, IDC_STATIC2);




}

void ui_TypeSelectButton(HWND hDlg)
{
	 TCHAR str[30];
	
	if (SendMessage(g_hRadio1, BM_GETCHECK, 0, 0) == BST_CHECKED)
	{
		wsprintf(str, TEXT("%s"),TEXT("�簢��"));
	}
	else
	{
		wsprintf(str, TEXT("%s"),TEXT("Ÿ��"));
	}
	SetDlgItemText(hDlg, IDC_STATIC1, str);
	
}

void ui_ColorSelectComboBox(HWND hDlg)
{
	//���� ��� ���õǾ� �ִ��� Ȯ��
	int idx = SendMessage(g_hComboBox1, CB_GETCURSEL, 0, 0);
	//�ش� ��ġ�� �ִ� ���� ���� ��������
	TCHAR buf[40];
	SendMessage(g_hComboBox1, CB_GETLBTEXT, idx, LPARAM(buf));
	//static control�� �޼��� ������
	SetWindowText(g_hStatic2, (LPCWSTR)buf);//��ȭâ ������ �ʱ�ȭ �ϴ� �Լ�
	
}
