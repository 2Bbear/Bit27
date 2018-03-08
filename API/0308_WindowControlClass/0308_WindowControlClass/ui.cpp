#include"std.h"



//=====================


extern HWND g_hEdit1;
extern HWND g_hEdit2;
extern HWND g_hListBox;
extern HWND g_hStatic1;
extern HWND g_hComboBox1, g_hStatic2;
//====================

void ui_CreateControl(HWND hwnd)
{
	
	//Create Edit Control
	g_hEdit1 = CreateWindow(TEXT("Edit"), TEXT("뭔가 입력해주세요"),WS_CHILD | WS_VISIBLE | WS_BORDER,10, 10, 200, 20, hwnd, (HMENU)IDC_EDIT1, 0, 0);
	
	//create Static control
	g_hStatic1 = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 40, 200, 50, hwnd, (HMENU)IDC_STATIC1, 0, 0);

	//Create Button control
	g_hEdit2 = CreateWindow(TEXT("Button"), TEXT("이건 버튼이래"), WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 100, 150, 101, hwnd, (HMENU)IDC_EDIT2, 0, 0);

	//create ListBox
	g_hListBox= CreateWindow(TEXT("Listbox"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER |LBS_NOTIFY, 10, 220, 200, 240, hwnd, (HMENU)IDC_List1, 0, 0);

	//create ComboBox
	g_hComboBox1= CreateWindow(TEXT("ComboBox"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER |CBS_DROPDOWN , 250, 220, 350, 240, hwnd, (HMENU)IDC_COMBOBOX1, 0, 0);

	//create Static2
	g_hStatic2 = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 250, 40, 350, 50, hwnd, (HMENU)IDC_STATIC2, 0, 0);
	

}

void ui_EditSetFpcus(HWND hwnd)
{
	SetWindowText(g_hEdit1, TEXT(""));//대화창 내용을 초기화 하는 함수
}

void ui_ButtonClick(HWND hwnd)
{
	TCHAR buf[30];
	GetWindowText(g_hEdit1, buf, 30);//g_hEdit1 ID값을 갖는 윈도우에서 글자를 읽어와서 buf에 저장하는 함수
	//MessageBox(0, buf,TEXT(""),MB_OK);
	SendMessage(g_hListBox, LB_ADDSTRING, 0, (LPARAM)buf);
	SendMessage(g_hComboBox1, CB_ADDSTRING, 0, (LPARAM)buf);
	SetFocus(g_hEdit1);
}

void ui_ListBoxSelChange(HWND hwnd)
{
	//현재 어디가 선택되어 있는지 확인
	int idx=SendMessage(g_hListBox, LB_GETCURSEL, 0, 0);
	//해당 위치에 있는 문자 값을 가져오기
	TCHAR buf[40];
	SendMessage(g_hListBox, LB_GETTEXT, idx, LPARAM(buf));
	//static control에 메세지 보내기
	SetWindowText(g_hStatic1,(LPCWSTR)buf);//대화창 내용을 초기화 하는 함수

	//MessageBox(0, buf, TEXT(""), MB_OK);
}

void ui_ComboBoxSelChange(HWND hwnd)
{
	//현재 어디가 선택되어 있는지 확인
	int idx = SendMessage(g_hComboBox1, CB_GETCURSEL, 0, 0);
	//해당 위치에 있는 문자 값을 가져오기
	TCHAR buf[40];
	SendMessage(g_hComboBox1, CB_GETLBTEXT, idx, LPARAM(buf));
	//static control에 메세지 보내기
	SetWindowText(g_hStatic2, (LPCWSTR)buf);//대화창 내용을 초기화 하는 함수
}
