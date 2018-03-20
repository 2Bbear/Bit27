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
	//ȸ������
	if (*p == PACK_ADDMEMBER)
	{
		ADDMEMBER *p = (ADDMEMBER*)buf;
		OnRecvMember(p);
		return TRUE;
	}
	//�α���
	else if (*p == PACK_LOGIN)
	{
		LOGIN *p = (LOGIN*)buf;
		OnRecvLogin(p);
	}
	//�α׾ƿ�
	else if (*p == PACK_LOGOUT)
	{
		LOGIN *p = (LOGIN*)buf;
		OnRecvLogOunt(p);
	}
	//ȸ�� Ż��
	else if (*p == PACK_UNREGISTER)
	{
		LOGIN *p = (LOGIN*)buf;
		OnRecvUnregister(p);
	}
	//�޼���
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

	//���ڿ� ����
	_tcscpy(buf, msg->msg);
	//ACK �޼��� �� ����
	msg->flag = ACK_PACK_SHORTMESSAGE_S;

	//������ ���
	ui_LogMessage(buf);
}
void OnRecvUnregister(LOGIN * login)
{
	TCHAR buf[256];


	//��ȯ�� �̸� ����
	TCHAR tempName[20];
	_tcscpy(tempName, wbcon_GetName(login));
	//���� �α� �ƿ� ��Ű�� ������....

	//üũ ����
	if (wbcon_CheckUnregister(login) == TRUE)
	{
		//����Ʈ�����̳� ����
		ui_MemberPrintALL(wbcon_GetMemberList());
		//ȭ�����
		wsprintf(buf, TEXT("[ȸ��Ż�� ����] : %s,%s\n"), login->id, login->pw);
		//ACK �޼��� �� ����
		login->flag = ACK_UNREGISTER_S;
		_tcscpy_s(login->pw, tempName);//???
	}
	//üũ ����
	else
	{
		wsprintf(buf, TEXT("[ȸ��Ż�� ����] : %s,%s\n"), login->id, login->pw);
		//ACK �޼��� ����
		login->flag = ACK_UNREGISTER_F;
	}
	ui_LogMessage(buf);
}
void OnRecvLogin(LOGIN * login)
{
	TCHAR buf[256];
	//üũ ����
	if (wbcon_CheckLogin(login) == TRUE)
	{
		//����Ʈ�����̳� ����
		ui_MemberPrintALL(wbcon_GetMemberList());
		//ȭ�����
		wsprintf(buf, TEXT("[�α��� ����] : %s,%s\n"), login->id, login->pw);
		//ACK �޼��� �� ����
		login->flag = ACK_LOGIN_S;
		//Ŭ���̾�Ʈ�� �̸����޿�
		_tcscpy_s(login->pw, wbcon_GetName(login));
	}
	//üũ ����
	else
	{
		wsprintf(buf, TEXT("[�α��� ����] : %s,%s\n"), login->id, login->pw);
		//ACK �޼��� ����
		login->flag = ACK_LOGIN_F;
	}
	ui_LogMessage(buf);

}
void OnRecvLogOunt(LOGIN * login)
{
	TCHAR buf[256];
	//üũ ����
	if (wbcon_CheckLogOut(login) == TRUE)
	{
		//����Ʈ�����̳� ����
		ui_MemberPrintALL(wbcon_GetMemberList());
		//ȭ�����
		wsprintf(buf, TEXT("[�α׾ƿ� ����] : %s,%s\n"), login->id, login->pw);
		//ACK �޼��� �� ����
		login->flag = ACK_LOGOUT_S;
		_tcscpy_s(login->pw, wbcon_GetName(login));//???
	}
	//üũ ����
	else
	{
		wsprintf(buf, TEXT("[�α׾ƿ� ����] : %s,%s\n"), login->id, login->pw);
		//ACK �޼��� ����
		login->flag = ACK_LOGOUT_F;
	}
	ui_LogMessage(buf);
}

void OnRecvMember(ADDMEMBER *mem)
{
	TCHAR buf[256];
	//���� �� ���强��
	if (wbcon_InsertMember(mem) == TRUE)
	{
		//����Ʈ�����̳� ����
		ui_MemberPrintALL(wbcon_GetMemberList());
		//ȭ�����
		wsprintf(buf, TEXT("[ȸ������ ����] : %s,%s,%s\n"), mem->name, mem->id, mem->pw);
		//ACK �޼��� �� ����
		mem->flag = ACK_ADDMEMBER_S;
	}
	//���� ����
	else
	{
		wsprintf(buf, TEXT("[ERROR :: ȸ������ ����]"));
		//ACK �޼��� ����
		mem->flag = ACK_ADDMEMBER_F;
	}
	ui_LogMessage(buf);

	//ȭ�����
	
}

//void OnRecvEllipse(ELLIPSEPRINT *login)
//{
//	TCHAR buf[256];
//	wsprintf(buf, TEXT("[Ÿ  ��]:%d,%d,%d\n"), login->x, login->y, login->width);
//	ui_LogMessage(buf);
//}
//
//void OnRecvShortMessage(STRINGEPRINT *msg)
//{
//	TCHAR buf[256];
//	wsprintf(buf, TEXT("[���ڿ�]:%d,%d,%s\n"), msg->x, msg->y, msg->str);
//	ui_LogMessage(buf);
//}

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