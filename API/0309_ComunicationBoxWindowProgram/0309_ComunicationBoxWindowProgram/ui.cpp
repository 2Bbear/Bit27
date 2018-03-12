#include"std.h"
HWND g_hRadio1;
HWND g_hComboBox1;
HWND g_hStatic1;
HWND g_hStatic2;

void ui_GetControlHandle(HWND hDlg)
{
	//자식의 핸들값을 얻어오는 함수
	//radio 
	g_hRadio1= GetDlgItem(hDlg, IDC_RADIO1);
	SendMessage(g_hRadio1, BM_SETCHECK, true, 0);

	//combo
	g_hComboBox1 = GetDlgItem(hDlg, IDC_COMBO1);
	//combo박스에 글자 추가하기
	SendMessage(g_hComboBox1, CB_ADDSTRING, 0, (LPARAM)TEXT("R"));
	SendMessage(g_hComboBox1, CB_ADDSTRING, 0, (LPARAM)TEXT("G"));
	SendMessage(g_hComboBox1, CB_ADDSTRING, 0, (LPARAM)TEXT("B"));
	SendMessage(g_hComboBox1, WM_SETCURSOR,0,0);
	
	//static 1
	g_hStatic1= GetDlgItem(hDlg, IDC_STATIC1);
	//static 2
	g_hStatic2 = GetDlgItem(hDlg, IDC_STATIC2);




}

void ui_TypeSelectButton(HWND hDlg)
{
	 TCHAR str[30];
	
	if (SendMessage(g_hRadio1, BM_GETCHECK, 0, 0) == BST_CHECKED)
	{
		wsprintf(str, TEXT("%s"),TEXT("사각형"));
	}
	else
	{
		wsprintf(str, TEXT("%s"),TEXT("타원"));
	}
	SetDlgItemText(hDlg, IDC_STATIC1, str);
	
}

void ui_ColorSelectComboBox(HWND hDlg)
{
	//현재 어디가 선택되어 있는지 확인
	int idx = SendMessage(g_hComboBox1, CB_GETCURSEL, 0, 0);
	//해당 위치에 있는 문자 값을 가져오기
	TCHAR buf[40];
	SendMessage(g_hComboBox1, CB_GETLBTEXT, idx, LPARAM(buf));
	//static control에 메세지 보내기
	SetWindowText(g_hStatic2, (LPCWSTR)buf);//대화창 내용을 초기화 하는 함수
	
}
