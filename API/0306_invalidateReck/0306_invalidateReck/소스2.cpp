#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100
/*
테스트 내용

1.이미 그려진 영역 위에 다른 그림을 그릴 수 있을까?
L버튼으로 만든 사각형 위에 R버튼으로 만든 사각형을 비스듬하게 겹친다
L버튼 사각형 위치 0~ 100
R버튼 사각형 위치 50~150

L버튼을 먼저 누르고 R버튼을 그 후에 누른다.

예상 결과 : L버튼 그림 위에 R버튼 그림이 올라갈 것이다

실험 결과 : 예상 결과와 일치 

결론 : 이미 그려진 영역 위에 다른 그림을 그릴 수 있다.
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)	{
	case WM_CREATE:
		return 0;

	case WM_LBUTTONDOWN:
	{
						   HDC hdc = GetDC(hwnd);
						   Rectangle(hdc, 0, 0, 100, 50);
						   ReleaseDC(hwnd, hdc);

						   return 0;
	}
	case WM_RBUTTONDOWN:
	{
						   HDC hdc = GetDC(hwnd);
						   Rectangle(hdc, 50, 0, 150, 50);
						   ReleaseDC(hwnd, hdc);
						   
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
