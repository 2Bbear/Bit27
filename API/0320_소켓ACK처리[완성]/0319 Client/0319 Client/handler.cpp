//handler.cpp

#include "std.h"
#define SERVER_IP TEXT("192.168.0.52")
#define SERVER_PORT 9000

#define FILESERVER_IP TEXT("192.168.0.52")
#define FILESERVER_PORT 8000


BOOL g_IsLogin = FALSE; //현재 자신이 로그인된 상태인지 확인하는 상태값
HWND g_hDlg;

BOOL  OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	g_hDlg = hDlg;
	ui_InitControl(hDlg);

	//서버 접속 바로 실행
	if (wbnet_StartClient(SERVER_IP, SERVER_PORT) == FALSE) //접속 실패 했을 때
	{
		MessageBox(NULL,TEXT("서버 접속 실패"),TEXT("알림"),MB_OK);
		SendMessage(hDlg, WM_CLOSE, 0, 0);
	}
	//서버 접속 바로 실행
	if (wbFile_StartClient(SERVER_IP, SERVER_PORT) == FALSE) //접속 실패 했을 때
	{
		MessageBox(NULL, TEXT("서버 접속 실패"), TEXT("알림"), MB_OK);
		SendMessage(hDlg, WM_CLOSE, 0, 0);
	}


	return true;
}


BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{

	//전송1:회원가입
	case IDC_BUTTON3:	OnAddMember(hDlg);				return 0;
	//전송2:로그인
	case IDC_BUTTON4:	OnLogin(hDlg);					return 0;
		//전송 : 코드 전송
	case IDC_BUTTON_CODE:
	{
		OnSendCode(hDlg);
		return 0;
	}
	//전송3:전송
	case IDC_BUTTON2:	OnSendData(hDlg);				return 0;
	//전송4: 로그아웃
	case IDC_BUTTON6:	OnLogout(hDlg);					return 0;
	//전송5: 회원탈퇴
	case IDC_BUTTON5:	OnMinMember(hDlg);				return 0;
	//전송6  파일전송
	case IDC_BUTTON8:
	{
		OnFileSend(hDlg);
		return 0;
	}
	//파일 열기
	case IDC_BUTTON_OPENFILE:
	{
		OnFileOpen(hDlg);
		return 0;
	}
	case IDCANCEL: 
	{
		wbFile_StopClient();
		wbnet_StopClient();
		EndDialog(hDlg, IDCANCEL);
		return 0;
	}
	}
	return TRUE;
}
void OnFileSend(HWND hDlg)
{
	TCHAR path[256] = TEXT("");
	TCHAR name[50] = TEXT("");
	ui_GetFilePathOrName(hDlg, path, name);
	wbFile_SendMessage(path,name);
}
void OnFileOpen(HWND hDlg)
{
	TCHAR path[256]=TEXT("");
	TCHAR name[50] = TEXT("");

	ui_GetFileInfo(hDlg,path,name);
}
void OnSendCode(HWND hDlg)
{
	TCHAR msg[500];
	ui_GetSendCodeMessage(hDlg,msg);
	CODEMESSAGE packet = pack_SetCodeMessage(msg);
	wbnet_SendMessage((TCHAR*)&packet, sizeof(CODEMESSAGE));
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
	ADDMEMBER packet = pack_SetMinMember(TEXT(""), id, pw);
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

void OnSendData(HWND hDlg)
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

void OnLogMessage(TCHAR *msg)
{
	ui_LogMessage(msg);
}

void OnMessage(char* buf, int nRead)
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
			ui_EnableButton(TRUE, TRUE, TRUE, FALSE);
			g_IsLogin = TRUE; //로그인 확인... 그 이후의 메시지는 모두 출력됨
			SetWindowText(g_hDlg, p->pw);
		
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
			ui_EnableButton(FALSE, FALSE, FALSE, TRUE);
			g_IsLogin = FALSE;

		}
			

		TCHAR buf[50];
		wsprintf(buf, TEXT("%s님이 로그아웃하셨습니다."), p->pw);
		ui_LogMessage(buf);
	
		
	}
	else if (*p == ACK_CODEMESSAGE)
	{
		if (g_IsLogin == FALSE)
			return;

		CODEMESSAGE *msg = (CODEMESSAGE*)buf;
		ui_PrintCodeLine(msg->msg);
		//ui_LogMessage(msg->msg);
	}
}