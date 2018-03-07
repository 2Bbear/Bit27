#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100
/*
1. 정말 SetROP2 을 통해 반전값이 된 값으로 이전의 그렸던 선 분을 지우는 것일 까?
SetROP2을 통해 그려지는 새로운 라인의 펜 속성을 점선으로 바꾼다.

예상 결과 : 화면에 점선들이 두두두둗 생길 것이다.

실험 결과 : 그냥 움직이면서 선들이 끊기는데 선이 남아 있지는 않는다.
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;
	static BOOL bNowDraw = FALSE;


	switch (msg)	{
	case WM_CREATE:
	{
					  return 0;
	}
		
	case WM_LBUTTONDOWN:
	{
						   start = MAKEPOINTS(lParam);
						   end = start;
						   bNowDraw = TRUE;

						   return 0;
	}
	case WM_LBUTTONUP:
	{
						 bNowDraw = FALSE;
						 HDC hdc = GetDC(hwnd);
						 MoveToEx(hdc, start.x, start.y, NULL);
						 LineTo(hdc, end.x, end.y);
						 ReleaseDC(hwnd, hdc);

						   return 0;
	}
	case WM_MOUSEMOVE:
	{
						 if (bNowDraw)
						 {
							 HDC hdc = GetDC(hwnd);
							 SetROP2(hdc, R2_NOT);//반전 이유는 이전 값의 선을 삭제하기 위해서, 검은색이면 흰색으로
							 //펜 스타일 변경
							 HPEN pen = CreatePen(1, 1, RGB(0, 0, 0));
							 HPEN oldPen = (HPEN)SelectObject(hdc,pen);

							 MoveToEx(hdc, start.x, start.y, NULL);
							 LineTo(hdc, end.x, end.y);

							 //펜 스타일 해제
							 DeleteObject(SelectObject(hdc,oldPen));

							 end = MAKEPOINTS(lParam);
							 MoveToEx(hdc, start.x, start.y, NULL);
							 LineTo(hdc, end.x, end.y);
							 ReleaseDC(hwnd, hdc);
						 }

						 return 0;
	}
		
	case WM_DESTROY:
	{
					   PostQuitMessage(0);
					   return 0;
	}
		
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
