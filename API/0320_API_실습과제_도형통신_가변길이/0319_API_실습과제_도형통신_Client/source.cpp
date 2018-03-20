#include"std.h"

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//�ʱ�ȭ event
	case WM_INITDIALOG:
	{
		OnInitDialog(hDlg,wParam,lParam);
		return TRUE;
	}
	case WM_LBUTTONDOWN:
	{
		
		return 0;
	}
	//�޼��� �޴� event�� ó���ϱ� ���� ����
	case WM_COMMAND:
	{
		OnCommand(hDlg, wParam, lParam);
		return TRUE;
	}
	case WM_PAINT:
	{
		return OnPaInt(hDlg, wParam, lParam);
	}

	}
	return FALSE;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd)
{

	//�ܼ� ��¿�
	AllocConsole(); // console â ����

	freopen("CONOUT$",   // console ��
		"wt",        // text write ����
		stdout);	  // stdout �� ����..

	UINT	ret = DialogBox(hInst,// instance
		MAKEINTRESOURCE(IDD_DIALOG1),	// ���̾�α� ���� 
		0,			// �θ� ������
		DlgProc);			// Proc..
	return 0;
}
