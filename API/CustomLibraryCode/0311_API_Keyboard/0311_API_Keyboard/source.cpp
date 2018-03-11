#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
	case WM_CREATE:
		return 0;
	//Keyboar Input
	case WM_KEYDOWN:
	{
		//Scan Code 가져오기=======================================================================
		//scan코드를 변환하기 위한 매크로
		#define GetScanCode(x) ( ( x >> 16) & 0x00FF)
		TCHAR buf[30];
		wsprintf(buf, TEXT("Scan Code : %d\n"), GetScanCode(lParam));

		//가상 key code 가져오기===================================================================
		switch (wParam)
		{
		case VK_BACK: {}break;
		case VK_TAB: {}break;
		case VK_RETURN: {}break;
		case VK_GAMEPAD_LEFT_TRIGGER: {}break;
			//등등 좋나 많음.
			//그냥 문자도 받아 올 수 있음 대소문자 구분 못함
		case 'A': {MessageBox(hwnd,TEXT("d"), TEXT("d"),0); }break;
		}

		//조합키 입력받기===========================================================================
		if (wParam==VK_F1&& GetKeyState(VK_CONTROL) & 0xFF00) // 누루고 있는 방식
		{
			MessageBox(0, TEXT("CRTL+ F1"), TEXT(""), MB_OK);
		}
		if (wParam == VK_F2 && GetKeyState(VK_CONTROL) & 0x00FF) //토글 방식
		{
			MessageBox(0, TEXT("CRTL+ F2"), TEXT(""), MB_OK);
		}
		return 0;
		//SHORT GetAsynckKeyState(int vKey); 현재 키보드의 상태를 조사하는 함수
		//BOOL GetKeyboardState( PBYTE lpKeyState) 모든 가상 키의 상태를 얻어온다.
	}
	case WM_KEYUP:
	{
		switch (wParam)
		{

		}
		return 0;
	}

	//ALt 조합키, 반드시 디폴트 윈도우로 넘겨줘야 한다.===========================================
	case WM_SYSKEYDOWN:
	{
		switch (wParam)
		{
		case 'G':
		{
			MessageBox(hwnd, TEXT("G"), TEXT("G라구요!"), 0);
			break;
		}
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	case WM_SYSKEYUP:
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	//아스키 값 가져오기==========================================================================
	case WM_CHAR:
	{
		switch (wParam)
		{
		case 'c':
		{
			MessageBox(0, TEXT("c라구"), TEXT(""), MB_OK);
			

			return 0;
		}
		case 'C':
		{
			MessageBox(0, TEXT("큰C라구"), TEXT(""), MB_OK);
			return 0;
		}

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
