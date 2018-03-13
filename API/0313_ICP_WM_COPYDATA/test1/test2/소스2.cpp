#include <Windows.h>
#include<tchar.h>
//You must have make Resource-Dialog 
#include"resource.h"

void OnCopyData(HWND hDlg,WPARAM wParam, LPARAM lParam)
{
	HWND hEdit = GetDlgItem(hDlg, IDC_EDIT1);
	COPYDATASTRUCT* p = (COPYDATASTRUCT*)lParam;
	if (p->dwData == 1) // �ĺ��� ����.
	{
		//��� �±� �߰� ����
		TCHAR Mebuf[300];
		wsprintf(Mebuf, TEXT("A :%s"), p->lpData);
		// Edit Box�� �߰� �Ѵ�.
		SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)Mebuf);
		SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
	}
}
HWND hwnd;
void OnConnect(HWND hDlg)
{

	
	hwnd = FindWindow(0, TEXT("A"));
	


}
void OnSendData(HWND hDlg)
{
	//���� ���ڿ�
	TCHAR buf[256];
	GetDlgItemText(hDlg, IDC_EDIT2, buf, sizeof(buf));
	// �������� Pointer�� �����ϱ� ���� �޼��� - WM_COPYDATA
	COPYDATASTRUCT cds;
	cds.cbData = _tcslen(buf) * 2 + 2;  // ������ data ũ��
	cds.dwData = 1;				// �ĺ��� 
	cds.lpData = buf;			// ������ Pointer
	SendMessage(hwnd, WM_COPYDATA, 0, (LPARAM)&cds);
	TCHAR Mebuf[300];
	wsprintf(Mebuf, TEXT("B :%s"), buf);
	HWND hEdit = GetDlgItem(hDlg, IDC_EDIT1);
	SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)Mebuf);
	SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));

}

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//����Ÿ ���� �ޱ�
	case WM_COPYDATA:
	{
		OnCopyData(hDlg,wParam,lParam);
		
		return 0;
	}
	


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
			//����Ÿ �����ϱ�
		case IDC_BUTTON1:
		{
			OnConnect(hDlg);
			OnSendData(hDlg);
			return 0;
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
