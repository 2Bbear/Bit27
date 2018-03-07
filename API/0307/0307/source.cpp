#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100
/*
윈도우에 선을 그리는 프로그램

*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;
	//static BOOL bNowDraw = FALSE;

	switch (msg)	{

	case WM_CREATE:
		return 0;
		//l버튼 눌럿을 때
	case WM_LBUTTONDOWN:
	{
						   HDC hdc = GetDC(hwnd);
						  SetMapMode(hdc, MM_LOMETRIC);
						  Rectangle(hdc,0,0,100,-100);

						  POINT pt = { LOWORD(lParam), HIWORD(lParam) };
						  DPtoLP(hdc, &pt, 1);
						  Rectangle(hdc, pt.x,pt.y,pt.x+50,pt.y+50); // 모드 변경 안해주면 이거 이상하게 출력됨
						  ReleaseDC(hwnd,hdc);
						 /*  start = MAKEPOINTS(lParam);
						   end = start;
						   SetCapture(hwnd);*/
						 //  bNowDraw = TRUE;

						   return 0;

	}
		
	case WM_LBUTTONUP:
	{
						 ReleaseCapture();
						// bNowDraw = FALSE;//더이상 마우스 무브에서 그림이 그려지지 않도록 함
						 HDC hdc = GetDC(hwnd);
						 MoveToEx(hdc, start.x, start.y, NULL);
						 LineTo(hdc, end.x, end.y);
						 ReleaseDC(hwnd, hdc);

						 return 0;
	}
		
	case WM_MOUSEMOVE:
	{
						 if (GetCapture()==hwnd)//if(bNowDraw)
						 {
							 HDC hdc = GetDC(hwnd);
							 SetROP2(hdc, R2_NOT);//반전모드 설정
							 MoveToEx(hdc, start.x, start.y, NULL);//(dc, 첫 마우스 좌표.)
							 LineTo(hdc, end.x, end.y);

							 end = MAKEPOINTS(lParam);
							 
							 MoveToEx(hdc, start.x, start.y, NULL);
							 LineTo(hdc, end.x, end.y);
							 ReleaseDC(hwnd, hdc);
						 }

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
