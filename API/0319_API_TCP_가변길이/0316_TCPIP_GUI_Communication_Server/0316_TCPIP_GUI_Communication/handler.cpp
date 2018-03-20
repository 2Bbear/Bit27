#include"std.h"


//
BOOL OnInitDlg(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//dlg �ڵ鰪 �ʱ�ȭ
	ui_InitControl(hDlg);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//��ư �Է��� �޴� event�� ó���ϱ� ���� ����
	switch (LOWORD(wParam))
	{
	//�����ư ������ �޼���
	case IDC_ACTIONBUTTON:
	{
		OnStartServer(hDlg);
		return 0;
	}
	//Ȯ�ι�ư
	case IDOK:
	{
		return 0;
	}
	//��ҹ�ư
	case IDCANCEL:
	{
		EndDialog(hDlg, IDCANCEL);	
		return 0;
	}

	}
	return FALSE;
}

void OnStartServer(HWND hDlg)
{
	int port;
	port=ui_getPort(hDlg);
	wbnet_StartServer(port);
}

void OnLogMessage(TCHAR * msg)
{
	ui_LogMessage(msg);
}

void OnClientLogMessage(int flag, char * ip, int port)
{
	TCHAR buf[256];
	wchar_t w_ip[250];
	MultiByteToWideChar(CP_ACP, 0, ip, -1, w_ip, 250);


	if(flag==1)
		wsprintf(buf,TEXT("Ŭ���̾�Ʈ ���� (%s: %d)"), w_ip,port);
	else if (flag==0)
		wsprintf(buf, TEXT("Ŭ���̾�Ʈ ���� (%s: %d)"), w_ip, port);


	ui_LogMessage(buf);
}

void OnMessage(char * _buf, int _nRead)
{
	TCHAR buf[256];
	//wchar_t w_ip[250];
	memcpy(buf, _buf, _nRead);
	
	//MultiByteToWideChar(CP_ACP, 0, _buf, -1, w_ip, 250);

	ui_LogMessage(buf);
}
