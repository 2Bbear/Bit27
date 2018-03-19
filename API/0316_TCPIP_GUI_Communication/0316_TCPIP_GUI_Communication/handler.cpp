#include"std.h"


//
BOOL OnInitDlg(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//dlg 핸들값 초기화
	ui_InitControl(hDlg);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//버튼 입력을 받는 event를 처리하기 위한 영역
	switch (LOWORD(wParam))
	{
	//실행버튼 누르는 메세지
	case IDC_ACTIONBUTTON:
	{
		OnStartServer(hDlg);
		return 0;
	}
	//확인버튼
	case IDOK:
	{
		return 0;
	}
	//취소버튼
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
		wsprintf(buf,TEXT("클라이언트 접속 (%s: %d)"), w_ip,port);
	else if (flag==0)
		wsprintf(buf, TEXT("클라이언트 해제 (%s: %d)"), w_ip, port);


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
