#include <windows.h>
#include <tchar.h>

#define MYERRORCHECK MessageBox(hwnd, TEXT("adad"), TEXT("adad"), 0);

/*
1. �⺻���� ���콺 �Է� �ޱ�
2. ���콺���� ��ǥ �о� ����
3. ���콺�� ����Ű �ޱ�
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
		//����Ű ���� �˻�
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
		//��ǥ�� ��������
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		TCHAR xText[20];
		TCHAR yText[20];
		wsprintf(xText, TEXT("x�� :%d"), x);
		wsprintf(yText, TEXT("y�� :%d"), y);
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

	wc.style = CS_HREDRAW | CS_VREDRAW |CS_DBLCLKS;//////////////////////////////////////////////////���� Ŭ���� ���� CS_DBLCLKS�� �߰���
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
