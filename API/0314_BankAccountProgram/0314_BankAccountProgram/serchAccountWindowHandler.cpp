#include"std.h"

HWND parentsHandle;
HINSTANCE g_hInst2;
TCHAR * localTempID;
BOOL CALLBACK DlgProc3(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
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
			//id ��������
			GetDlgItemText(hDlg, IDC_EDIT111, temp, _tcslen(temp));
			//id ������ Account��������
			Account * pAcc = B_FindAccount(temp);
			//���� temp �޸𸮷� id�� ��������
			_tcscpy(localTempID,pAcc->id);
			//�θ𿡰� ������ ����Ʈ�� ����϶�� �޼��� ����
			SendMessage(parentsHandle, WM_USER + 100, (WPARAM)pAcc->id, 0);
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
void SAWH_CreateDialogWindow(TCHAR * _tempID,HWND hwnd)
{
	parentsHandle = hwnd;
	localTempID = _tempID;
	g_hInst2 = GetModuleHandle(0);
	//�� �ڵ� ��ü�� ���ο� â�� ���� ��
	UINT ret = DialogBox(g_hInst2,// instance 
		MAKEINTRESOURCE(IDD_DIALOG3), // ���̾�α� ���� 
		0,   // �θ� ������ 
		DlgProc3);   // Proc..
}
