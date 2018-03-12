#include"std.h"

HWND g_hCombo;
void ui_GetHandle(HWND hDlg)
{
	g_hCombo = GetDlgItem(hDlg, IDC_COMBO1);
}

void ui_GetProcessName( TCHAR * buf)
{
	GetWindowText(g_hCombo, buf, 50);
}

void ui_SetComboBoxAddProcessName(TCHAR * buf)
{
	SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)buf);
}

int ui_ComboBoxSelChange(HWND hDlg)
{
	//현재 어디가 선택되어 있는지 확인
	int idx = SendMessage(g_hCombo, CB_GETCURSEL, 0, 0);
	return idx;
	

	
}

void ui_ProInfoPrint(HWND hDlg, PROINFO * p)
{
	//이름 출력
	SetDlgItemText(hDlg, IDC_EDIT1, (LPCWSTR)(p->name));//대화창 내용을 초기화 하는 함수
	

	//ID 출력
	SetDlgItemInt(hDlg, IDC_EDIT2, (p->id),0);//대화창 내용을 초기화 하는 함수
	//핸들 출력
	SetDlgItemInt(hDlg, IDC_EDIT3,(UINT) p->handle,0);//대화창 내용을 초기화 하는 함수
}

HANDLE ui_GetProcessHandle(HWND hDlg)
{
	return (HANDLE)GetDlgItemInt(hDlg, IDC_EDIT3, 0, 0);
	
}

void ui_ExitCodePrint(HWND hDlg, int  code)
{
	TCHAR buf[256];
	if (code == STILL_ACTIVE)
	{
		wsprintf(buf, TEXT("살아있다.[code : %d]"), code);
	}
	else
	{
		wsprintf(buf, TEXT("죽었다..[code : %d]"), code);
	
	}
	SetDlgItemText(hDlg, IDC_EDIT4,buf);
}

void ui_FindName(HWND hDlg, TCHAR *name)
{
	
	OPENFILENAME OFN;
	TCHAR str[300];
	TCHAR lpstrFile[MAX_PATH] = TEXT("");
	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hDlg;
	OFN.lpstrFilter = TEXT("실행 파일(*.exe)\0*.exe\0 모든 파일(*.*)\0*.*\0");
	OFN.lpstrFile = name;
	OFN.nMaxFile = MAX_PATH;
	if (GetOpenFileName(&OFN) != 0) {

		
	/*	wsprintf(str, TEXT("%s 파일을 선택했습니다."), name);
		MessageBox(hDlg, str, TEXT("파일 열기 성공"), MB_OK);*/
	}
}

void ui_ComboBoxPrint(HWND hDlg, TCHAR * name)
{
	SetWindowText(g_hCombo, name);
}
