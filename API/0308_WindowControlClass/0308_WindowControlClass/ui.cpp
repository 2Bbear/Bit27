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
	g_hEdit1 = CreateWindow(TEXT("Edit"), TEXT("���� �Է����ּ���"),WS_CHILD | WS_VISIBLE | WS_BORDER,10, 10, 200, 20, hwnd, (HMENU)IDC_EDIT1, 0, 0);
	
	//create Static control
	g_hStatic1 = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 40, 200, 50, hwnd, (HMENU)IDC_STATIC1, 0, 0);

	//Create Button control
	g_hEdit2 = CreateWindow(TEXT("Button"), TEXT("�̰� ��ư�̷�"), WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 100, 150, 101, hwnd, (HMENU)IDC_EDIT2, 0, 0);

	//create ListBox
	g_hListBox= CreateWindow(TEXT("Listbox"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER |LBS_NOTIFY, 10, 220, 200, 240, hwnd, (HMENU)IDC_List1, 0, 0);

	//create ComboBox
	g_hComboBox1= CreateWindow(TEXT("ComboBox"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER |CBS_DROPDOWN , 250, 220, 350, 240, hwnd, (HMENU)IDC_COMBOBOX1, 0, 0);

	//create Static2
	g_hStatic2 = CreateWindow(TEXT("Static"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 250, 40, 350, 50, hwnd, (HMENU)IDC_STATIC2, 0, 0);
	

}

void ui_EditSetFpcus(HWND hwnd)
{
	SetWindowText(g_hEdit1, TEXT(""));//��ȭâ ������ �ʱ�ȭ �ϴ� �Լ�
}

void ui_ButtonClick(HWND hwnd)
{
	TCHAR buf[30];
	GetWindowText(g_hEdit1, buf, 30);//g_hEdit1 ID���� ���� �����쿡�� ���ڸ� �о�ͼ� buf�� �����ϴ� �Լ�
	//MessageBox(0, buf,TEXT(""),MB_OK);
	SendMessage(g_hListBox, LB_ADDSTRING, 0, (LPARAM)buf);
	SendMessage(g_hComboBox1, CB_ADDSTRING, 0, (LPARAM)buf);
	SetFocus(g_hEdit1);
}

void ui_ListBoxSelChange(HWND hwnd)
{
	//���� ��� ���õǾ� �ִ��� Ȯ��
	int idx=SendMessage(g_hListBox, LB_GETCURSEL, 0, 0);
	//�ش� ��ġ�� �ִ� ���� ���� ��������
	TCHAR buf[40];
	SendMessage(g_hListBox, LB_GETTEXT, idx, LPARAM(buf));
	//static control�� �޼��� ������
	SetWindowText(g_hStatic1,(LPCWSTR)buf);//��ȭâ ������ �ʱ�ȭ �ϴ� �Լ�

	//MessageBox(0, buf, TEXT(""), MB_OK);
}

void ui_ComboBoxSelChange(HWND hwnd)
{
	//���� ��� ���õǾ� �ִ��� Ȯ��
	int idx = SendMessage(g_hComboBox1, CB_GETCURSEL, 0, 0);
	//�ش� ��ġ�� �ִ� ���� ���� ��������
	TCHAR buf[40];
	SendMessage(g_hComboBox1, CB_GETLBTEXT, idx, LPARAM(buf));
	//static control�� �޼��� ������
	SetWindowText(g_hStatic2, (LPCWSTR)buf);//��ȭâ ������ �ʱ�ȭ �ϴ� �Լ�
}
