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

BOOL OnMessage(char* buf, int nRead)//서버에게보임
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

	//계좌 관련 Msg===============================================
	else if (*p == PACK_ADDACCOUNT)
	{
		ADDACCOUNT *p = (ADDACCOUNT*)buf;
		OnRecvAddAccount(p);
	}
	else if (*p == PACK_DELACCOUNT)
	{
		ADDACCOUNT *p = (ADDACCOUNT*)buf;
		OnRecvDelAccount(p);
	}
	else if (*p == PACK_ADDMONEY)
	{
		ADDMONEY *p = (ADDMONEY*)buf;
		OnRecvAddMoney(p);
	}
	else if (*p == PACK_SUBMONEY)
	{
		SUBMONEY *p = (SUBMONEY*)buf;
		OnRecvSubMoney(p);
	}

	return FALSE;
}

void OnRecvMember(ADDMEMBER *mem) // 서버에게 보임
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
		wsprintf(buf, TEXT("[회원탈퇴성공]:%s,%s\n"), mem->id, mem->pw);

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
		_tcscpy_s(login->pw, wbcon_GetName(login));
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


// 계좌 recv msg ============================================
void OnRecvAddAccount(ADDACCOUNT* acc)
{
	TCHAR buf[256];
	if (wbcon_InsertAccount(acc) == TRUE) //계좌 저장 성공
	{
		//1. list뷰에 보여주기
		ui_AccountPrintALL(wbcon_GetAccountList());
		//2. 알림 msg 알려주기..
		wsprintf(buf, TEXT("[계좌생성성공]:%s=>%d,%d\n"), acc->id,acc->accnum, acc->balance);
		acc->flag = ACK_ADDACCOUNT_S;
	}
	else
	{
		wsprintf(buf, TEXT("[계좌생성실패]:%s=>%d,%d,%s\n"), acc->id, acc->accnum, acc->balance, acc->date);
		acc->flag = ACK_ADDACCOUNT_F;
	}
	ui_LogMessage(buf);
}

void OnRecvDelAccount(ADDACCOUNT* acc)
{
	TCHAR buf[256];
	if (wbcon_DeleteAccount(acc) == TRUE) //삭제 성공
	{
		ui_AccountPrintALL(wbcon_GetAccountList());
		wsprintf(buf, TEXT("[계좌삭제성공]:%s=>%d,%d\n"), acc->id, acc->accnum, acc->balance);

		acc->flag = ACK_DELACCOUNT_S;
	}
	else
	{
		wsprintf(buf, TEXT("[계좌삭제실패]:%s=>%d,%d\n"), acc->id, acc->accnum, acc->balance);
		acc->flag = ACK_DELACCOUNT_F;
	}
	ui_LogMessage(buf);
}

void OnRecvAddMoney(ADDMONEY* money)
{
	ACCOUNT* acc;
	TCHAR buf[256];
	if (is_AccNumCheck(money->accnum) == FALSE) // 계좌일치
	{
		acc = wbcon_GetAccount(money);
		wbcon_AddMoney(money, acc);//1. vector에서 add연산..
		ui_AccountPrintALL(wbcon_GetAccountList());//2. list뷰 출력
		wsprintf(buf, TEXT("[입금성공]:계좌:%d,입금액:%d\n"),money->accnum, money->money);

		money->flag = ACK_ADDMONEY;
	}
	ui_LogMessage(buf);//3.log출력
}

void OnRecvSubMoney(SUBMONEY* money)
{
	ACCOUNT* acc;
	TCHAR buf[256];
	if (is_AccNumCheck(money->accnum) == FALSE) // 계좌일치
	{
		ADDMONEY* m = (ADDMONEY*)money; //함수 재사용할려고..형변환(어짜피 구조체 타입 같으니까)
		acc = wbcon_GetAccount(m);
		if (wbcon_SubPossible(acc, money) == TRUE)//1. 뺄수 있는가? <0?
		{	
			wbcon_SubMoney(money, acc);//2. 연산
			ui_AccountPrintALL(wbcon_GetAccountList());//3. list뷰
			wsprintf(buf, TEXT("[출금성공]:계좌:%d,출금액:%d\n"), money->accnum, money->money);

			money->flag = ACK_SUBMONEY_S;
		}
		else
		{
			//연산실패
			wsprintf(buf, TEXT("[출금실패]:계좌:%d,출금액:%d\n"), money->accnum, money->money);
			money->flag = ACK_SUBMONEY_F;
		}
		ui_LogMessage(buf);	//4. log
	}
	
}