//handler.cpp

#include "std.h"

//���󿡼� ���� �Ⱦ��ϴ� ����������
HWND g_hDlg;

//
//���� �ڽ��� ����
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
	//����
	case IDC_BUTTON1:	OnConnect(hDlg);				return 0;
	//����1:ȸ������
	case IDC_BUTTON3:	OnAddMember(hDlg);				return 0;
	//����2:�α���
	case IDC_BUTTON4:	OnLogin(hDlg);					return 0;
	//����2_2: �α� �ƿ�
	case IDC_BUTTON_LOGOUT: OnLogOut(hDlg);				return 0;
	//����3:����
	case IDC_BUTTON2:	OnSendData(hDlg);				return 0;
	//����4:ȸ��Ż��
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
		//�޼��� �� ���� id���̱�
		TCHAR temp[100];
		wsprintf(temp,TEXT("%s : %s"), g_CurrentID,msg);
		//��Ű¡
		SHORTMESSAGE shortmessage=pack_SetShortMessage(temp);
		//����
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
			ui_SetButtonString(TEXT("��������"));
			bConnect = TRUE;
		}
	}
	else
	{
		wbnet_StopClient();
		ui_LogMessage(TEXT("���� ���� ����..."));
		ui_SetButtonString(TEXT("����"));
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
		//���� ���� ������ ����
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
	//ȸ������
	if (*p == ACK_ADDMEMBER_S)
	{
		ADDMEMBER *p = (ADDMEMBER*)buf;
		ui_LogMessage(TEXT("ȸ�����Լ���"));

	}
	else if (*p == ACK_ADDMEMBER_F)
	{
		ui_LogMessage(TEXT("ȸ�����Խ���"));
	}
	//�α���
	else if (*p == ACK_LOGIN_S)
	{
		LOGIN *p = (LOGIN*)buf;
		//
		//���� ���� ������ ����
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
		wsprintf(buf, TEXT("%s ���� �α����ϼ̽��ϴ�."), p->pw);
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
			ui_LogMessage(TEXT("�α��� ����"));
		}
	}
	//�޼��� ��������
	else if (*p == ACK_PACK_SHORTMESSAGE_S)
	{
		if (g_IsLogin==TRUE)
		{
			printf("�޼��� �����޾Ҿ�");
			SHORTMESSAGE *msg = (SHORTMESSAGE*)buf;
			ui_LogMessage(msg->msg);
		}
		
	}
	//�α׾ƿ�
	else if (*p == ACK_LOGOUT_S)
	{
		LOGIN *p = (LOGIN*)buf;

		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg, id, pw);
		//���� ���� ���� �� ���̵� �´��� �˻�
		if (_tcscmp(id, p->id) == 0)
		{
			g_IsLogin = FALSE;
		}
		if (g_IsLogin == TRUE)
		{
			
		}
		TCHAR buf[50];
		wsprintf(buf, TEXT("%s ���� �α׾ƿ��ϼ̽��ϴ�."), p->pw);
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
			ui_LogMessage(TEXT("�α׾ƿ� ����"));
		}
	}
	//ȸ�� Ż��
	else if (*p == ACK_UNREGISTER_S)
	{
		LOGIN *p = (LOGIN*)buf;

		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg, id, pw);
		//���� ���� ���� �� ���̵� �´��� �˻�
		if (_tcscmp(id, p->id) == 0)
		{
			g_IsLogin = FALSE;
		}
		if (g_IsLogin == TRUE)
		{
			return;
		}
		TCHAR buf[50];
		wsprintf(buf, TEXT("%s ���� ȸ�� Ż���ϼ̽��ϴ�."), p->pw);
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
			ui_LogMessage(TEXT("ȸ��Ż�� ����"));
		}
	}
	
}