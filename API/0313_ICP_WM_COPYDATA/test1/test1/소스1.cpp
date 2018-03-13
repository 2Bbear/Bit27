#include <Windows.h>
#include<tchar.h>
//You must have make Resource-Dialog 
#include"resource.h"
HWND hwnd;
void OnConnect(HWND hDlg)
{

	TCHAR str[20];
	GetDlgItemText(hDlg, IDC_EDIT3, str, sizeof(str));
	hwnd = FindWindow(0,str );
	if (hwnd == 0)
	{
		MessageBox(hDlg, TEXT("B �����츦 ���� ������� �ּ���!\n"), TEXT("�˸�"), MB_OK);
	}
	
	

}
void OnSendData(HWND hDlg)
{
	//���� ���ڿ�
	TCHAR buf[256];
	GetDlgItemText(hDlg, IDC_EDIT1, buf, sizeof(buf));
	// �������� Pointer�� �����ϱ� ���� �޼��� - WM_COPYDATA
	COPYDATASTRUCT cds;
	cds.cbData = _tcslen(buf)*2 + 2;  // ������ data ũ��
	cds.dwData = 1;				// �ĺ��� 
	cds.lpData = buf;			// ������ Pointer
	SendMessage(hwnd, WM_COPYDATA, 0, (LPARAM)&cds);

	HWND hEdit = GetDlgItem(hDlg, IDC_EDIT2);

	TCHAR Mebuf[300];
	wsprintf(Mebuf, TEXT("A :%s"),buf);
	SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)Mebuf);
	SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));

}
void OnCopyData(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	HWND hEdit = GetDlgItem(hDlg, IDC_EDIT2);
	COPYDATASTRUCT* p = (COPYDATASTRUCT*)lParam;
	if (p->dwData == 1) // �ĺ��� ����.
	{
		//��� �±� �߰� ����
		TCHAR Mebuf[300];
		wsprintf(Mebuf, TEXT("B :%s"), p->lpData);
		// Edit Box�� �߰� �Ѵ�.
		SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)Mebuf);
		SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
	}
}
BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	
	//����Ÿ ���� �ޱ�
	case WM_COPYDATA:
	{
		OnCopyData(hDlg, wParam, lParam);

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

		case IDC_BUTTON3:
		{
			
			OnConnect(hDlg);
			return 0;
		}
		case IDC_BUTTON2:
		{
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
