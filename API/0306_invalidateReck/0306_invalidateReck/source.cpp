#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100
/*
�׽�Ʈ ����

1. InvalidateRect�� ���������� WM_PAINT�� ȣ���ϴ� ��?
 L��ư�� 100~150 ���̿� �簢���� �׸���.
 R��ư�� 0~50������ �簢���� �����.

 WM_PAINT�� 0~50���̿� �簢���� �׸���
            100~150 ������ �簢���� �����.
 ���� ��� : 
 R��ư�� ������ 0~50 ������ �簢���� ��� ���� ���� ���̰�, 100~150������ �簢���� ����� ���̴�.
 
 ���� �Ǵ� ��� :
 R��ư ó�� �ȿ��� 100~150 ������ �簢���� ����� ������ ���� ���µ� 100~150 ������ �簢���� �������.
 �� ���� R ��ư �ȿ� �ִ� InvalidateRect�� ���������� WM_PAINT�� ȣ���Ѵٴ� �ǹ��̴�.

 ���� - ����� ��ġ

2. ���������� TRUE ���� ������?
 L��ư���� ���� �簢���� R��ư���� �����غ���
 TRUE ���� �� ��� �۵��ϴ� ��
 FALSE ���� �� ��� �۵��ϴ� �� �˾ƺ���

 ���� ��� : TRUE �϶� �簢���� �ٷ� ����� ���̴�. FALSE �϶� �簢���� ������� �ʰ� ���� ���� ���̴�.

 ���� - ����� ��ġ

 ���
 InvalidateRect�� �ش� ��ġ�� ��ȿȭ ������ �����Ѵ�. 
 TRUE ���� �� WM_PAINT �޼����� �ٷ� ���ν����� �����Ѵ�.
 FALSE ���� �� WM_PAINT �޼����� �޼��� ť�� �־� ���´�. 


*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)	{
	case WM_CREATE:
		return 0;

	case WM_LBUTTONDOWN:
	{
						   HDC hdc = GetDC(hwnd);
						   Rectangle(hdc, 100, 0, 150, 50);
						   ReleaseDC(hwnd, hdc);

		return 0;
	}
	case WM_RBUTTONDOWN:
	{
						  
		//���� 1		   
		RECT r = { 0, 0, 50, 50 };
		InvalidateRect(hwnd, &r, TRUE);//True���� �ϸ� �ٷ� �ݿ���

		//���� 2
		//RECT r = { 100, 0, 150, 50 };
		//InvalidateRect(hwnd, &r, TRUE);//True���� �ϸ� �ٷ� �ݿ���
		return 0;
	}
		//���� 1
	case WM_PAINT:
	{
					 RECT r = { 100, 0, 150, 50 };
					 InvalidateRect(hwnd, &r, FALSE);//True���� �ϸ� �ٷ� �ݿ���
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		HBRUSH old = (HBRUSH)SelectObject(hdc, brush);
		
		Rectangle(hdc,0,0,50,50);
		
		DeleteObject(SelectObject(hdc, old));
		EndPaint(hwnd, &ps);

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
