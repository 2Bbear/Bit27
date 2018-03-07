//�ҽ�.cpp
#include "std.h"


vector<SHAPE*> g_drawList;
SHAPE g_drawCurrent;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//Init Event
	case WM_CREATE:			return OnCreate(hwnd);
	//Re Draw Window Event
	case WM_PAINT:			return OnPaint(hwnd);
	//Timer Event
	case WM_TIMER: return OnTimer(hwnd,wParam);
	//key Event
	case WM_LBUTTONDOWN:	return OnLButtonDown(hwnd,lParam);
	case WM_RBUTTONDOWN:	return OnRButtonDown(hwnd);
	case WM_KEYDOWN: return OnKeyDown(hwnd,wParam);
	case WM_CHAR: return OnChar(hwnd,wParam);
		
	//Destroy Event
	case WM_DESTROY:		return OnDestroy(hwnd);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}



int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPTSTR lpCmdLine, int nShowCmd)
{
	AllocConsole(); // console â ����

	freopen("CONOUT$",   // console ��
		"wt",        // text write ����
		stdout);	  // stdout �� ����..
	// 1. ������ Ŭ���� ����� 
	WNDCLASS wc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;			// DefWindowProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	// 2. ���(������Ʈ����)
	RegisterClass(&wc);

	// 3. ������ â ����� 
	HWND hwnd = CreateWindowEx(0,	// WS_EX_TOPMOST
		TEXT("first"),				// Ŭ���� ��
		TEXT("Hello"),				// ĸ�ǹ� ����
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	// �ʱ� ��ġ 
		0, 0,			// �θ� ������ �ڵ�, �޴� �ڵ�
		hInst,		// WinMain�� 1��° �Ķ���� (exe �ּ�)
		0);			// ���� ����

	// 4. ������ �����ֱ�
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// 5. Message 
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);//WM_CAHR�� ���������� ���� ��Ų��. 
		DispatchMessage(&msg);
	}
	return 0;
}