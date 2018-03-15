
//You must have make Resource-Dialog 

#include"std.h"

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//�ʱ�ȭ event
	case WM_INITDIALOG:
	{

		return OnInitDialog(hDlg);
	}
	//�ڽĿ��Լ� ���� AccountDetail ��� �޼��� wParam , lParam ���ʿ� id���� ������ ��� ���� ���� �� �� ���� TCHAR *��
	case MY_ACCOUNTDETAILPRINT:
	{
		
		return OnAccountDetailPrint(hDlg, wParam, lParam);
	}
	
	//�޼��� �޴� event�� ó���ϱ� ���� ����
	case WM_COMMAND:
	{
	
		//��ư �Է��� �޴� event�� ó���ϱ� ���� ����
		switch (LOWORD(wParam))
		{
			//����Ʈ ��Ʈ�� ���� �޼���
		case LVM_GETSELECTIONMARK:
		{
			MessageBox(hDlg, TEXT(""), TEXT(""), 0);
			return 0;
		}
		
		//��ܸ޴�
			//���α׷� ����
		case ID_40001:
		{
			return 0;
		}
		//���»���
		case ID_40002:
		{
			return OnCreateAccountWindow( hDlg,  wParam,  lParam);
		}
		//���� �˻�
		case ID_40003:
		{
			return OnSearchAccountWindow(hDlg,wParam,lParam);
		}
		//��ư�޴�
			//���� ��ư
		case IDC_DELETEACCBUTTON:
		{
			return OnDeleteAccountButton(hDlg);
		}
			//����� ��ư
		case IDC_BUTTON2:
		{

			return OnBankStatement(hDlg);
		}
		//������ư
			//�Ա� ��ư
		case IDC_RADIO1:
		{
			
			return OnDeposit();
		}
			//��� ��ư
		case IDC_RADIO2:
		{
			return OnWithdraw();
		}
		case IDCANCEL:
		{
			EndDialog(hDlg, IDCANCEL);	return 0;
		}

		}
		return TRUE;
	}

	}
	return FALSE;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd)
{
	UINT	ret = DialogBox(hInst,// instance
		MAKEINTRESOURCE(IDD_DIALOG1),	// ���̾�α� ���� 
		0,			// �θ� ������
		DlgProc);			// Proc..
	return 0;
}
