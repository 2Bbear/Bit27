//handler.cpp

#include "std.h"

//세상에서 제일 싫어하는 전역변수들
HWND g_hDlg;

//
//현재 자신의 상태
BOOL g_IsLogin = FALSE;
TCHAR g_CurrentID[20];
TCHAR g_CurrentName[20];
TCHAR g_CurrentPW[20];
//

//

void InitCurrentAccount()
{
	printf("InitCurrentAccount\n");
	g_IsLogin = FALSE;
	printf("current IsLogin Value %d\n", g_IsLogin);
	_tcscpy_s(g_CurrentID,TEXT(""));
	_tcscpy_s(g_CurrentName, TEXT(""));
	_tcscpy_s(g_CurrentPW, TEXT(""));
	
}

void SetCurrentAccountName(TCHAR * _name)
{
	printf("SetCurrentAccountName\n");
	_tcscpy_s(g_CurrentName,_name);
	
	char buf[50];
	WideCharToMultiByte(CP_ACP, 0, g_CurrentName, -1, buf, 50, NULL, NULL);
	printf("current name : %s\n",buf);
}

void SetCurrentAccountID(TCHAR * _id)
{
	printf("SetCurrentAccountID\n");
	_tcscpy_s(g_CurrentID, _id);

	char buf[50];
	WideCharToMultiByte(CP_ACP, 0, g_CurrentID, -1, buf, 50, NULL, NULL);
	printf("current id : %s\n", buf);
}

void SetCurrentAccountPW(TCHAR * _pw)
{
	printf("SetCurrentAccountPW\n");
	_tcscpy_s(g_CurrentPW, _pw);

	char buf[50];
	WideCharToMultiByte(CP_ACP, 0, g_CurrentPW, -1, buf, 50, NULL, NULL);
	printf("current pw : %s\n", buf);
}

BOOL  OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	InitCurrentAccount();
	g_hDlg = hDlg;
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
	//전송2_2: 로그 아웃
	case IDC_BUTTON_LOGOUT: OnLogOut(hDlg);				return 0;
	//전송3:전송
	case IDC_BUTTON2:	OnSendData(hDlg);				return 0;
	//전송4:회원탈퇴
	case IDC_BUTTON_UNREGISTER: OnUnregister(hDlg);			 return 0;
	case IDCANCEL: 
	{
		OnLogOut(hDlg);
		EndDialog(hDlg, IDCANCEL);		
		return 0;
	}
	}
	return TRUE;
}
void OnSendData(HWND hDlg)
{
	if (g_IsLogin == TRUE)
	{
		TCHAR msg[80];
		ui_GetSendMessage(hDlg, msg);
		//메세지 재 가공 id붙이기
		TCHAR temp[100];
		wsprintf(temp,TEXT("%s : %s"), g_CurrentID,msg);
		//패키징
		SHORTMESSAGE shortmessage=pack_SetShortMessage(temp);
		//전송
		wbnet_SendMessage((TCHAR *)&shortmessage, sizeof(SHORTMESSAGE));
	}
	
}
void OnUnregister(HWND hDlg)
{
	if (g_IsLogin == TRUE)
	{
		LOGIN packet = pack_SetUnregister(g_CurrentID, g_CurrentPW, &g_IsLogin);
		wbnet_SendMessage((TCHAR*)&packet, sizeof(LOGIN));
	}
}
void OnLogOut(HWND hDlg)
{
	if (g_IsLogin==TRUE)
	{
		LOGIN packet = pack_SetLogOut(g_CurrentID, g_CurrentPW,&g_IsLogin);
		wbnet_SendMessage((TCHAR*)&packet, sizeof(LOGIN));
	}

	
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

void OnLogin(HWND hDlg)
{
	if (g_IsLogin == FALSE)
	{
		TCHAR id[20];
		TCHAR pw[20];

		ui_GetLogin(hDlg, id, pw);
		//현재 계정 정보에 저장
		SetCurrentAccountPW(pw);
		SetCurrentAccountID(id);
		//
		LOGIN packet = pack_SetLogin(id, pw);
		wbnet_SendMessage((TCHAR*)&packet, sizeof(LOGIN));
	}
	
}



void OnLogMessage(TCHAR *msg)
{
	ui_LogMessage(msg);
}

void OnMessage(char* buf, int nRead)
{
	int *p = (int*)buf;
	//회원가입
	if (*p == ACK_ADDMEMBER_S)
	{
		ADDMEMBER *p = (ADDMEMBER*)buf;
		ui_LogMessage(TEXT("회원가입성공"));

	}
	else if (*p == ACK_ADDMEMBER_F)
	{
		ui_LogMessage(TEXT("회원가입실패"));
	}
	//로그인
	else if (*p == ACK_LOGIN_S)
	{
		LOGIN *p = (LOGIN*)buf;
		//
		//현재 계정 정보에 저장
		SetCurrentAccountName(p->pw);
		
		//
		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg,id,pw);
	
		if (_tcscmp(id,p->id)==0)
		{
			g_IsLogin = TRUE;
		}
		if (g_IsLogin==FALSE)
		{
			return;
		}
		TCHAR buf[50];
		wsprintf(buf, TEXT("%s 님이 로그인하셨습니다."), p->pw);
		ui_LogMessage(buf);


		printf("current IsLogin Value %d\n",g_IsLogin);
	}
	else if(*p == ACK_LOGIN_F)
	{
		LOGIN *p = (LOGIN*)buf;
		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg, id, pw);
		if (_tcscmp(id, p->id) == 0)
		{
			ui_LogMessage(TEXT("로그인 실패"));
		}
	}
	//메세지 돌려받음
	else if (*p == ACK_PACK_SHORTMESSAGE_S)
	{
		if (g_IsLogin==TRUE)
		{
			printf("메세지 돌려받았어");
			SHORTMESSAGE *msg = (SHORTMESSAGE*)buf;
			ui_LogMessage(msg->msg);
		}
		
	}
	//로그아웃
	else if (*p == ACK_LOGOUT_S)
	{
		LOGIN *p = (LOGIN*)buf;

		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg, id, pw);
		//들어온 값이 현재 내 아이디가 맞는지 검사
		if (_tcscmp(id, p->id) == 0)
		{
			g_IsLogin = FALSE;
		}
		if (g_IsLogin == TRUE)
		{
			
		}
		TCHAR buf[50];
		wsprintf(buf, TEXT("%s 님이 로그아웃하셨습니다."), p->pw);
		ui_LogMessage(buf);


		printf("current IsLogin Value %d\n", g_IsLogin);
	}
	else if (*p == ACK_LOGOUT_F)
	{
		LOGIN *p = (LOGIN*)buf;
		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg, id, pw);
		if (_tcscmp(id, p->id) == 0)
		{
			ui_LogMessage(TEXT("로그아웃 실패"));
		}
	}
	//회원 탈퇴
	else if (*p == ACK_UNREGISTER_S)
	{
		LOGIN *p = (LOGIN*)buf;

		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg, id, pw);
		//들어온 값이 현재 내 아이디가 맞는지 검사
		if (_tcscmp(id, p->id) == 0)
		{
			g_IsLogin = FALSE;
		}
		if (g_IsLogin == TRUE)
		{
			return;
		}
		TCHAR buf[50];
		wsprintf(buf, TEXT("%s 님이 회원 탈퇴하셨습니다."), p->pw);
		ui_LogMessage(buf);


		printf("current IsLogin Value %d\n", g_IsLogin);
	}
	else if (*p == ACK_UNREGISTER_F)
	{
		LOGIN *p = (LOGIN*)buf;
		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg, id, pw);
		if (_tcscmp(id, p->id) == 0)
		{
			ui_LogMessage(TEXT("회원탈퇴 실패"));
		}
	}
	
}