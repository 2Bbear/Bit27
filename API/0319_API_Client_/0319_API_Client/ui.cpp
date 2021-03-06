#include"std.h"
HWND g_hLinkButton;
HWND g_hSendButton;
HWND g_hTextPrintEdit;

void ui_InitDialog(HWND hDlg)
{
	//버튼 핸들 받기
	g_hLinkButton = GetDlgItem(hDlg, IDC_BUTTON_LINK);
	g_hSendButton= GetDlgItem(hDlg, IDC_BUTTON_SEND);
	g_hTextPrintEdit= GetDlgItem(hDlg, IDC_EDIT2);

	//Dlg 초기화
	SetDlgItemText(hDlg, IDC_IPADDRESS1, TEXT("192.168.0.33"));
	SetDlgItemInt(hDlg, IDC_EDIT_PORT, 9000, 0);
}


void ui_LogMessage(TCHAR * _msg)
{
	SendMessage(g_hTextPrintEdit, EM_REPLACESEL, 0, (LPARAM)_msg);
	SendMessage(g_hTextPrintEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));

}

void ui_getAddress(HWND hDlg, TCHAR * ip, int *port)
{
	GetDlgItemText(hDlg, IDC_IPADDRESS1, ip, 256);
	*port = GetDlgItemInt(hDlg, IDC_EDIT_PORT, 0, 0);
}

void ui_SetButtonString(TCHAR * str)
{
	SetWindowText(g_hLinkButton, str);
}

void ui_GetSendMessage(HWND hDlg, TCHAR * msg)
{
	GetDlgItemText(hDlg, IDC_EDIT3, msg, 50);

}
