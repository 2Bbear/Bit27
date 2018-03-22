//handler.cpp

#include "std.h"

BOOL OnInitDialog(HWND hDlg)
{
	ui_InitControl(hDlg);

	return true;
}


BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	//실행버튼
	case IDC_BUTTON1: OnStartServer(hDlg);      return 0;
	case IDCANCEL:	EndDialog(hDlg, IDCANCEL);	return 0;
	}
	return TRUE;
}


void OnStartServer(HWND hDlg)
{
	int port;
	port = ui_getPort(hDlg);
	wbnet_StartServer(port);
}


void OnLogMessage(TCHAR *msg)
{
	ui_LogMessage(msg);
}

BOOL OnMessage(char* buf, int nRead)
{
	int *p = (int*)buf;
	if (*p == PACK_ADDMEMBER)
	{
		ADDMEMBER *p = (ADDMEMBER*)buf;
		OnRecvMember(p);
		return TRUE; // 1:1통신 구조를 위하여
	}
	else if (*p == PACK_MINMEMBER)
	{
		ADDMEMBER *p = (ADDMEMBER*)buf;
		OnRecvMinMember(p);

	}
	else if (*p == PACK_LOGIN)
	{
		LOGIN *p = (LOGIN*)buf;
		OnRecvLogin(p); // 1:다 통신
	}
	else if (*p == PACK_LOGOUT)
	{
		LOGIN *p = (LOGIN*)buf;
		OnRecvLogout(p);
	}
	else if (*p == PACK_SHORTMESSAGE)
	{
		SHORTMESSAGE *msg = (SHORTMESSAGE*)buf;
		OnRecvShortMessage(msg);
	}
	else if (*p == PACK_CODEMESSAGE)
	{
		CODEMESSAGE *msg = (CODEMESSAGE*)buf;
		OnRecvCodeMessage(msg);
	}

	return FALSE;
}

void OnRecvMember(ADDMEMBER *mem)
{
	TCHAR buf[256];
	if (wbcon_InsertMember(mem) == TRUE) //저장 성공 //1
	{
		ui_MemberPrintALL(wbcon_GetMemberList()); // 출력을 하기위해 wbcon에게 리스트를 달라고 한다...(주소값) //2
		wsprintf(buf, TEXT("[회원가입성공]:%s,%s,%s\n"), mem->name, mem->id, mem->pw);
	
		mem->flag = ACK_ADDMEMBER_S;
	}
	else //저장 실패
	{
		wsprintf(buf, TEXT("[회원가입실패]:%s,%s,%s\n"), mem->name, mem->id, mem->pw);
		mem->flag = ACK_ADDMEMBER_F;
	}
	ui_LogMessage(buf); //3

}

void OnRecvMinMember(ADDMEMBER *mem)
{
	TCHAR buf[256];
	if (wbcon_DeleteMember(mem) == TRUE) //삭제 성공
	{
		ui_MemberPrintALL(wbcon_GetMemberList()); //리스트뷰 다시 출력
		wsprintf(buf, TEXT("[회원탈퇴성공]:%s\n"), mem->id);

		mem->flag = ACK_MINMEMBER;
	}
	ui_LogMessage(buf);
}

void OnRecvLogin(LOGIN *login)
{
	TCHAR buf[256];
	if (wbcon_CheckLogin(login) == TRUE) //체크 성공
	{
		ui_MemberPrintALL(wbcon_GetMemberList()); 
		wsprintf(buf, TEXT("[로그인성공]:%s,%s\n"), login->id, login->pw); //pw에 이름을 담아서..

		login->flag = ACK_LOGIN_S;
		_tcscpy_s(login->pw, wbcon_GetName(login/*login->id, login->pw*/)); // 컨테이너에게 ip/pw를 보내서 해당되는 이름을 받아온다. 그리고 그 이름을 pw에 담을 것..(프로토콜)
	}
	else //체크 실패
	{
		wsprintf(buf, TEXT("[로그인실패]:%s,%s\n"), login->id, login->pw);
		login->flag = ACK_ADDMEMBER_F;
	}
	ui_LogMessage(buf);
}

void OnRecvLogout(LOGIN *login)
{
	TCHAR buf[256];
	if (wbcon_CheckLogout(login) == TRUE) //체크 성공
	{
		ui_MemberPrintALL(wbcon_GetMemberList());
		wsprintf(buf, TEXT("[로그아웃성공]:%s,%s\n"), login->id, login->pw); //pw에 이름을 담아서..
		login->flag = ACK_LOGOUT;
	}
	ui_LogMessage(buf);
}

void OnRecvShortMessage(SHORTMESSAGE *msg)
{
	TCHAR buf[256];
	wsprintf(buf, TEXT("[메시지]:%s\n"), msg->msg);
	ui_LogMessage(buf);
	msg->flag = ACK_SHORTMESSAGE;
}

void OnRecvCodeMessage(CODEMESSAGE *msg)
{
	ui_LogMessage(TEXT("CODEMESSAGE수신...."));
	msg->flag = ACK_CODEMESSAGE;
}


void OnClientLogMessage(int flag, char* ip, int port)
{
	TCHAR buf[256];
	wchar_t w_ip[250];

	MultiByteToWideChar(CP_ACP, 0, ip, -1, w_ip, 250);

	if (flag == 1)
		wsprintf(buf, TEXT("클라이언트 접속(%s:%d)"), w_ip, port);
	else if (flag == 0)
		wsprintf(buf, TEXT("클라이언트 해제(%s:%d)"), w_ip, port);
	ui_LogMessage(buf);
}