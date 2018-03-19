#include"std.h"
//dlg handle
HWND g_hAcctionButton;
HWND g_hCurrentConnectCountStatic;
HWND g_hIPEdit;
HWND g_hPortEdit;
HWND g_hConnectList;
HWND g_hTextPrintEdit;

void ui_InitControl(HWND hDlg)
{
	//dlg 핸들값 저장
	g_hAcctionButton = GetDlgItem(hDlg, IDC_ACTIONBUTTON);
	g_hCurrentConnectCountStatic = GetDlgItem(hDlg, IDC_STATIC_CRRENTCONNECTCOUNT);
	g_hIPEdit = GetDlgItem(hDlg, IDC_IPADDRESS1);
	g_hPortEdit = GetDlgItem(hDlg, IDC_EDIT_PORT);
	g_hConnectList = GetDlgItem(hDlg, IDC_LIST1);
	g_hTextPrintEdit = GetDlgItem(hDlg, IDC_EDIT3);

	//ip ,port dlg setting
	//이 컴퓨터 ip "192.168.0.33"
	SetDlgItemText(hDlg, IDC_IPADDRESS1,TEXT("192.168.0.33"));
	SetDlgItemInt(hDlg, IDC_EDIT_PORT, 9000, 0);

	//접속개수 static text setting
	ui_SetCurrentConnectCountStatic(0);

}

void ui_SetCurrentConnectCountStatic(int n)
{
	TCHAR buf[10];
	wsprintf(buf,TEXT("접속개수: %d"),n);
	SetWindowText(g_hCurrentConnectCountStatic,buf);
}

int ui_getPort(HWND hDlg)
{
	return GetDlgItemInt(hDlg, IDC_EDIT_PORT, 0, 0);
}

void ui_LogMessage(TCHAR * _msg)
{
	SendMessage(g_hTextPrintEdit, EM_REPLACESEL, 0, (LPARAM)_msg);
	SendMessage(g_hTextPrintEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));

}
