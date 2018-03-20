#include"std.h"

//Dlg Handle
HWND g_hButtonActive;
HWND g_hEditLogPrint;

void ui_InitControl(HWND hDlg)
{
	//핸들값 받아오기
	g_hButtonActive = GetDlgItem(hDlg, IDC_BUTTON_ACTIVE);
	g_hEditLogPrint = GetDlgItem(hDlg, IDC_EDIT_LOGPRINT);

	/*SetDlgItemText(hDlg, IDC_IPADDRESS1, TEXT("192.168.0.52"));
	SetDlgItemInt(hDlg, IDC_EDIT1, 9000, 0);*/
}



void ui_LogMessage(TCHAR *msg)
{
	SendMessage(g_hEditLogPrint, EM_REPLACESEL, 0, (LPARAM)msg);
	SendMessage(g_hEditLogPrint, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
}