#include"std.h"

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	ui_GetControlHandle(hDlg);
	return true;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{

	//���� ���� ��ư
	case IDC_BUTTON1:
	{ 
		ui_TypeSelectButton(hDlg);  
		return true;
	}
	//���� ���� ��ư
	case IDC_COMBO1 :
	{
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			ui_ColorSelectComboBox(hDlg);
		}
		return true;
	}
	case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return true;
	}
	return true;
}
