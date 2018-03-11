#include <windows.h>
#include <tchar.h>

#define MYERRORCHECK MessageBox(hwnd, TEXT("adad"), TEXT("adad"), 0);
/*
���콺 ĸ���ϴ� ���
1. down �޼����� ĸó�� �ִ´�.
2. up  �޼����� ����� �Ѵ�.

*/
//�̰� ���߶��� ���ݾ�.  �־��� �ڵ鰪�� ������ �ִ� �������� ������ ����ϴ� �Լ� 
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
			//�Ű������� �ڵ��� ���콺 Ŀ���� ĸ���ϰ� ��
			SetCapture(hwnd);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			//���� � �����찡 Ŀ���� ĸ���ߴ°�
			if (GetCapture() == hwnd)
			{
				//���� ĸ�ĵ� ��Ȳ�� ����
				ReleaseCapture();
				POINT pt;
				//���� ���콺 Ŀ���� ��ġ ���� ����
				GetCursorPos(&pt);
				//���� Ŀ���� ��ġ�� �������� �ڵ� ���� �������� �Լ�
				HWND hwndDest = WindowFromPoint(pt);
				PrintWindowInfo(hwndDest);
			}
		}
		//���� ���콺 Ŀ���� ��ġ�� ���� ǥ���ٿ� ����ϴ� �Լ�
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

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;//////////////////////////////////////////////////���� Ŭ���� ���� CS_DBLCLKS�� �߰���
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
