#include <windows.h>
#include <tchar.h>

#define MYERRORCHECK MessageBox(hwnd, TEXT("adad"), TEXT("adad"), 0);

/*
1. 기본적인 마우스 입력 받기
2. 마우스에서 좌표 읽어 오기
3. 마우스와 조합키 받기
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CREATE:
	{
		return 0;
	}
	//Mouse Input
	//L Button
	case WM_LBUTTONDOWN :
	{
		
		return 0;
	}
	case WM_LBUTTONUP:
	{
		if (GetCapture()==hwnd)
		{
			

		}
		return 0;
	}
	case WM_LBUTTONDBLCLK:
	{
		
		return 0;
	}
	//R button
	case WM_RBUTTONDOWN :
	{
		//조합키 상태 검사
		if (wParam&MK_SHIFT)
		{
			MessageBox(hwnd, TEXT("control"), TEXT("control"), 0);
		}
		else if (wParam&MK_LBUTTON)
		{

		}
		else if (wParam&MK_RBUTTON)
		{

		}
		else if (wParam&MK_MBUTTON)
		{

		}
		else if (wParam&MK_CONTROL)
		{

		}
		return 0;
	}
	case WM_RBUTTONUP:
	{
		return 0;
	}
	case WM_RBUTTONDBLCLK:
	{
		return 0;
	}
	//M button
	case WM_MBUTTONDOWN:
	{
		//좌표값 가져오기
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		TCHAR xText[20];
		TCHAR yText[20];
		wsprintf(xText, TEXT("x값 :%d"), x);
		wsprintf(yText, TEXT("y값 :%d"), y);
		MessageBox(hwnd, xText, yText, 0);
		return 0;
	}
	case WM_MBUTTONUP:
	{
		return 0;
	}
	case WM_MBUTTONDBLCLK:
	{
		return 0;
	}
	//M Wheel
	case WM_MOUSEWHEEL:
	{
		
		return 0;
	}
	
	
	//Move
	case WM_MOUSEMOVE:
	{
		
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

	wc.style = CS_HREDRAW | CS_VREDRAW |CS_DBLCLKS;//////////////////////////////////////////////////더블 클릭을 위해 CS_DBLCLKS를 추가함
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
