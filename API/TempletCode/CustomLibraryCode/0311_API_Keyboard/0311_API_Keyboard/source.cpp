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
		//Scan Code ��������=======================================================================
		//scan�ڵ带 ��ȯ�ϱ� ���� ��ũ��
		#define GetScanCode(x) ( ( x >> 16) & 0x00FF)
		TCHAR buf[30];
		wsprintf(buf, TEXT("Scan Code : %d\n"), GetScanCode(lParam));

		//���� key code ��������===================================================================
		switch (wParam)
		{
		case VK_BACK: {}break;
		case VK_TAB: {}break;
		case VK_RETURN: {}break;
		case VK_GAMEPAD_LEFT_TRIGGER: {}break;
			//��� ���� ����.
			//�׳� ���ڵ� �޾� �� �� ���� ��ҹ��� ���� ����
		case 'A': {MessageBox(hwnd,TEXT("d"), TEXT("d"),0); }break;
		}

		//����Ű �Է¹ޱ�===========================================================================
		if (wParam==VK_F1&& GetKeyState(VK_CONTROL) & 0xFF00) // ����� �ִ� ���
		{
			MessageBox(0, TEXT("CRTL+ F1"), TEXT(""), MB_OK);
		}
		if (wParam == VK_F2 && GetKeyState(VK_CONTROL) & 0x00FF) //��� ���
		{
			MessageBox(0, TEXT("CRTL+ F2"), TEXT(""), MB_OK);
		}
		return 0;
		//SHORT GetAsynckKeyState(int vKey); ���� Ű������ ���¸� �����ϴ� �Լ�
		//BOOL GetKeyboardState( PBYTE lpKeyState) ��� ���� Ű�� ���¸� ���´�.
	}
	case WM_KEYUP:
	{
		switch (wParam)
		{

		}
		return 0;
	}

	//ALt ����Ű, �ݵ�� ����Ʈ ������� �Ѱ���� �Ѵ�.===========================================
	case WM_SYSKEYDOWN:
	{
		switch (wParam)
		{
		case 'G':
		{
			MessageBox(hwnd, TEXT("G"), TEXT("G�󱸿�!"), 0);
			break;
		}
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	case WM_SYSKEYUP:
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	//�ƽ�Ű �� ��������==========================================================================
	case WM_CHAR:
	{
		switch (wParam)
		{
		case 'c':
		{
			MessageBox(0, TEXT("c��"), TEXT(""), MB_OK);
			

			return 0;
		}
		case 'C':
		{
			MessageBox(0, TEXT("ūC��"), TEXT(""), MB_OK);
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
