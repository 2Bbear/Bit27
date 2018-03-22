//handler.cpp

#include "std.h"

BOOL g_IsLogin = FALSE; //���� �ڽ��� �α��ε� �������� Ȯ���ϴ� ���°�
HWND g_hDlg;
LOGIN g_Curinfo; //���� �α��ε� ID�� id,name�� ������ ����

BOOL  OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	g_hDlg = hDlg;
	
	// ó�� �ʱ�ȭ..
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
	//����
	case IDC_BUTTON1:	OnConnect(hDlg);				return 0;
	//����1:ȸ������
	case IDC_BUTTON3:	OnAddMember(hDlg);				return 0;
	//����2:�α���
	case IDC_BUTTON4:	OnLogin(hDlg);					return 0;
	//����3:����
	case IDC_BUTTON2:	OnSendData(hDlg);				return 0;
	//����4: �α׾ƿ�
	case IDC_BUTTON6:	OnLogout(hDlg);					return 0;
	//����5: ȸ��Ż��
	case IDC_BUTTON5:	OnMinMember(hDlg);				return 0;
	//���: ���°���
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
	//	ui_SetLoginButtonString(TEXT("�α���"));
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
	//	ui_SetLoginButtonString(TEXT("�α׾ƿ�"));
	//	bLogin = FALSE;
	//}
}

void OnSendData(HWND hDlg) // �������� ����
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
	if (g_IsLogin == TRUE) //���� �α��ε� ���¿��� �� �� �ְ�..
	{
		//LOGIN  info = g_Curinfo;
		UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
			MAKEINTRESOURCE(IDD_DIALOG2),
			hDlg,		// �θ�
			Acc_DlgProc, // �޼��� �Լ�.
			(LPARAM)&g_Curinfo); // WM_INITDIALOG�� lParam�� ���޵ȴ�.
		if (ret == IDOK)
		{

		}
	}
	else if (g_IsLogin == FALSE)
		MessageBox(hDlg, TEXT("�α��κ��� �ϼ���"), TEXT("Error"), MB_OK);

}

//msg======================================================================================
void OnLogMessage(TCHAR *msg)
{
	ui_LogMessage(msg);
}

void OnMessage(char* buf, int nRead) // �츮 Ŭ���̾�Ʈ���� ����
{
	int *p = (int*)buf;
	if (*p == ACK_ADDMEMBER_S)
	{
		ADDMEMBER *p = (ADDMEMBER*)buf;
		ui_LogMessage(TEXT("ȸ������ ����"));

	}
	else if (*p == ACK_ADDMEMBER_F)
	{
		ui_LogMessage(TEXT("ȸ������ ����"));

	}
	else if (*p == ACK_MINMEMBER)
	{
		ui_LogMessage(TEXT("ȸ��Ż�� ����"));
	}
	else if (*p == ACK_LOGIN_S)
	{
		  
		LOGIN *p = (LOGIN*)buf; //�̸��� ��������.
		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg, id, pw);
		if (_tcscmp(id, p->id) == 0)
		{
			g_IsLogin = TRUE; //�α��� Ȯ��... �� ������ �޽����� ��� ��µ�
			_tcscpy_s(g_Curinfo.id, p->id);
			_tcscpy_s(g_Curinfo.pw, p->pw); //���� �������� ���� �̿��ϱ� ����.. (���� pw�� �̸��������)
		}

		if (g_IsLogin == FALSE)
			return; //���� �α��� �ϱ����� �߻�.. .. �ٸ������ �α������� ���� ���ڿ� ��¾ȵ�..

		TCHAR buf[50];
		wsprintf(buf, TEXT("%s���� �α����ϼ̽��ϴ�."), p->pw);
		ui_LogMessage(buf);
	}
	else if (*p == ACK_LOGIN_F)
	{
		LOGIN *p = (LOGIN*)buf;
		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg, id, pw);
		if (_tcscmp(id, p->id) == 0) //
			ui_LogMessage(TEXT("�α��� ����"));//�̶��� ���

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
		LOGIN *p = (LOGIN*)buf; //�̸��� ��������.
		TCHAR id[20];
		TCHAR pw[20];
		ui_GetLogin(g_hDlg, id, pw);
		if (_tcscmp(id, p->id) == 0)
		{
			g_IsLogin = FALSE;

			TCHAR buf[50];
			wsprintf(buf, TEXT("%s���� �α׾ƿ��ϼ̽��ϴ�."), p->pw);
			ui_LogMessage(buf);
		}

	}

	//���� ����msg==============================================================
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