#include"std.h"


LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//SendMessage(hwnd, WM_TIMER, 1, NULL);//강제로 해당 핸들에 메세지로 보내는 함수
	return 0;
}

LRESULT OnInitDialog(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	ui_InitDialog(hwnd);

	return TRUE;
}

LRESULT OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	
	//버튼 입력을 받는 event를 처리하기 위한 영역
	switch (LOWORD(wParam))
	{
		//연결
	case IDC_BUTTON_LINK:
	{
		OnConnect(hDlg);
		return 0;
	}
	//메세지 보내기
	case IDC_BUTTON_SEND:
	{
		OnShortMessage(hDlg);
		//OnSend(hDlg);
		return 0;
	}
	//전송 1 회원가입
	case IDC_BUTTON_SIGNIN:
	{
		OnAddMember(hDlg);
		return 0;
	}
	//전송 2 로그인
	case IDC_BUTTON_LOGIN:
	{
		OnLogin(hDlg);
		return 0;
	}
	//전송3 탈퇴
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
	//현재 메세지가 발생한 순간의 특정 키보드 상태를 조사한다.
	//SHORT GetKeyState(int nVirtKey);
	//현재 키보드의 상태를 조사한다
	//   SHORT GetAsynckKeyState(int vKey);
	//모든 가상 키의 상태를 얻어온다.
	//BOOL GetKeyboardState( PBYTE lpKeyState)

	//가상 키 읽어오기
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

//=========================================================================

void OnConnect(HWND hDlg)
{
	static BOOL bConnect = FALSE;
	if (bConnect==FALSE)
	{
		TCHAR ip[256];
		int port;
		ui_getAddress(hDlg,ip,&port);
		//======================디버그용
		char wtoa[256];
		WideCharToMultiByte(CP_ACP, 0, ip, -1, wtoa, 250, NULL, NULL);
		printf("접속 시도 : IP %s  / Port %d", wtoa,port);
		//=======================
		wbnet_StartClient(ip,port);
		if (wbnet_StartClient(ip,port)==TRUE)
		{
			ui_SetButtonString(TEXT("연결해제"));
			bConnect = TRUE;
		}
	}
	else
	{
		wbnet_StopClient();
		ui_LogMessage(TEXT("서버 연결 해제..."));
		ui_SetButtonString(TEXT("연결"));
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
		//메세지 출력
		//OnRecvAddMember(p);

	}
	else if (*p == PACK_LOGIN)
	{
		LOGIN* p = (LOGIN*)_buf;
		wsprintf(buf, TEXT("Flag : %d , id : %s , pw : %s\n"), p->flag, p->id, p->pw);
		//메세지 출력
		//OnRecvLogin(p);
	}
	else if (*p == PACK_SHORTMESSAGE)
	{
		SHORTMESSAGE *p = (SHORTMESSAGE*)_buf;
		wsprintf(buf, TEXT("Flag : %d , 문자열 : %s\n"), p->flag,p->rest);
		//메세지 출력
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