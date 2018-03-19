//�ҽ�.cpp
#include "std.h"

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		return OnInitDialog(hDlg,wParam,lParam);// OnInitDialog(hDlg);
	}
	case WM_COMMAND:
	{
		return OnCommand(hDlg, wParam, lParam);
		
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

	UINT ret = DialogBox(
		hInst,							// instance 
		MAKEINTRESOURCE(IDD_DIALOG1),	// ���̾�α� ���� 
		0,								// �θ� ������ 
		DlgProc);						// Proc.. 

	return 0;
}