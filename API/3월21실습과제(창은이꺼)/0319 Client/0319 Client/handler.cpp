//handler.cpp

#include "std.h"

BOOL g_IsLogin = FALSE; //현재 자신이 로그인된 상태인지 확인하는 상태값
HWND g_hDlg;
LOGIN g_Curinfo; //현재 로그인된 ID의 id,name을 가지고 있음

BOOL  OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	g_hDlg = hDlg;
	
	// 처음 초기화..
	g_Curinfo.flag = 0;
	_tcscpy_s(g_Curinfo.id, TEXT(""));
	_tcscpy_s(g_Curinfo.pw, TEXT(""));

	ui_InitControl(hDlg);

	return true;
}


BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	//연결
	case IDC_BUTTON1:	OnConnect(hDlg);				return 0;
	//전송1:회원가입
	case IDC_BUTTON3:	OnAddMember(hDlg);				return 0;
	//전송2:로그인
	case IDC_BUTTON4:	OnLogin(hDlg);					return 0;
	//전송3:전송
	case IDC_BUTTON2:	OnSendData(hDlg);				return 0;
	//전송4: 로그아웃
	case IDC_BUTTON6:	OnLogout(hDlg);					return 0;
	//전송5: 회원탈퇴
	case IDC_BUTTON5:	OnMinMember(hDlg);				return 0;
	//모달: 계좌관리
	case IDC_BUTTON7:	OnAccControl(hDlg);				return 0;
	case IDCANCEL:		EndDialog(hDlg, IDCANCEL);		return 0;
	}
	return TRUE;
}

void OnConnect(HWND hDlg)
{
	static BOOL bConnect = FALSE;

	if (bConnect == FALSE)
	{
		TCHAR ip[256];
		int port;
		ui_getAddress(hDlg, ip, &port);

		if (wbnet_StartClient(ip, port) == TRUE)
		{
			ui_SetButtonString(TEXT("연결해제"));
			bConnect = TRUE;
		}
	}
	else
	{
		wbnet_StopClient();
		ui_LogMessage(TEXT("서버 연결 해제..."));
		ui_SetButtonString(TEXT("연결"));
		bConnect = FALSE;
	}
}

void OnAddMember(HWND hDlg)
{
	TCHAR name[20];
	TCHAR id[20];
	TCHAR pw[20];
	ui_GetAddMember(hDlg, name, id, pw);
	ADDMEMBER packet = pack_SetAddMember(name, id, pw);
	wbnet_SendMessage((TCHAR*)&packet, sizeof(ADDMEMBER));
}

void OnMinMember(HWND hDlg)
{
	TCHAR name[20];
	TCHAR id[20];
	TCHAR pw[20];
	ui_GetMinMember(hDlg, name, id, pw);
	ADDMEMBER packet = pack_SetMinMember(name, id, pw);
	wbnet_SendMessage((TCHAR*)&packet, sizeof(ADDMEMBER));
}

void OnLogin(HWND hDlg)
{
	TCHAR id[20];
	TCHAR pw[20];

	ui_GetLogin(hDlg, id, pw);
	LOGIN packet = pack_SetLogiin(id, pw);
	wbnet_SendMessage((TCHAR*)&packet, sizeof(LOGIN));

	//static BOOL bLogin = FALSE;
	//if (bLogin == FALSE)
	//{
	//	ui_SetLoginButtonString(TEXT("로그인"));
	//	bLogin = TRUE;
	//	TCHAR id[20];
	//	TCHAR pw[20];
	//	ui_GetLogin(hDlg, id, pw);
	//	LOGIN packet = pack_SetLogiin(id, pw);
	//	wbnet_SendMessage((TCHAR*)&packet, sizeof(LOGIN));
	//	
	//}
	//else
	//{
	//	ui_SetLoginButtonString(TEXT("로그아웃"));
	//	bLogin = FALSE;
	//}
}

void OnSendData(HWND hDlg) // 서버한테 보임
{
	TCHAR msg[50];
	ui_GetSendMessage(hDlg, msg);
	SHORTMESSAGE packet = pack_SetShortMessage(msg);
	wbnet_SendMessage((TCHAR*)&packet, sizeof(SHORTMESSAGE));
}

void OnLogout(HWND hDlg)
{
	TCHAR id[20];
	TCHAR pw[20];

	ui_GetLogin(hDlg, id, pw);
	LOGIN packet = pack_SetLogout(id, pw);
	wbnet_SendMessage((TCHAR*)&packet, sizeof(LOGIN));
}

void OnAccControl(HWND hDlg)
{
	if (g_IsLogin == TRUE) //현재 로그인된 상태여야 뜰 수 있게..
	{
		//LOGIN  info = g_Curinfo;
		UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
			MAKEINTRESOURCE(IDD_DIALOG2),
			hDlg,		// 부모
			Acc_DlgProc, // 메세지 함수.
			(LPARAM)&g_Curinfo); // WM_INITDIALOG의 lParam로 전달된다.
		if (ret == IDOK)
		{

		}
	}
	else if (g_IsLogin == FALSE)
		MessageBox(hDlg, TEXT("로그인부터 하세요"), TEXT("Error"), MB_OK);

}

//msg======================================================================================
void OnLogMessage(TCHAR *msg)
{
	ui_LogMessage(msg);
}

void OnMessage(char* buf, int nRead) // 우리 클라이언트한테 보임
{
	int *p = (int*)buf;
	if (*p == ACK_ADDMEMBER_S)
	{
		ADDMEMBER *p = (ADDMEMBER*)buf;
		ui_LogMessage(TEXT("회원가입 성공"));

	}
	else if (*p == ACK_ADDMEMBER_F)
	{
		ui_LogMessage(TEXT("회원가입 실패"));

	}
	else if (*p == ACK_MINMEMBER)
	{
		ui_LogMessage(TEXT("회원탈퇴 성공"));
	}
	else if (*p == ACK_LOGIN_S)
	{
		  
		LOGIN *p = (LOGIN*)buf; //이름을 빼내야함.
		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg, id, pw);
		if (_tcscmp(id, p->id) == 0)
		{
			g_IsLogin = TRUE; //로그인 확인... 그 이후의 메시지는 모두 출력됨
			_tcscpy_s(g_Curinfo.id, p->id);
			_tcscpy_s(g_Curinfo.pw, p->pw); //계좌 관리에서 정보 이용하기 위해.. (현재 pw에 이름들어있음)
		}

		if (g_IsLogin == FALSE)
			return; //내가 로그인 하기전에 발생.. .. 다른사람이 로그인했을 때는 문자열 출력안됨..

		TCHAR buf[50];
		wsprintf(buf, TEXT("%s님이 로그인하셨습니다."), p->pw);
		ui_LogMessage(buf);
	}
	else if (*p == ACK_LOGIN_F)
	{
		LOGIN *p = (LOGIN*)buf;
		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg, id, pw);
		if (_tcscmp(id, p->id) == 0) //
			ui_LogMessage(TEXT("로그인 실패"));//이때만 출력

	}
	else if (*p == ACK_SHORTMESSAGE)
	{
		if (g_IsLogin == FALSE)
			return;

		SHORTMESSAGE *msg = (SHORTMESSAGE*)buf;
		ui_LogMessage(msg->msg);
	}

	else if (*p == ACK_LOGOUT)
	{
		LOGIN *p = (LOGIN*)buf; //이름을 빼내야함.
		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg, id, pw);
		if (_tcscmp(id, p->id) == 0)
		{
			g_IsLogin = FALSE;

			TCHAR buf[50];
			wsprintf(buf, TEXT("%s님이 로그아웃하셨습니다."), p->pw);
			ui_LogMessage(buf);
		}

	}

	//계좌 관련msg==============================================================
	else if (*p == ACK_ADDACCOUNT_S)
	{
		Acc_OnAddcount_s(buf);
	}
	else if (*p == ACK_ADDACCOUNT_F)
	{
		Acc_OnAddcount_f();
	}
	else if (*p == ACK_DELACCOUNT_S)
	{
		Acc_OnDelcount_s(buf);
	}
	else if (*p == ACK_DELACCOUNT_F)
	{
		Acc_OnDelcount_f();
	}
	else if (*p == ACK_ADDMONEY)
	{
		Acc_OnAddMoney(buf);
	}
	else if (*p == ACK_SUBMONEY_S)
	{
		Acc_OnSubMoney_s(buf);
	}
	else if (*p == ACK_SUBMONEY_F)
	{
		Acc_OnSubMoney_f();
	}
}