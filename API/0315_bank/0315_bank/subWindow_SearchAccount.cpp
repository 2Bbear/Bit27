#include"std.h"
extern HWND mainhwnd;

//static TCHAR temp[50];
BOOL CALLBACK SW_SearchAccountProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
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
		switch (LOWORD(wParam))
		{
			//Ȯ�� ��ư�� ������ ��
		case IDOK:
		{
		
			TCHAR temp[50];
			//id��������
			GetDlgItemText(hDlg, IDC_SW_SA_EDIT1, temp, _tcslen(temp));
			
			//�θ𿡰� �޼��� ������
			SendMessage(mainhwnd, MY_ACCOUNTDETAILPRINT, (WPARAM)temp, (LPARAM)temp);
		
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