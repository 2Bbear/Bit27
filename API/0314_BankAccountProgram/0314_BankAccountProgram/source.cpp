#include"std.h"


BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//custom message 
	//������ ����Ʈ ����ϱ� �޼���
	case WM_USER + 100:
	{
		//���ļ� ����� ����
		TCHAR * c = (TCHAR*)wParam;
		Account * acc=B_FindAccount(c);
		setEditControls(acc->accountNum, acc->name, acc->balance);
		return OnRightListControlPrint(hDlg,wParam,lParam);
	}
		//�ʱ�ȭ event
	case WM_INITDIALOG:
	{
		return OnInitDialog(hDlg, wParam, lParam);
	}
	//�޼��� �޴� event�� ó���ϱ� ���� ����
	case WM_COMMAND:
	{
		return OnCommand(hDlg,wParam, lParam);
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
