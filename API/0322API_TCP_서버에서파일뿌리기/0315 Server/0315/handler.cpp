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
	//�����ư
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
		return TRUE; // 1:1��� ������ ���Ͽ�
	}
	else if (*p == PACK_MINMEMBER)
	{
		ADDMEMBER *p = (ADDMEMBER*)buf;
		OnRecvMinMember(p);

	}
	else if (*p == PACK_LOGIN)
	{
		LOGIN *p = (LOGIN*)buf;
		OnRecvLogin(p); // 1:�� ���
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
	if (wbcon_InsertMember(mem) == TRUE) //���� ���� //1
	{
		ui_MemberPrintALL(wbcon_GetMemberList()); // ����� �ϱ����� wbcon���� ����Ʈ�� �޶�� �Ѵ�...(�ּҰ�) //2
		wsprintf(buf, TEXT("[ȸ�����Լ���]:%s,%s,%s\n"), mem->name, mem->id, mem->pw);
	
		mem->flag = ACK_ADDMEMBER_S;
	}
	else //���� ����
	{
		wsprintf(buf, TEXT("[ȸ�����Խ���]:%s,%s,%s\n"), mem->name, mem->id, mem->pw);
		mem->flag = ACK_ADDMEMBER_F;
	}
	ui_LogMessage(buf); //3

}

void OnRecvMinMember(ADDMEMBER *mem)
{
	TCHAR buf[256];
	if (wbcon_DeleteMember(mem) == TRUE) //���� ����
	{
		ui_MemberPrintALL(wbcon_GetMemberList()); //����Ʈ�� �ٽ� ���
		wsprintf(buf, TEXT("[ȸ��Ż�𼺰�]:%s\n"), mem->id);

		mem->flag = ACK_MINMEMBER;
	}
	ui_LogMessage(buf);
}

void OnRecvLogin(LOGIN *login)
{
	TCHAR buf[256];
	if (wbcon_CheckLogin(login) == TRUE) //üũ ����
	{
		ui_MemberPrintALL(wbcon_GetMemberList()); 
		wsprintf(buf, TEXT("[�α��μ���]:%s,%s\n"), login->id, login->pw); //pw�� �̸��� ��Ƽ�..

		login->flag = ACK_LOGIN_S;
		_tcscpy_s(login->pw, wbcon_GetName(login/*login->id, login->pw*/)); // �����̳ʿ��� ip/pw�� ������ �ش�Ǵ� �̸��� �޾ƿ´�. �׸��� �� �̸��� pw�� ���� ��..(��������)
	}
	else //üũ ����
	{
		wsprintf(buf, TEXT("[�α��ν���]:%s,%s\n"), login->id, login->pw);
		login->flag = ACK_ADDMEMBER_F;
	}
	ui_LogMessage(buf);
}

void OnRecvLogout(LOGIN *login)
{
	TCHAR buf[256];
	if (wbcon_CheckLogout(login) == TRUE) //üũ ����
	{
		ui_MemberPrintALL(wbcon_GetMemberList());
		wsprintf(buf, TEXT("[�α׾ƿ�����]:%s,%s\n"), login->id, login->pw); //pw�� �̸��� ��Ƽ�..
		login->flag = ACK_LOGOUT;
	}
	ui_LogMessage(buf);
}

void OnRecvShortMessage(SHORTMESSAGE *msg)
{
	TCHAR buf[256];
	wsprintf(buf, TEXT("[�޽���]:%s\n"), msg->msg);
	ui_LogMessage(buf);
	msg->flag = ACK_SHORTMESSAGE;
}

void OnRecvCodeMessage(CODEMESSAGE *msg)
{
	ui_LogMessage(TEXT("CODEMESSAGE����...."));
	msg->flag = ACK_CODEMESSAGE;
}


void OnClientLogMessage(int flag, char* ip, int port)
{
	TCHAR buf[256];
	wchar_t w_ip[250];

	MultiByteToWideChar(CP_ACP, 0, ip, -1, w_ip, 250);

	if (flag == 1)
		wsprintf(buf, TEXT("Ŭ���̾�Ʈ ����(%s:%d)"), w_ip, port);
	else if (flag == 0)
		wsprintf(buf, TEXT("Ŭ���̾�Ʈ ����(%s:%d)"), w_ip, port);
	ui_LogMessage(buf);
}