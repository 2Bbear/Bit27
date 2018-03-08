#include"std.h"

//=====================


HWND g_hEdit1;
HWND g_hEdit2;
HWND g_hListBox;
HWND g_hStatic1;
HWND g_hComboBox1, g_hStatic2;

//====================
LRESULT Oncreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	ui_CreateControl(hwnd);
	return 0;
}

LRESULT OnCommand(HWND hwnd, WPARAM wParam)
{
	switch ((LOWORD(wParam)))
	{
	case IDC_EDIT1:
	{
		if (HIWORD(wParam) == EN_SETFOCUS)
		{
			ui_EditSetFpcus(hwnd);
		}
		break;
	}
	case IDC_EDIT2:
	{
		ui_ButtonClick(hwnd);
		break;
	}
	case IDC_List1:
	{
		if (HIWORD(wParam)==LBN_SELCHANGE)//리스트 박스가 선택 되었을 때
		{
			ui_ListBoxSelChange(hwnd);
		}
		break;
	}
	case IDC_COMBOBOX1:
	{
		if (HIWORD(wParam)==CBN_SELCHANGE)
		{
			ui_ComboBoxSelChange(hwnd);
		}
		break;
	}

	}
	return 0;
}
