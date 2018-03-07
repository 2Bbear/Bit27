#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)	{
	case WM_CREATE:
	{
		SetTimer(hwnd, 1, 1000, NULL);//(타이머 메세지를 받을 윈도우,타이머의 번호 지정,주기값,호출될 함수) 내부 적으로 WM_TIMER 메세지를 보냄 wParam에 Timer ID를 같이 넣어서 보냄
		SendMessage(hwnd, WM_TIMER, 1, NULL);//강제로 WM_TIMER를 실행시키는 함수
		return 0;
	}
	case WM_TIMER:
	{
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
	case WM_LBUTTONDOWN:
	{
		DWORD count = GetTickCount();
		int second = count / 1000;
		int minute = (second % 3600) / 60;
		int hour = (second % 86400) / 3600;
		int day = second / 864000;
		TCHAR buf[50];
		wsprintf(buf, TEXT("%d일 %d시간 %d분 %d초 가 경과하였습니다."),day, hour, minute, second % 60);
		SetWindowText(hwnd, buf);

		return 0;
	}
		
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine,
	int nShowCmd)
{
	// 1. 윈도우 클래스 만들기 
	WNDCLASS wc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 2. 등록(레지스트리에)
	RegisterClass(&wc);
	// 3. 윈도우 창 만들기 
	HWND hwnd = CreateWindowEx(0,	// WS_EX_TOPMOST
		TEXT("first"),		// 클래스 명
		TEXT("Hello"),		// 캡션바 내용
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,// 초기 위치 
		0, 0,			// 부모 윈도우 핸들, 메뉴 핸들
		hInst,		// WinMain의 1번째 파라미터 (exe 주소)
		0);		// 생성 인자
	// 4. 윈도우 보여주기
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// 5. Message 
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); //분배기의 역할
	}
	return 0;
}
