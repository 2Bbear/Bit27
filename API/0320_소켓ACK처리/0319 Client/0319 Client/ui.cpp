//ui.cpp

#include "std.h"

HWND g_hEdit2, g_hButton1;

void ui_InitControl(HWND hDlg)
{
	g_hEdit2 = GetDlgItem(hDlg, IDC_EDIT2);
	g_hButton1 = GetDlgItem(hDlg, IDC_BUTTON1);

	SetDlgItemText(hDlg, IDC_IPADDRESS1, TEXT("192.168.0.33"));
	SetDlgItemInt(hDlg, IDC_EDIT1, 9000, 0);
}

void ui_LogMessage(TCHAR *msg)
{
	SendMessage(g_hEdit2, EM_REPLACESEL, 0, (LPARAM)msg);
	SendMessage(g_hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
}

void ui_getAddress(HWND hDlg, TCHAR* ip, int *port)
{
	GetDlgItemText(hDlg, IDC_IPADDRESS1, ip, 256);
	*port = GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
}

void ui_SetButtonString(TCHAR * msg)
{
	SetWindowText(g_hButton1, msg);
}


void ui_GetAddMember(HWND hDlg, TCHAR*name, TCHAR *id, TCHAR*pw)
{
	GetDlgItemText(hDlg, IDC_EDIT4, name, 20);
	GetDlgItemText(hDlg, IDC_EDIT5, id, 20);
	GetDlgItemText(hDlg, IDC_EDIT6, pw, 20);

	SetDlgItemText(hDlg, IDC_EDIT4, TEXT(""));
	SetDlgItemText(hDlg, IDC_EDIT5, TEXT(""));
	SetDlgItemText(hDlg, IDC_EDIT6, TEXT(""));
}

void ui_GetSendMessage(HWND hDlg, TCHAR* msg)
{
	GetDlgItemText(hDlg, IDC_EDIT_SHORTMESSAGE, msg, 80);
}

void ui_GetLogin(HWND hDlg, TCHAR * id, TCHAR * pw)
{
	GetDlgItemText(hDlg, IDC_EDIT5, id, 20);
	GetDlgItemText(hDlg, IDC_EDIT6, pw, 20);

	//SetDlgItemText(hDlg, IDC_EDIT5, TEXT(""));
	//SetDlgItemText(hDlg, IDC_EDIT6, TEXT(""));
}
