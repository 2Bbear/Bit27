#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100
/*
�����쿡 ���� �׸��� ���α׷�

*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;
	//static BOOL bNowDraw = FALSE;

	switch (msg)	{

	case WM_CREATE:
		return 0;
		//l��ư ������ ��
	case WM_LBUTTONDOWN:
	{
						   HDC hdc = GetDC(hwnd);
						  SetMapMode(hdc, MM_LOMETRIC);
						  Rectangle(hdc,0,0,100,-100);

						  POINT pt = { LOWORD(lParam), HIWORD(lParam) };
						  DPtoLP(hdc, &pt, 1);
						  Rectangle(hdc, pt.x,pt.y,pt.x+50,pt.y+50); // ��� ���� �����ָ� �̰� �̻��ϰ� ��µ�
						  ReleaseDC(hwnd,hdc);
						 /*  start = MAKEPOINTS(lParam);
						   end = start;
						   SetCapture(hwnd);*/
						 //  bNowDraw = TRUE;

						   return 0;

	}
		
	case WM_LBUTTONUP:
	{
						 ReleaseCapture();
						// bNowDraw = FALSE;//���̻� ���콺 ���꿡�� �׸��� �׷����� �ʵ��� ��
						 HDC hdc = GetDC(hwnd);
						 MoveToEx(hdc, start.x, start.y, NULL);
						 LineTo(hdc, end.x, end.y);
						 ReleaseDC(hwnd, hdc);

						 return 0;
	}
		
	case WM_MOUSEMOVE:
	{
						 if (GetCapture()==hwnd)//if(bNowDraw)
						 {
							 HDC hdc = GetDC(hwnd);
							 SetROP2(hdc, R2_NOT);//������� ����
							 MoveToEx(hdc, start.x, start.y, NULL);//(dc, ù ���콺 ��ǥ.)
							 LineTo(hdc, end.x, end.y);

							 end = MAKEPOINTS(lParam);
							 
							 MoveToEx(hdc, start.x, start.y, NULL);
							 LineTo(hdc, end.x, end.y);
							 ReleaseDC(hwnd, hdc);
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
