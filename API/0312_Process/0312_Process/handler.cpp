#include"std.h"


extern vector< PROINFO* >g_prolist;

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	//프로세스생성-확인
	case IDOK:
	{
		OnCheck(hDlg);
		return TRUE;
	}
	//Check 버튼
	case IDC_BUTTON2:
	{
		OnGetExitCode(hDlg);
		return TRUE;
	}
	//종료 버튼
	case IDC_BUTTON3:
	{
	
		OnExitProcess(hDlg);
		return TRUE;
	}
	//찾아보기 버튼
	case IDC_BUTTON1:
	{
		OnFindName(hDlg);
		return TRUE;
	}
	case IDC_COMBO1:
	{
		if (HIWORD(wParam)==CBN_SELCHANGE)
		{
			OnComboBoxSelChange(hDlg);
		}
		return TRUE;
	}
	case IDCANCEL:
	{
		EndDialog(hDlg, IDCANCEL);	return 0;
	}

	}
	return true;
	
}
BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	ui_GetHandle(hDlg); 
	return TRUE;
}
BOOL OnExitProcess(HWND hDlg)
{
	HANDLE h = ui_GetProcessHandle(hDlg);
	proc_ExitProcess(h);
	int code = proc_GetExitCodeProcess(h);
	ui_ExitCodePrint(hDlg, code);

	return 0;
}
BOOL OnFindName(HWND hDlg)
{
	TCHAR name[256] = {'\0'};
	ui_FindName(hDlg,name);
	ui_SetComboBoxAddProcessName(name);
	ui_ComboBoxPrint(hDlg,name);
	return 0;
}
BOOL OnComboBoxSelChange(HWND hDlg)
{
	int idx= ui_ComboBoxSelChange(hDlg);
	//해당 위치에 있는 문자 값을 가져오기
	PROINFO* p = g_prolist[idx];
	//static control에 출력 할 수 있도록 메세지 전달
	ui_ProInfoPrint(hDlg,p);

	return 0;
}
BOOL OnGetExitCode(HWND hDlg)
{
	HANDLE h=ui_GetProcessHandle(hDlg);
	int code = proc_GetExitCodeProcess(h);
	ui_ExitCodePrint(hDlg,code);
	
	return 0;
}
void OnCheck(HWND hDlg)
{
	//해당 위치에 있는 문자 값을 가져오기
	TCHAR buf[50];
	//텍스트 가져오기
	ui_GetProcessName(buf);
	//텍스트 콤보 박스에 저장하기
	ui_SetComboBoxAddProcessName(buf);
	//텍스트에 맞는 프로세스 실행
	proc_CreateProcess(buf);
	//프로세스의 정보 가져오기
	//프로세스의 정보 저장하기
	PROINFO *pInfo = proc_CreateProcess(buf);
	g_prolist.push_back(pInfo);

	ui_ProInfoPrint(hDlg, g_prolist[g_prolist.size() - 1]);
	

	//MessageBox(NULL,buf,TEXT(""),MB_OK);
	
	//현재 어디가 선택되어 있는지 확인
	//int idx = SendMessage(g_hComboBox1, CB_GETCURSEL, 0, 0);
	//
	//SendMessage(g_hComboBox1, CB_GETLBTEXT, idx, LPARAM(buf));
	////static control에 메세지 보내기
	//SetWindowText(g_hStatic2, (LPCWSTR)buf);//대화창 내용을 초기화 하는 함수
}
