#include"std.h"

//vector<PROINFO*>g_pList;

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	AllocConsole(); // console â ����
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "wt", stdout);
	

	switch (msg)
	{
		//�ʱ�ȭ event
	case WM_INITDIALOG:
	{
		return OnInitDialog(hDlg, wParam, lParam);
	}
	//�޼��� �޴� event�� ó���ϱ� ���� ����
	case WM_COMMAND:
	{
		return OnCommand(hDlg, wParam, lParam);
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
