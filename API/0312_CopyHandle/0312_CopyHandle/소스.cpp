#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static HANDLE	hProcess1;
	static HANDLE	hProcess2;
	switch (msg) {
	case WM_LBUTTONDOWN:
	{
		TCHAR name[] = TEXT("notepad.exe");
		STARTUPINFO	si = { sizeof(si) };
		PROCESS_INFORMATION	pi;
		BOOL b = CreateProcess(NULL, name, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS,NULL, NULL, &si, &pi);

		// 가짜 복사 
		hProcess1 = pi.hProcess;

		// 진짜 복사 
		DuplicateHandle(GetCurrentProcess(),	// 이 프로세스안의
			pi.hProcess,	// 이 핸들을
			GetCurrentProcess(),	// 이 프로세스에 복사하라. 
			&hProcess2,		// hProcess에 핸들값 저장
			0, FALSE,		// 접근 권한, 상속 
			DUPLICATE_SAME_ACCESS);
		if (b) {
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
	}
	return 0;
	case WM_RBUTTONDOWN:
		TerminateProcess(hProcess2, 0);
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
