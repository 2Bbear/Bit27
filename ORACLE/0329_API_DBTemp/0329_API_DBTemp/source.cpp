#include"std.h"

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//�ʱ�ȭ event
	case WM_INITDIALOG:
	{
		OnInitDialog(hDlg);
		return TRUE;
	}
	//�޼��� �޴� event�� ó���ϱ� ���� ����
	case WM_COMMAND:
	{
		return OnCommand(hDlg,wParam,lParam);
		
	}
	case WN_CANCEL:
	{
		if (wbdb_DBDConnect() == FALSE)
		{
			MessageBox(0, TEXT("���� ����"), TEXT(""), 0);
		}
		else
		{
			MessageBox(0, TEXT("���� ����"), TEXT(""), 0);
		}
		
		return 0;
	}
	}
	return FALSE;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd)
{
	UINT	ret = DialogBox(hInst,// instance
		MAKEINTRESOURCE(IDD_MAINDLG),	// ���̾�α� ���� 
		0,			// �θ� ������
		DlgProc);			// Proc..
	return 0;
}
