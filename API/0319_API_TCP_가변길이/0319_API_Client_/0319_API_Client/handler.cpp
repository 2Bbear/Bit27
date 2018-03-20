#include"std.h"


LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//SendMessage(hwnd, WM_TIMER, 1, NULL);//������ �ش� �ڵ鿡 �޼����� ������ �Լ�
	return 0;
}

LRESULT OnInitDialog(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	ui_InitDialog(hwnd);

	return TRUE;
}

LRESULT OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	
	//��ư �Է��� �޴� event�� ó���ϱ� ���� ����
	switch (LOWORD(wParam))
	{
		//����
	case IDC_BUTTON_LINK:
	{
		OnConnect(hDlg);
		return 0;
	}
	//�޼��� ������
	case IDC_BUTTON_SEND:
	{
		OnShortMessage(hDlg);
		//OnSend(hDlg);
		return 0;
	}
	//���� 1 ȸ������
	case IDC_BUTTON_SIGNIN:
	{
		OnAddMember(hDlg);
		return 0;
	}
	//���� 2 �α���
	case IDC_BUTTON_LOGIN:
	{
		OnLogin(hDlg);
		return 0;
	}
	//����3 Ż��
	case IDC_BUTTON_UNREGISTER:
	{
		
		return 0;
	}
	case IDCANCEL:
	{
		EndDialog(hDlg, IDCANCEL);	return 0;
	}

	}
	return TRUE;
}

LRESULT OnInitMenuPopUp(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT OnContextMenu(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT OnLButtonUp(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT OnRButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT OnRButtonUp(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT OnMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT OnKeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//���� �޼����� �߻��� ������ Ư�� Ű���� ���¸� �����Ѵ�.
	//SHORT GetKeyState(int nVirtKey);
	//���� Ű������ ���¸� �����Ѵ�
	//   SHORT GetAsynckKeyState(int vKey);
	//��� ���� Ű�� ���¸� ���´�.
	//BOOL GetKeyboardState( PBYTE lpKeyState)

	//���� Ű �о����
	switch (wParam)
	{
	case VK_RETURN:
	{
		OnSend(hwnd);
		break;
	}
		
	case VK_LEFT:
	{
		break;
	}
	case VK_RIGHT:
	{
		break;
	}
	case VK_UP:
	{
		break;
	}
	case VK_DOWN:
	{
		break;
	}
	}


	return 0;
}

LRESULT OnSystemKeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT OnSystemKeyUp(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT OnChar(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 'a':
	{
		MessageBox(hwnd, TEXT(""), TEXT(""), 0);
		break;
	}
	}
	//this function must have write [ TranslateMessage(const MSG *lpMsg);] in Main code
	return 0;
}


void CALLBACK MyTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	RECT rc = { 200, 0, 500, 100 };
	InvalidateRect(hWnd, &rc, TRUE);
}


LRESULT OnTimer(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//You must have call [SetTimer(hwnd,Ÿ�̸� �ѹ���,1000,null)] function In WM_CREATE and anywhere.
	//SetTimer(hwnd, 1, 1000, MyTimerProc);//Ÿ�̸ӿ� Call Back �Լ��� �ɾ� ���� ���
	//wParam�� �� Ÿ�̸Ӽ��� �ѹ����̴�, �ٸ� Ÿ�̸ӵ�� ȥ�� �ϸ� �ȵǴϱ�
	if (wParam == 1)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		TCHAR buf[20];
		wsprintf(buf, TEXT("���� �ð� : %d:%d:%d"),
			st.wHour, st.wMinute, st.wSecond);
		SetWindowText(hwnd, buf);
	}

	return 0;
}

LRESULT OnDestroy()
{
	PostQuitMessage(0);
	return 0;
}

LRESULT OnPaInt(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	//==============================================
	//���⿡ �׸��� �׸��� �ȴ�

	//==============================================
	//���� ��¹����� hdc�� ����Ѵ�.
	EndPaint(hwnd, &ps); 

	return 0;
}

//=========================================================================

void OnConnect(HWND hDlg)
{
	static BOOL bConnect = FALSE;
	if (bConnect==FALSE)
	{
		TCHAR ip[256];
		int port;
		ui_getAddress(hDlg,ip,&port);
		//======================����׿�
		char wtoa[256];
		WideCharToMultiByte(CP_ACP, 0, ip, -1, wtoa, 250, NULL, NULL);
		printf("���� �õ� : IP %s  / Port %d", wtoa,port);
		//=======================
		wbnet_StartClient(ip,port);
		if (wbnet_StartClient(ip,port)==TRUE)
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



void OnLogMessage(TCHAR * msg)
{
	ui_LogMessage(msg);
}

void OnMessage(char * _buf, int _nRead)
{
	TCHAR buf[256];
	
	//wchar_t w_ip[250];
	memcpy(buf, _buf, _nRead);
	//MultiByteToWideChar(CP_ACP, 0, _buf, -1, w_ip, 250);

	int* p = (int*)_buf;
	if (*p == PACK_ADDMEMBER)
	{
		ADDMEMBER *p = (ADDMEMBER*)_buf;
		wsprintf(buf, TEXT("Flag : %d , name : %s , id : %s , pw : %s\n"), p->flag, p->name, p->id, p->pw);
		//�޼��� ���
		//OnRecvAddMember(p);

	}
	else if (*p == PACK_LOGIN)
	{
		LOGIN* p = (LOGIN*)_buf;
		wsprintf(buf, TEXT("Flag : %d , id : %s , pw : %s\n"), p->flag, p->id, p->pw);
		//�޼��� ���
		//OnRecvLogin(p);
	}
	else if (*p == PACK_SHORTMESSAGE)
	{
		SHORTMESSAGE *p = (SHORTMESSAGE*)_buf;
		wsprintf(buf, TEXT("Flag : %d , ���ڿ� : %s\n"), p->flag,p->rest);
		//�޼��� ���
		//OnRecvShortMessage(p); //
	}

	ui_LogMessage(buf);
}



void OnSend(HWND hDlg)
{
	TCHAR  msg[50];
	ui_GetSendMessage(hDlg, msg);
	wbnet_SendMessage(msg, _tcslen(msg) * 2 + 2);
}

void OnAddMember(HWND hDlg)
{
	TCHAR name[20];
	TCHAR id[20];
	TCHAR password[20];

	ui_GetEditMemberData(hDlg,name,id,password);
	ADDMEMBER  packet=pack_SetAddMember(name,id,password);
	
	wbnet_SendMessage((TCHAR*)&packet, sizeof(ADDMEMBER));
}

void OnLogin(HWND hDlg)
{

	TCHAR name[20];
	TCHAR id[20];
	TCHAR password[20];

	ui_GetEditMemberData(hDlg, name, id, password);
	LOGIN  packet = pack_SetLoginData(id, password);
	wbnet_SendMessage((TCHAR*)&packet, sizeof(LOGIN));
}
void OnShortMessage(HWND hDlg)
{
	SHORTMESSAGE packet = pack_SetShortMessage();
	ui_GetSendMessage(hDlg, packet.rest);

	wbnet_SendMessage((TCHAR*)&packet, sizeof(SHORTMESSAGE));
}