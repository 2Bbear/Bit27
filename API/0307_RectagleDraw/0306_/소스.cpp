//소스.cpp
#include "std.h"


vector<SHAPE*> g_drawList;
SHAPE g_drawCurrent;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//Init Event
	case WM_CREATE:			return OnCreate(hwnd);
	//Re Draw Window Event
	case WM_PAINT:			return OnPaint(hwnd);
	//Timer Event
	case WM_TIMER: return OnTimer(hwnd,wParam);
	//key Event
	case WM_LBUTTONDOWN:	return OnLButtonDown(hwnd,lParam);
	case WM_RBUTTONDOWN:	return OnRButtonDown(hwnd);
	case WM_KEYDOWN: return OnKeyDown(hwnd,wParam);
	case WM_CHAR: return OnChar(hwnd,wParam);
		
	//Destroy Event
	case WM_DESTROY:		return OnDestroy(hwnd);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}



int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPTSTR lpCmdLine, int nShowCmd)
{
	AllocConsole(); // console 창 생성

	freopen("CONOUT$",   // console 을
		"wt",        // text write 모드로
		stdout);	  // stdout 과 연결..
	// 1. 윈도우 클래스 만들기 
	WNDCLASS wc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;			// DefWindowProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	// 2. 등록(레지스트리에)
	RegisterClass(&wc);

	// 3. 윈도우 창 만들기 
	HWND hwnd = CreateWindowEx(0,	// WS_EX_TOPMOST
		TEXT("first"),				// 클래스 명
		TEXT("Hello"),				// 캡션바 내용
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	// 초기 위치 
		0, 0,			// 부모 윈도우 핸들, 메뉴 핸들
		hInst,		// WinMain의 1번째 파라미터 (exe 주소)
		0);			// 생성 인자

	// 4. 윈도우 보여주기
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// 5. Message 
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);//WM_CAHR을 내부적으로 실행 시킨다. 
		DispatchMessage(&msg);
	}
	return 0;
}