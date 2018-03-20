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
	//회원가입
	if (*p == PACK_ADDMEMBER)
	{
		ADDMEMBER *p = (ADDMEMBER*)buf;
		OnRecvMember(p);
		return TRUE;
	}
	//로그인
	else if (*p == PACK_LOGIN)
	{
		LOGIN *p = (LOGIN*)buf;
		OnRecvLogin(p);
	}
	//로그아웃
	else if (*p == PACK_LOGOUT)
	{
		LOGIN *p = (LOGIN*)buf;
		OnRecvLogOunt(p);
	}
	//회원 탈퇴
	else if (*p == PACK_UNREGISTER)
	{
		LOGIN *p = (LOGIN*)buf;
		OnRecvUnregister(p);
	}
	//메세지
	else if (*p == PACK_SHORTMESSAGE)
	{
		SHORTMESSAGE *msg = (SHORTMESSAGE*)buf;
		OnRecvShortMessage(msg);
	}
	return FALSE;
}
void OnRecvShortMessage(SHORTMESSAGE * msg)
{
	TCHAR buf[256];

	//문자열 복사
	_tcscpy(buf, msg->msg);
	//ACK 메세지 재 조정
	msg->flag = ACK_PACK_SHORTMESSAGE_S;

	//오른쪽 출력
	ui_LogMessage(buf);
}
void OnRecvUnregister(LOGIN * login)
{
	TCHAR buf[256];


	//반환용 이름 저장
	TCHAR tempName[20];
	_tcscpy(tempName, wbcon_GetName(login));
	//강제 로그 아웃 시키고 싶은데....

	//체크 성공
	if (wbcon_CheckUnregister(login) == TRUE)
	{
		//리스트컨테이너 갱신
		ui_MemberPrintALL(wbcon_GetMemberList());
		//화면출력
		wsprintf(buf, TEXT("[회원탈퇴 성공] : %s,%s\n"), login->id, login->pw);
		//ACK 메세지 재 조정
		login->flag = ACK_UNREGISTER_S;
		_tcscpy_s(login->pw, tempName);//???
	}
	//체크 실패
	else
	{
		wsprintf(buf, TEXT("[회원탈퇴 실패] : %s,%s\n"), login->id, login->pw);
		//ACK 메세지 조정
		login->flag = ACK_UNREGISTER_F;
	}
	ui_LogMessage(buf);
}
void OnRecvLogin(LOGIN * login)
{
	TCHAR buf[256];
	//체크 성공
	if (wbcon_CheckLogin(login) == TRUE)
	{
		//리스트컨테이너 갱신
		ui_MemberPrintALL(wbcon_GetMemberList());
		//화면출력
		wsprintf(buf, TEXT("[로그인 성공] : %s,%s\n"), login->id, login->pw);
		//ACK 메세지 재 조정
		login->flag = ACK_LOGIN_S;
		//클라이언트에 이름전달용
		_tcscpy_s(login->pw, wbcon_GetName(login));
	}
	//체크 실패
	else
	{
		wsprintf(buf, TEXT("[로그인 실패] : %s,%s\n"), login->id, login->pw);
		//ACK 메세지 조정
		login->flag = ACK_LOGIN_F;
	}
	ui_LogMessage(buf);

}
void OnRecvLogOunt(LOGIN * login)
{
	TCHAR buf[256];
	//체크 성공
	if (wbcon_CheckLogOut(login) == TRUE)
	{
		//리스트컨테이너 갱신
		ui_MemberPrintALL(wbcon_GetMemberList());
		//화면출력
		wsprintf(buf, TEXT("[로그아웃 성공] : %s,%s\n"), login->id, login->pw);
		//ACK 메세지 재 조정
		login->flag = ACK_LOGOUT_S;
		_tcscpy_s(login->pw, wbcon_GetName(login));//???
	}
	//체크 실패
	else
	{
		wsprintf(buf, TEXT("[로그아웃 실패] : %s,%s\n"), login->id, login->pw);
		//ACK 메세지 조정
		login->flag = ACK_LOGOUT_F;
	}
	ui_LogMessage(buf);
}

void OnRecvMember(ADDMEMBER *mem)
{
	TCHAR buf[256];
	//저장 및 저장성공
	if (wbcon_InsertMember(mem) == TRUE)
	{
		//리스트컨테이너 갱신
		ui_MemberPrintALL(wbcon_GetMemberList());
		//화면출력
		wsprintf(buf, TEXT("[회원가입 성공] : %s,%s,%s\n"), mem->name, mem->id, mem->pw);
		//ACK 메세지 재 조정
		mem->flag = ACK_ADDMEMBER_S;
	}
	//저장 실패
	else
	{
		wsprintf(buf, TEXT("[ERROR :: 회원가입 실패]"));
		//ACK 메세지 조정
		mem->flag = ACK_ADDMEMBER_F;
	}
	ui_LogMessage(buf);

	//화면출력
	
}

//void OnRecvEllipse(ELLIPSEPRINT *login)
//{
//	TCHAR buf[256];
//	wsprintf(buf, TEXT("[타  원]:%d,%d,%d\n"), login->x, login->y, login->width);
//	ui_LogMessage(buf);
//}
//
//void OnRecvShortMessage(STRINGEPRINT *msg)
//{
//	TCHAR buf[256];
//	wsprintf(buf, TEXT("[문자열]:%d,%d,%s\n"), msg->x, msg->y, msg->str);
//	ui_LogMessage(buf);
//}

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