#include"std.h"

int flag;
int x;
int y;
int width;
TCHAR str[20];
HWND mainHandle;
LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//SendMessage(hwnd, WM_TIMER, 1, NULL);//������ �ش� �ڵ鿡 �޼����� ������ �Լ�
	return 0;
}

LRESULT OnInitDialog(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	mainHandle = hwnd;
	ui_InitDlg(hwnd);
	return 0;
}

LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//��ư �Է��� �޴� event�� ó���ϱ� ���� ����
	switch (LOWORD(wParam))
	{
		//���ӹ�ư
	case IDC_BUTTON_CONNECTION:
	{
		printf("���ӹ�ư ����\n");
		OnConnect(hwnd);
		
		return 0;
	}
	//��޸��� ��ư
	case IDC_BUTTON_MODAL:
	{
		printf("��޸��� ��ư ����\n");
		OnPopUpSubWindow(hwnd,wParam,lParam);
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
	int _flag = 0;
	int _x = 0;
	int _y = 0;
	int _width = 0;
	//========================================

	//========================================
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	//==============================================
	printf("�׸����\n");
	//���⿡ �׸��� �׸��� �ȴ�
	ui_Draw(hdc,flag,x,y,width,str);
	
	//==============================================
	//���� ��¹����� hdc�� ����Ѵ�.
	EndPaint(hwnd, &ps);

	return 0;
}
//===============================================================================================
void OnPopUpSubWindow(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//��޸��� �˾�â
	UINT ret = SWSS_CreateWindow(hwnd, wParam, lParam);
}


void OnConnect(HWND hDlg)
{
	static BOOL bConnect = FALSE;
	if (bConnect == FALSE)
	{
		TCHAR ip[256] = TEXT("192.168.0.33") ;
		int port=9000;
		//ui_getAddress(hDlg, ip, &port);
		//======================����׿�
		char wtoa[256];
		WideCharToMultiByte(CP_ACP, 0, ip, -1, wtoa, 250, NULL, NULL);
		printf("���� �õ� : IP %s  / Port %d", wtoa, port);
		//=======================
		//wbnet_StartClient(ip, port);
		if (wbnet_StartClient(ip, port) == TRUE)
		{
			printf("��������");
			//ui_SetButtonString(TEXT("��������"));
			bConnect = TRUE;
		}
	}
	else
	{
		wbnet_StopClient();
		printf("���� ���� ����");
		//ui_LogMessage(TEXT("���� ���� ����..."));
		//ui_SetButtonString(TEXT("����"));
		bConnect = FALSE;
	}
}

void OnMessage(char* buf, int nRead)
{
	
	int *p = (int*)buf;
	if (*p == PACK_RECTPRINT)
	{
		printf("�簢���׷��� �ֻ�\n");
		
		RECTPRINT * p = (RECTPRINT*)buf;
		printf("x %d y %d width %d");
		flag = p->flag;
		x = p->x;
		y = p->y;
		width = p->width;
		printf("�׸� ���� �Ϸ�\n");
		
		RECT rc = { x - width, y - width, x + width, y + width };
		Rectangle(GetDC(mainHandle), x - width, y - width, x + width, y + width);
	/*	printf("��ȿȭ ���� �Ϸ�\n");
		InvalidateRect(mainHandle, &rc, TRUE);
		printf("��ȿȭ ���� ����\n");*/
		/*ADDMEMBER *p = (ADDMEMBER*)buf;
		OnRecvAddMember(p);*/

	}
	else if (*p == PACK_ELLIPSEPRINT)
	{
		printf("Ÿ���׷��� �ֻ�\n");
		ELLIPSEPRINT * p = (ELLIPSEPRINT*)buf;
		flag = p->flag;
		x = p->x;
		y = p->y;
		width = p->width;
		
		RECT rc = { x - width, y - width, x + width, y + width };
		InvalidateRect(mainHandle, &rc, TRUE);
		/*LOGIN *p = (LOGIN*)buf;
		OnRecvLogin(p);*/
	}
	else if (*p == PACK_STRINGPRINT)
	{
		printf("���ڿ��׷��� �ֻ�\n");
		STRINGEPRINT * p = (STRINGEPRINT*)buf;
		flag = p->flag;
		x = p->x;
		y = p->y;
	
		_tcscpy_s(str, p->str);
		//���ڿ� �׸��� �κ�
		//InvalidateRect(mainHandle, &rc, TRUE);

		/*SHORTMESSAGE *msg = (SHORTMESSAGE*)buf;
		OnRecvShortMessage(msg);*/
	}
}