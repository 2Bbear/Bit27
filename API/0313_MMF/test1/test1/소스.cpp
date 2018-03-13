#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100
typedef struct _LINE {
	POINTS ptFrom;
	POINTS ptTo;
} LINE;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static HANDLE hEvent, hMap;
	static LINE*  pData;//페이징 파일에 잡힌 메모리로 쓸 변수
	static POINTS ptFrom;
	switch (msg)
	{
	case WM_LBUTTONDOWN: ptFrom = MAKEPOINTS(lParam); return 0;
	case WM_MOUSEMOVE:
		if (wParam & MK_LBUTTON)
		{
			POINTS pt = MAKEPOINTS(lParam);
			HDC hdc = GetDC(hwnd);
			MoveToEx(hdc, ptFrom.x, ptFrom.y, 0);
			LineTo(hdc, pt.x, pt.y);
			ReleaseDC(hwnd, hdc);

			// MMF 에 넣는다.
			pData->ptFrom = ptFrom;
			pData->ptTo = pt;
			SetEvent(hEvent);
			ptFrom = pt;
		}
		return 0;
	case WM_CREATE:
	{
		//이벤트가 발생했다고 연동하기 위한 것 그러한 것
		hEvent = CreateEvent(0, 0, 0, TEXT("DRAW_SIGNAL"));
		//
		hMap = CreateFileMapping((HANDLE)-1, // Paging 화일을 사용해서 매핑
			0, PAGE_READWRITE, 0, sizeof(LINE), TEXT("map"));
		pData = (LINE*)MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, 0);
		if (pData == 0)
		{
			MessageBox(0, TEXT("Fail"), TEXT(""), MB_OK);			
		}
	}
		return 0;
	case WM_DESTROY:
		UnmapViewOfFile(pData);
		CloseHandle(hMap);
		CloseHandle(hEvent);
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