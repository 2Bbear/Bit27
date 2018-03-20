#include"std.h"
//Dlg handle


BOOL CALLBACK ModalProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	

	switch (msg)
	{
		//�ʱ�ȭ event
	case WM_INITDIALOG:
	{
		
		return TRUE;
	}
	//�޼��� �޴� event�� ó���ϱ� ���� ����
	case WM_COMMAND:
	{
		//��ư �Է��� �޴� event�� ó���ϱ� ���� ����
		switch (LOWORD(wParam))
		{
			//�簢�� ��ư
		case IDC_BUTTON_MODAL_RECT:
		{
			printf("�簢�� ��ư \n");
			RECTPRINT data;
			data.flag = 1;
			data.x = GetDlgItemInt(hDlg, IDC_EDIT_MODAL_X, 0, 0);
			data.y= GetDlgItemInt(hDlg, IDC_EDIT_MODAL_Y, 0, 0);
			data.width= GetDlgItemInt(hDlg, IDC_EDIT_MODAL_SIZE, 0, 0);

			wbnet_SendMessage((TCHAR*)&data, sizeof(data));
			return 0;
		}
		//Ÿ�� ��ư
		case IDC_BUTTON_MODAL_ELLIP:
		{
			printf("Ÿ�� ��ư \n");
			ELLIPSEPRINT data;
			data.flag = 2;
			data.x = GetDlgItemInt(hDlg, IDC_EDIT_MODAL_X, 0, 0);
			data.y = GetDlgItemInt(hDlg, IDC_EDIT_MODAL_Y, 0, 0);
			data.width = GetDlgItemInt(hDlg, IDC_EDIT_MODAL_SIZE, 0, 0);

			wbnet_SendMessage((TCHAR*)&data, sizeof(data));
			return 0;
		}
		//���ڿ� ��ư
		case IDC_BUTTON_MODAL_STRING:
		{
			printf("���ڿ� ��ư \n");
			STRINGEPRINT data;
			data.flag = 3;
			data.x = GetDlgItemInt(hDlg, IDC_EDIT_MODAL_X, 0, 0);
			data.y = GetDlgItemInt(hDlg, IDC_EDIT_MODAL_Y, 0, 0);
			
			TCHAR buff[20];
			GetDlgItemText(hDlg, IDC_EDIT_MODAL_STRING, buff, 20);
			_tcscpy(data.str, buff);
			wbnet_SendMessage((TCHAR*)&data, sizeof(data));
			return 0;
		}
		case IDCANCEL:
		{
			//_temp->color = tt;

			EndDialog(hDlg, IDCANCEL);	return 0;
		}
		case IDOK:
		{
			printf("��� ������\n");
			EndDialog(hDlg, IDOK);	return 0;
		}

		}
		return TRUE;
	}

	}
	return FALSE;
}


UINT SWSS_CreateWindow(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	UINT	ret = DialogBoxParam(GetModuleHandle(0),// instance
		MAKEINTRESOURCE(IDD_DIALOG2),	// ���̾�α� ���� 
		0,			// �θ� ������
		ModalProc,
		lParam);			// Proc..

	return ret;
}
