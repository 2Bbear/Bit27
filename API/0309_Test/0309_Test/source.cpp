#include"std.h"

#define WM_JJHMESSAGE WM_USER+100
/*
�� �߱�
���� Ŭ���� ��޷�
������ Ŭ���� ��޸�����
*/
//�� ����
//���� �� ��
double w_vcount = 5;
//���� �� ��
double w_hcount = 10;
//=======================================================
//��
//���� ���
int opa_pen = 1;//1~5
//======================================================
LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd,&ps);

	RECT rc;
	GetClientRect(hwnd, &rc);
	
	//=======================================================
	//����
		//���� ����
	double w_Vvalue= rc.right / (w_vcount +1);
		//���� ����
	double w_Hvalue = rc.bottom / (double)(w_hcount + 1);
	//========================================================
	//�׸���
		//hdc setting
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(opa_pen*50, opa_pen * 50, opa_pen * 50));
	HPEN oldPen = (HPEN)SelectObject(hdc,pen);
		//����
	for (double i=0;i<rc.right;i+= w_Vvalue)
	{
		MoveToEx(hdc,i, 0, 0);
		LineTo(hdc, i, rc.bottom);
	}
		//����
	for (double i=0;i<rc.bottom;i+= w_Hvalue)
	{
		MoveToEx(hdc, 0, i, 0);
		LineTo(hdc, rc.right,i);
	}
	
	//===================
	DeleteObject(SelectObject(hdc,oldPen));

	EndPaint(hwnd, &ps);
	return 0;
}

LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//���� ����
	DATA data = { w_vcount ,w_hcount,opa_pen };

	UINT	ret = DialogBoxParam(GetModuleHandle(0),// instance
		MAKEINTRESOURCE(IDD_DIALOG1),	// ���̾�α� ���� 
		hwnd,			// �θ� ������
		DlgProc,(LPARAM)&data);			// Proc..

	if (ret==IDOK)
	{
		w_vcount = data.w_count;
		w_hcount = data.h_count;
		opa_pen = data.opa_pen;
		InvalidateRect(hwnd, 0, TRUE);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CREATE:
		return 0;
	case WM_LBUTTONDOWN:

		return OnLButtonDown(hwnd, wParam, lParam);
	case WM_RBUTTONDOWN:
		return 0;
	case WM_PAINT:
	{
		return OnPaint(hwnd, wParam, lParam);
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
