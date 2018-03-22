//ui.cpp

#include "std.h"

HWND g_hEdit2, g_hButton1, g_hButton4,g_hButton5,g_hButton6,g_hButton2;
HWND g_hEditCodeLine;
extern HWND g_hDlg;

void ui_GetFilePathOrName(HWND hDlg, TCHAR * _path, TCHAR * _name)
{
	GetDlgItemText(hDlg, IDC_EDIT_OPENPATH, _path, 256);
	GetDlgItemText(hDlg, IDC_STATIC_1, _name, 50);
}


void ui_InitControl(HWND hDlg)
{
	g_hEdit2 = GetDlgItem(hDlg, IDC_EDIT2);
	g_hButton1 = GetDlgItem(hDlg, IDC_BUTTON1);
	g_hButton2 = GetDlgItem(hDlg, IDC_BUTTON2);//전송 버튼
	g_hButton4 = GetDlgItem(hDlg, IDC_BUTTON4);//로그인
	g_hButton5 = GetDlgItem(hDlg, IDC_BUTTON5);//회원 탈퇴 버튼
	g_hButton6= GetDlgItem(hDlg, IDC_BUTTON6);//로그 아웃 버튼

	g_hEditCodeLine= GetDlgItem(hDlg, IDC_EDIT_CODELINE);//코드 에디트


	ui_EnableButton(FALSE, FALSE, FALSE,TRUE);


	//SetDlgItemText(hDlg, IDC_IPADDRESS1, TEXT("192.168.0.52"));
	//SetDlgItemInt(hDlg, IDC_EDIT1, 9000, 0);
}
void ui_EnableButton(BOOL bmin,BOOL out,BOOL send,BOOL login)
{
	EnableWindow(g_hButton5, bmin);//전송 버튼
	EnableWindow(g_hButton6, out);// 회원탈퇴
	EnableWindow(g_hButton2, send);// 로그아웃
	EnableWindow(g_hButton4, login);// 로그인

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
//	SetDlgItemText(hDlg, IDC_EDIT8, TEXT(""));
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

void 	ui_GetSendCodeMessage(HWND hDlg, TCHAR* msg)
{
	GetDlgItemText(hDlg, IDC_EDIT_CODELINE, msg, 500);
}

void ui_PrintCodeLine(TCHAR * msg)
{
	SetDlgItemText(g_hDlg, IDC_EDIT_CODELINE, msg);
	//SendMessage(g_hEdit2, EM_REPLACESEL, 0, (LPARAM)msg);
	//SendMessage(g_hEdit2, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
}

void ui_GetFileInfo(HWND hDlg, TCHAR * path, TCHAR * name)
{
	OPENFILENAME OFN;
	TCHAR str[300];

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hDlg;
	OFN.lpstrFilter = TEXT("모든 파일(*.*)\0*.*\0");
	OFN.lpstrFile = path;
	OFN.nMaxFile = MAX_PATH;

	if (GetOpenFileName(&OFN) != 0) {
		wsprintf(str, TEXT("%s 파일을 선택했습니다."), OFN.lpstrFile);
	
	}
	SetDlgItemText(hDlg, IDC_EDIT_OPENPATH, path);
	//path==>* . *
	/*TCHAR name2[100] = _TEXT("");
	_tcscpy_s(name2, path);*/
	//파일명 추출
	ui_GetFileName(path);

	SetDlgItemText(hDlg, IDC_STATIC_1, path);

}

void ui_GetFileName(TCHAR * _name)
{
	PathStripPath(_name);
}
