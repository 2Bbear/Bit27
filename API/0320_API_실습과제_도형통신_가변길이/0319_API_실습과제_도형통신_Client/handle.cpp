#include"std.h"

int flag;
int x;
int y;
int width;
TCHAR str[20];
HWND mainHandle;
LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//SendMessage(hwnd, WM_TIMER, 1, NULL);//강제로 해당 핸들에 메세지로 보내는 함수
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
	//버튼 입력을 받는 event를 처리하기 위한 영역
	switch (LOWORD(wParam))
	{
		//접속버튼
	case IDC_BUTTON_CONNECTION:
	{
		printf("접속버튼 누름\n");
		OnConnect(hwnd);
		
		return 0;
	}
	//모달리스 버튼
	case IDC_BUTTON_MODAL:
	{
		printf("모달리스 버튼 누름\n");
		OnPopUpSubWindow(hwnd,wParam,lParam);
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
	int _flag = 0;
	int _x = 0;
	int _y = 0;
	int _width = 0;
	//========================================

	//========================================
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	//==============================================
	printf("그림출력\n");
	//여기에 그림을 그리면 된다
	ui_Draw(hdc,flag,x,y,width,str);
	
	//==============================================
	//각종 출력문에서 hdc를 사용한다.
	EndPaint(hwnd, &ps);

	return 0;
}
//===============================================================================================
void OnPopUpSubWindow(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//모달리스 팝업창
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
		//======================디버그용
		char wtoa[256];
		WideCharToMultiByte(CP_ACP, 0, ip, -1, wtoa, 250, NULL, NULL);
		printf("접속 시도 : IP %s  / Port %d", wtoa, port);
		//=======================
		//wbnet_StartClient(ip, port);
		if (wbnet_StartClient(ip, port) == TRUE)
		{
			printf("연결해제");
			//ui_SetButtonString(TEXT("연결해제"));
			bConnect = TRUE;
		}
	}
	else
	{
		wbnet_StopClient();
		printf("서버 연결 해제");
		//ui_LogMessage(TEXT("서버 연결 해제..."));
		//ui_SetButtonString(TEXT("연결"));
		bConnect = FALSE;
	}
}

void OnMessage(char* buf, int nRead)
{
	
	int *p = (int*)buf;
	if (*p == PACK_RECTPRINT)
	{
		printf("사각형그려라 핫산\n");
		
		RECTPRINT * p = (RECTPRINT*)buf;
		printf("x %d y %d width %d");
		flag = p->flag;
		x = p->x;
		y = p->y;
		width = p->width;
		printf("그림 셋팅 완료\n");
		
		RECT rc = { x - width, y - width, x + width, y + width };
		Rectangle(GetDC(mainHandle), x - width, y - width, x + width, y + width);
	/*	printf("무효화 영역 완료\n");
		InvalidateRect(mainHandle, &rc, TRUE);
		printf("무효화 영역 생성\n");*/
		/*ADDMEMBER *p = (ADDMEMBER*)buf;
		OnRecvAddMember(p);*/

	}
	else if (*p == PACK_ELLIPSEPRINT)
	{
		printf("타원그려라 핫산\n");
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
		printf("문자열그려라 핫산\n");
		STRINGEPRINT * p = (STRINGEPRINT*)buf;
		flag = p->flag;
		x = p->x;
		y = p->y;
	
		_tcscpy_s(str, p->str);
		//문자열 그리는 부분
		//InvalidateRect(mainHandle, &rc, TRUE);

		/*SHORTMESSAGE *msg = (SHORTMESSAGE*)buf;
		OnRecvShortMessage(msg);*/
	}
}