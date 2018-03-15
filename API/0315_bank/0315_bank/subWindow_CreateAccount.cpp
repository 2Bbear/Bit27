#include"std.h"

BOOL CALLBACK SW_CreateAccountProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static Account * pTemp = 0;
	switch (msg)
	{
	
		//�ʱ�ȭ event
	case WM_INITDIALOG:
	{
		pTemp = (Account*)lParam;
		return TRUE;
	}
	//�޼��� �޴� event�� ó���ϱ� ���� ����
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			//Ȯ�� ��ư�� ������ ��
		case IDOK:
		{

			//���� =====================================
			//���¹�ȣ
			//GetDlgItemInt(hDlg, IDC_SW_CA_EDIT1, pTemp->accountNum, 0);
			pTemp->accountNum=GetDlgItemInt(hDlg, IDC_SW_CA_EDIT1,0,0);
			//�̸�
			GetDlgItemText(hDlg, IDC_SW_CA_EDIT2, pTemp->name, _tcslen(pTemp->name));
			//���̵�
			GetDlgItemText(hDlg, IDC_SW_CA_EDIT3, pTemp->id, _tcslen(pTemp->id));
			//��й�ȣ
			GetDlgItemText(hDlg, IDC_SW_CA_EDIT4, pTemp->password, _tcslen(pTemp->password));
			//�ܾ�
			pTemp->balance = 0;

			//=======================================
			EndDialog(hDlg, IDOK);
			return 0;
		}
		case IDCANCEL:
		{
			EndDialog(hDlg, IDCANCEL);
			return 0;
		}
		}

		return 0;
	}

	}
	return FALSE;
}
