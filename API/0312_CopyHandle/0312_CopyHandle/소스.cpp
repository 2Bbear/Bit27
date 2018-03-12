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

		// ��¥ ���� 
		hProcess1 = pi.hProcess;

		// ��¥ ���� 
		DuplicateHandle(GetCurrentProcess(),	// �� ���μ�������
			pi.hProcess,	// �� �ڵ���
			GetCurrentProcess(),	// �� ���μ����� �����϶�. 
			&hProcess2,		// hProcess�� �ڵ鰪 ����
			0, FALSE,		// ���� ����, ��� 
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
	// 1. ������ Ŭ���� ����� 
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
	// 2. ���(������Ʈ����)
	RegisterClass(&wc);
	// 3. ������ â ����� 
	HWND hwnd = CreateWindowEx(0,	// WS_EX_TOPMOST
		TEXT("first"),		// Ŭ���� ��
		TEXT("Hello"),		// ĸ�ǹ� ����
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,// �ʱ� ��ġ 
		0, 0,			// �θ� ������ �ڵ�, �޴� �ڵ�
		hInst,		// WinMain�� 1��° �Ķ���� (exe �ּ�)
		0);		// ���� ����
				// 4. ������ �����ֱ�
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// 5. Message 
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); //�й���� ����
	}
	return 0;
}
