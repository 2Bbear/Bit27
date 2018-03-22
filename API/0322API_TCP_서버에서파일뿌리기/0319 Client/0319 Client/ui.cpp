//ui.cpp

#include "std.h"

HWND g_hEdit2, g_hButton1, g_hButton4;
HWND g_hButton5; //회원탈퇴
HWND g_hButton6; //로그아웃
HWND g_hButton2; //전송

extern HWND g_hDlg;

void ui_InitControl(HWND hDlg)
{
	g_hEdit2 = GetDlgItem(hDlg, IDC_EDIT2);
	g_hButton1 = GetDlgItem(hDlg, IDC_BUTTON1);
	g_hButton4 = GetDlgItem(hDlg, IDC_BUTTON4);
	g_hButton5 = GetDlgItem(hDlg, IDC_BUTTON5);
	g_hButton6 = GetDlgItem(hDlg, IDC_BUTTON6);
	g_hButton2 = GetDlgItem(hDlg, IDC_BUTTON2);
	
	ui_EnableButton(FALSE, FALSE, FALSE, TRUE);
	
}

void ui_EnableButton(BOOL bmin, BOOL logout, BOOL send, BOOL login)
{
	EnableWindow(g_hButton5, bmin);		//회원탈퇴
	EnableWindow(g_hButton6, logout);	//로그아웃
	EnableWindow(g_hButton2, send);		//전송
	EnableWindow(g_hButton4, login);	//로그인
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

void ui_SetLoginButtonString(TCHAR * msg)
{
	SetWindowText(g_hButton4, msg);
}


void ui_GetAddMember(HWND hDlg, TCHAR*name, TCHAR *id, TCHAR*pw)
{
	GetDlgItemText(hDlg, IDC_EDIT7, name, 20);
	GetDlgItemText(hDlg, IDC_EDIT8, id, 20);
	GetDlgItemText(hDlg, IDC_EDIT9, pw, 20);

	SetDlgItemText(hDlg, IDC_EDIT7, TEXT(""));
	//SetDlgItemText(hDlg, IDC_EDIT8, TEXT(""));
	SetDlgItemText(hDlg, IDC_EDIT9, TEXT(""));
}

void ui_GetMinMember(HWND hDlg, TCHAR* name, TCHAR* id, TCHAR* pw)
{
	GetDlgItemText(hDlg, IDC_EDIT4, name, 20);
	GetDlgItemText(hDlg, IDC_EDIT5, id, 20);
	GetDlgItemText(hDlg, IDC_EDIT6, pw, 20);

	SetDlgItemText(hDlg, IDC_EDIT4, TEXT(""));
	SetDlgItemText(hDlg, IDC_EDIT5, TEXT(""));
	SetDlgItemText(hDlg, IDC_EDIT6, TEXT(""));
}

void ui_GetLogin(HWND hDlg, TCHAR *id, TCHAR *pw)
{
	GetDlgItemText(hDlg, IDC_EDIT5, id, 20);
	GetDlgItemText(hDlg, IDC_EDIT6, pw, 20);

//	SetDlgItemText(hDlg, IDC_EDIT5, TEXT(""));
//	SetDlgItemText(hDlg, IDC_EDIT6, TEXT(""));
}

void ui_GetSendMessage(HWND hDlg, TCHAR* msg)
{
	GetDlgItemText(hDlg, IDC_EDIT3, msg, 50);
}

void ui_GetSendCodeMessage(HWND hDlg, TCHAR* msg)
{
	GetDlgItemText(hDlg, IDC_EDIT1, msg, 500);
}


void ui_CodeMessage(TCHAR *msg)
{
	SetDlgItemText(g_hDlg, IDC_EDIT1, msg);
}

void ui_GetFileInfo(HWND hDlg, TCHAR*path, TCHAR*name)
{
	OPENFILENAME OFN;
	TCHAR str[300];

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hDlg;
	OFN.lpstrFilter = TEXT("모든 파일(*.*)\0*.*\0");
	OFN.lpstrFile = path;
	OFN.nMaxFile = MAX_PATH;
	if (GetOpenFileName(&OFN) != 0) 
	{
		wsprintf(str, TEXT("%s 파일을 선택했습니다."), OFN.lpstrFile);
	}

	SetDlgItemText(hDlg, IDC_EDIT4, path);
	//path ==> *.*
	//TCHAR name[200];
	//_tcscpy_s(name, (TCHAR*)OFN.lpstrFile);
	ui_GetFileName(path);
	SetDlgItemText(hDlg, IDC_STATIC1, path);
}

void ui_GetFileName(TCHAR*name)
{
	PathStripPath(name);
}

void ui_GetFilePathOrName(HWND hDlg, TCHAR*path, TCHAR*name)
{
	GetDlgItemText(hDlg, IDC_EDIT4, path, 256);
	GetDlgItemText(hDlg, IDC_STATIC1, name, 50);
}