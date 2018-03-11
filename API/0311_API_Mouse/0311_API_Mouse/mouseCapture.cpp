#include <windows.h>
#include <tchar.h>

#define MYERRORCHECK MessageBox(hwnd, TEXT("adad"), TEXT("adad"), 0);
/*
마우스 캡쳐하는 방법
1. down 메세지에 캡처를 넣는다.
2. up  메세지에 릴리즈를 한다.

*/
//이거 쓰잘떼기 없잖아.  주어진 핸들값을 가지고 있는 윈도우의 정보를 출력하는 함수 
void PrintWindowInfo(HWND hwnd)
{
	TCHAR Info[1024] = { 0 };
	TCHAR temp[256];
	RECT rcWin;
	GetClassName(hwnd, temp, 256);
	wsprintf(Info, TEXT("Window Class : %s\n"), temp);
	GetWindowText(hwnd, temp, 256);
	wsprintf(Info + wcslen(Info), TEXT("Window Caption : %s\n"), temp);
	GetWindowRect(hwnd, &rcWin);
	wsprintf(Info + wcslen(Info), TEXT("Window Position : (%d,%d)-(%d,%d)"),
		rcWin.left, rcWin.top, rcWin.right, rcWin.bottom);
	MessageBox(0, Info, TEXT("Window Info"), MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			return 0;
		}
	
	
		//Mouse Input
		//L Button
		case WM_LBUTTONDOWN:
		{
			//매개변수의 핸들이 마우스 커서를 캡쳐하게 함
			SetCapture(hwnd);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			//현재 어떤 윈도우가 커서를 캡쳐했는가
			if (GetCapture() == hwnd)
			{
				//현재 캡쳐된 상황을 해제
				ReleaseCapture();
				POINT pt;
				//현재 마우스 커서의 위치 값을 저장
				GetCursorPos(&pt);
				//현재 커서가 위치한 윈도우의 핸들 값을 가져오는 함수
				HWND hwndDest = WindowFromPoint(pt);
				PrintWindowInfo(hwndDest);
			}
		}
		//현재 마우스 커서의 위치를 제목 표시줄에 출력하는 함수
		case WM_MOUSEMOVE:
		{
			short xPos, yPos;
			TCHAR temp[256];
			xPos = LOWORD(lParam);
			yPos = HIWORD(lParam);
			wsprintf(temp, TEXT("Cursor Position : (%d, %d)"), xPos, yPos);
			SetWindowText(hwnd, temp);
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

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;//////////////////////////////////////////////////더블 클릭을 위해 CS_DBLCLKS를 추가함
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
