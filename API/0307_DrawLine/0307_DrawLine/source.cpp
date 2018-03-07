#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100
/*
1. ���� SetROP2 �� ���� �������� �� ������ ������ �׷ȴ� �� ���� ����� ���� ��?
SetROP2�� ���� �׷����� ���ο� ������ �� �Ӽ��� �������� �ٲ۴�.

���� ��� : ȭ�鿡 �������� �εεΊP ���� ���̴�.

���� ��� : �׳� �����̸鼭 ������ ����µ� ���� ���� ������ �ʴ´�.
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;
	static BOOL bNowDraw = FALSE;


	switch (msg)	{
	case WM_CREATE:
	{
					  return 0;
	}
		
	case WM_LBUTTONDOWN:
	{
						   start = MAKEPOINTS(lParam);
						   end = start;
						   bNowDraw = TRUE;

						   return 0;
	}
	case WM_LBUTTONUP:
	{
						 bNowDraw = FALSE;
						 HDC hdc = GetDC(hwnd);
						 MoveToEx(hdc, start.x, start.y, NULL);
						 LineTo(hdc, end.x, end.y);
						 ReleaseDC(hwnd, hdc);

						   return 0;
	}
	case WM_MOUSEMOVE:
	{
						 if (bNowDraw)
						 {
							 HDC hdc = GetDC(hwnd);
							 SetROP2(hdc, R2_NOT);//���� ������ ���� ���� ���� �����ϱ� ���ؼ�, �������̸� �������
							 //�� ��Ÿ�� ����
							 HPEN pen = CreatePen(1, 1, RGB(0, 0, 0));
							 HPEN oldPen = (HPEN)SelectObject(hdc,pen);

							 MoveToEx(hdc, start.x, start.y, NULL);
							 LineTo(hdc, end.x, end.y);

							 //�� ��Ÿ�� ����
							 DeleteObject(SelectObject(hdc,oldPen));

							 end = MAKEPOINTS(lParam);
							 MoveToEx(hdc, start.x, start.y, NULL);
							 LineTo(hdc, end.x, end.y);
							 ReleaseDC(hwnd, hdc);
						 }

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
