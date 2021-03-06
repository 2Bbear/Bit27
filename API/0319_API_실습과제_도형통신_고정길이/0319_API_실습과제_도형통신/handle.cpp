#include"std.h"

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//SendMessage(hwnd, WM_TIMER, 1, NULL);//강제로 해당 핸들에 메세지로 보내는 함수
	return 0;
}

LRESULT OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	ui_InitControl(hDlg);
	return 0;
}

LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//버튼 입력을 받는 event를 처리하기 위한 영역
	switch (LOWORD(wParam))
	{
	//서버 실행 버튼
	case IDC_BUTTON_ACTIVE:
	{
		OnStartServer(hwnd);
		return 0;
	}
	//캔슬 버튼 입력
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
	//현재 메세지가 발생한 순간의 특정 키보드 상태를 조사한다.
	//SHORT GetKeyState(int nVirtKey);
	//현재 키보드의 상태를 조사한다
	//   SHORT GetAsynckKeyState(int vKey);
	//모든 가상 키의 상태를 얻어온다.
	//BOOL GetKeyboardState( PBYTE lpKeyState)

	//가상 키 읽어오기
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
	//You must have call [SetTimer(hwnd,타이머 넘버링,1000,null)] function In WM_CREATE and anywhere.
	//SetTimer(hwnd, 1, 1000, MyTimerProc);//타이머에 Call Back 함수를 걸어 놓은 모습
	//wParam는 각 타이머셋의 넘버링이다, 다른 타이머들과 혼동 하면 안되니까
	if (wParam == 1)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		TCHAR buf[20];
		wsprintf(buf, TEXT("현재 시간 : %d:%d:%d"),
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
	//여기에 그림을 그리면 된다

	//==============================================
	//각종 출력문에서 hdc를 사용한다.
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
		wsprintf(buf, TEXT("클라이언트 접속(%s:%d)"), w_ip, port);
	else if (flag == 0)
		wsprintf(buf, TEXT("클라이언트 해제(%s:%d)"), w_ip, port);
	ui_LogMessage(buf);
}


void OnMessage(char* buf, int nRead)
{
	TCHAR msgBuf[50] = {0};
	int *p = (int*)buf;
	if (*p == PACK_RECTPRINT)
	{
		printf("사각형\n");
		RECTPRINT *p = (RECTPRINT*)buf;

		wsprintf(msgBuf, TEXT("사각형 (X : %d Y : %d)(%d)"), p->x, p->y, p->width);

		ui_LogMessage(msgBuf);
		/*ADDMEMBER *p = (ADDMEMBER*)buf;
		OnRecvAddMember(p);*/

	}
	else if (*p == PACK_ELLIPSEPRINT)
	{
		printf("타원\n");
		ELLIPSEPRINT *p = (ELLIPSEPRINT*)buf;

		wsprintf(msgBuf, TEXT("타원 (X : %d Y : %d)(%d)"), p->x, p->y, p->width);

		ui_LogMessage(msgBuf);
		/*LOGIN *p = (LOGIN*)buf;
		OnRecvLogin(p);*/
	}
	else if (*p == PACK_STRINGPRINT)
	{
		printf("문자열\n");
		STRINGEPRINT *p = (STRINGEPRINT*)buf;

		wsprintf(msgBuf, TEXT("문자열 (X : %d Y : %d)(%s)"), p->x, p->y, p->str);

		ui_LogMessage(msgBuf);
		/*SHORTMESSAGE *msg = (SHORTMESSAGE*)buf;
		OnRecvShortMessage(msg);*/
	}
}