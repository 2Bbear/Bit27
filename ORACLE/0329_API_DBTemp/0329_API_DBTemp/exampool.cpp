#include"std.h"

static HWND g_hComobo;

void OnInitExamPool(HWND hDlg)
{
	//�޺� �ڽ� �ʱ�ȭ
	g_hComobo=GetDlgItem(hDlg, IDC_EXAMPOOL_COMBOBOX1);
	SendMessage(g_hComobo, CB_ADDSTRING, 0, (LPARAM)TEXT("1"));
	SendMessage(g_hComobo, CB_ADDSTRING, 0, (LPARAM)TEXT("2"));
	SendMessage(g_hComobo, CB_ADDSTRING, 0, (LPARAM)TEXT("3"));
	SendMessage(g_hComobo, CB_ADDSTRING, 0, (LPARAM)TEXT("4"));

	SendMessage(g_hComobo, CB_SETCURSEL, 0, 0);

	//����

}

void OnInsertExamPool(HWND hDlg)
{
	//���� ����
	TCHAR str1[500];
	TCHAR str2[100];
	TCHAR str3[100];
	TCHAR str4[100];
	TCHAR str5[100];
	int number;
	//Edit���� �� �ڷ� ��������
	GetDlgItemText(hDlg, IDC_EXAMPOOL_EDIT1,str1,sizeof(str1)); //����
	GetDlgItemText(hDlg, IDC_EXAMPOOL_EDIT2, str2, sizeof(str2));//1��
	GetDlgItemText(hDlg, IDC_EXAMPOOL_EDIT3, str3, sizeof(str3));//2��
	GetDlgItemText(hDlg, IDC_EXAMPOOL_EDIT4, str4, sizeof(str4));//3��
	GetDlgItemText(hDlg, IDC_EXAMPOOL_EDIT5, str5, sizeof(str5));//4��
	number = GetDlgItemInt(hDlg, IDC_EXAMPOOL_COMBOBOX1, 0, 0);//��¥��

	//���� DB ���� �׽�Ʈ
	if (wbdb_CreateExam(str1, str2, str3, str4, str5, number))
	{
		EndDialog(hDlg, 0);
	}
	else
	{

	}

}
//��ȭ ���� ���ν���
BOOL CALLBACK exampoolDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
		// Dialog�� ó�� ��Ÿ���� �߻�. �� ��Ʈ���� �ʱ�ȭ �Ѵ�.
	case WM_INITDIALOG: 
	{
		OnInitExamPool(hDlg);
		return TRUE;
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case IDC_EXAMPOOL_BUTTON1:
		{
			OnInsertExamPool(hDlg);
			return 0;
		}
		case IDOK:
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
	}
	return FALSE; // �޼��� ó���� ���Ѱ��..
}

