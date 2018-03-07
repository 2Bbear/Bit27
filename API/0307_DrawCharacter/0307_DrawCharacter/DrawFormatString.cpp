#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100
int some = 0;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)	{
	case WM_CREATE:
		return 0;
	case WM_LBUTTONDOWN:
	{
						   HDC hdc = GetDC(hwnd);
						   SetTextAlign(hdc, TA_UPDATECP);
						   TextOut(hdc, 200, 200, TEXT("Buautiful Korea"), 15);
						   TextOut(hdc, 200, 220, TEXT("is My"), 5);
						   TextOut(hdc, 200, 240, TEXT("Lovely Home Country"), 19);
						   ReleaseDC(hwnd, hdc);

						   return 0;

	}
	case WM_PAINT:
	{
					
					 PAINTSTRUCT ps;
					 HDC hdc = BeginPaint(hwnd, &ps);

					 TCHAR str[] = TEXT("네 번째 인수는 출력할 영역을 담고 있는 구조체 포인터이다.다섯번째 인수는 DrawText 함수가 문자열을 출력할 방법을지정하는 플래그이며 다음과 같은 여러 가지 플래그의 조합을 지정한다.");
					 
					 RECT rt = { 100, 100, 400, 300 };
					 DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);
					 EndPaint(hwnd, &ps);



					 EndPaint(hwnd, &ps);


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
