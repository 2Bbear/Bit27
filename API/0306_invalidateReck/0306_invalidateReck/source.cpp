#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100
/*
테스트 내용

1. InvalidateRect가 내부적으로 WM_PAINT를 호출하는 가?
 L버튼은 100~150 사이에 사각형을 그린다.
 R버튼은 0~50사이의 사각형을 지운다.

 WM_PAINT는 0~50사이에 사각형을 그린다
            100~150 사이의 사각형을 지운다.
 예상 결과 : 
 R버튼을 누르면 0~50 사이의 사각형은 계속 색이 변할 것이고, 100~150사이의 사각형은 사라질 것이다.
 
 예상 되는 결론 :
 R버튼 처리 안에는 100~150 사이의 사각형을 지우는 내용이 전혀 없는데 100~150 사이의 사각형이 사라졌다.
 이 말은 R 버튼 안에 있는 InvalidateRect가 내부적으로 WM_PAINT를 호출한다는 의미이다.

 실험 - 예상과 일치

2. 마지막으로 TRUE 값의 역할은?
 L버튼으로 만든 사각형을 R버튼으로 삭제해보자
 TRUE 값일 때 어떻게 작동하는 지
 FALSE 값일 때 어떻게 작동하는 지 알아보자

 예상 결과 : TRUE 일때 사각형은 바로 사라질 것이다. FALSE 일때 사각형은 사라지지 않고 남아 있을 것이다.

 실험 - 예상과 일치

 결론
 InvalidateRect는 해당 위치에 무효화 영역을 생성한다. 
 TRUE 값일 때 WM_PAINT 메세지를 바로 프로시저에 전달한다.
 FALSE 값일 때 WM_PAINT 메세지를 메세지 큐에 넣어 놓는다. 


*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)	{
	case WM_CREATE:
		return 0;

	case WM_LBUTTONDOWN:
	{
						   HDC hdc = GetDC(hwnd);
						   Rectangle(hdc, 100, 0, 150, 50);
						   ReleaseDC(hwnd, hdc);

		return 0;
	}
	case WM_RBUTTONDOWN:
	{
						  
		//실험 1		   
		RECT r = { 0, 0, 50, 50 };
		InvalidateRect(hwnd, &r, TRUE);//True값을 하면 바로 반영됨

		//실험 2
		//RECT r = { 100, 0, 150, 50 };
		//InvalidateRect(hwnd, &r, TRUE);//True값을 하면 바로 반영됨
		return 0;
	}
		//실험 1
	case WM_PAINT:
	{
					 RECT r = { 100, 0, 150, 50 };
					 InvalidateRect(hwnd, &r, FALSE);//True값을 하면 바로 반영됨
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		HBRUSH old = (HBRUSH)SelectObject(hdc, brush);
		
		Rectangle(hdc,0,0,50,50);
		
		DeleteObject(SelectObject(hdc, old));
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
