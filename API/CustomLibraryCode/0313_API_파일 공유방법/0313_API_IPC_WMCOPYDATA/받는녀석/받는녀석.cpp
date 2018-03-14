#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;
	switch (msg)
	{
	case WM_USER+100:
	{
		return 0;
	}
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
			10, 10, 400, 400, hwnd, (HMENU)1, 0, 0);
		return 0;
	case WM_COPYDATA:
	{
		MessageBox(hwnd,TEXT(""), TEXT(""),MB_OK);
		COPYDATASTRUCT* p = (COPYDATASTRUCT*)lParam;
		if (p->dwData == 1) // 식별자 조사.
		{
			// Edit Box에 추가 한다.
			SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)(p->lpData));
			SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
		}
	}
	return 0;
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
	wc.lpszClassName = TEXT("B");
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 2. 등록(레지스트리에)
	RegisterClass(&wc);
	// 3. 윈도우 창 만들기 
	HWND hwnd = CreateWindowEx(0,	// WS_EX_TOPMOST
		TEXT("B"),		// 클래스 명
		TEXT("B"),		// 캡션바 내용
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
