#include <Windows.h>
#include<tchar.h>
//You must have make Resource-Dialog 
#include"resource.h"

#include"handler.h"

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
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
		//���α׷� ���� ���� ��ư
		case IDC_BUTTON1:
		{
			
			//Process ���� ù��° 
			//OnExitProcess_1(hDlg);
			//process ���� �ι�°
			//OnExitProcess_2(GetCurrentProcess(),hDlg);
			//process ���� ����°
			
			return 0;
		}

		//OK ��ư
		case IDOK:
		{
			//Process ���� ù��° ���
			//OnCreateProcess_1();
			//Process ���� �ι�° ���
			OnCreateProcess_2();
			return 0;
		}
		//Cancel ��ư
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
