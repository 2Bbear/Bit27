#include"std.h"

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//SendMessage(hwnd, WM_TIMER, 1, NULL);//������ �ش� �ڵ鿡 �޼����� ������ �Լ�
	return 0;
}

LRESULT OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	ui_InitControl(hDlg);
	return 0;
}

LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//��ư �Է��� �޴� event�� ó���ϱ� ���� ����
	switch (LOWORD(wParam))
	{
	//���� ���� ��ư
	case IDC_BUTTON_ACTIVE:
	{
		OnStartServer(hwnd);
		return 0;
	}
	//ĵ�� ��ư �Է�
	case IDCANCEL:
	{
		EndDialog(hwnd, IDCANCEL);	return 0;
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
//=================================================



void OnStartServer(HWND hDlg)
{
	
	int port= PORT;
	//port = ui_getPort(hDlg);
	wbnet_StartServer(port);
}


void OnLogMessage(TCHAR *msg)
{
	ui_LogMessage(msg);
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


void OnMessage(char* buf, int nRead)
{
	TCHAR msgBuf[50] = {0};
	int *p = (int*)buf;
	if (*p == PACK_RECTPRINT)
	{
		printf("�簢��\n");
		RECTPRINT *p = (RECTPRINT*)buf;

		wsprintf(msgBuf, TEXT("�簢�� (X : %d Y : %d)(%d)"), p->x, p->y, p->width);

		ui_LogMessage(msgBuf);
		/*ADDMEMBER *p = (ADDMEMBER*)buf;
		OnRecvAddMember(p);*/

	}
	else if (*p == PACK_ELLIPSEPRINT)
	{
		printf("Ÿ��\n");
		ELLIPSEPRINT *p = (ELLIPSEPRINT*)buf;

		wsprintf(msgBuf, TEXT("Ÿ�� (X : %d Y : %d)(%d)"), p->x, p->y, p->width);

		ui_LogMessage(msgBuf);
		/*LOGIN *p = (LOGIN*)buf;
		OnRecvLogin(p);*/
	}
	else if (*p == PACK_STRINGPRINT)
	{
		printf("���ڿ�\n");
		STRINGEPRINT *p = (STRINGEPRINT*)buf;

		wsprintf(msgBuf, TEXT("���ڿ� (X : %d Y : %d)(%s)"), p->x, p->y, p->str);

		ui_LogMessage(msgBuf);
		/*SHORTMESSAGE *msg = (SHORTMESSAGE*)buf;
		OnRecvShortMessage(msg);*/
	}
}