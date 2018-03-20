#include"std.h"

HWND g_hButtonConnection;
HWND g_hButtonModal;
HWND hMain;
void ui_InitDlg(HWND hDlg)
{
	hMain = hDlg;
	//Dlg วฺต้
	g_hButtonConnection =GetDlgItem(hDlg, IDC_BUTTON_CONNECTION);
	g_hButtonModal = GetDlgItem(hDlg, IDC_BUTTON_MODAL);
}

void ui_Draw(HDC hdc, int flag, int x, int y, int width, TCHAR * str)
{
	switch (flag)
	{
	case PACK_RECTPRINT:
	{
		
		Rectangle(hdc, x - width, y - width, x + width, y + width);
		
		break;
	}
	case PACK_ELLIPSEPRINT:
	{
		Ellipse(hdc, x - width, y - width, x + width, y + width);
		break;
	}
	case PACK_STRINGPRINT:
	{
		break;
	}
	}
}

