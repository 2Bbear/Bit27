#include"resource.h"

#include <windows.h>
#include <tchar.h>



#define WM_JJHMESSAGE WM_USER+100
/////////================

typedef struct tagDATA {
	TCHAR str[20];
	int   num;
}DATA;
/////////////=============

//------------------------------------
HWND g_hDlg; // Dialog �� �ڵ�.
#define WM_APPLY	WM_USER + 100
//------------------------------------


//��ȭ ���� ���ν���.
BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	static DATA *pData;
	switch (msg)
	{
	// Dialog�� ó�� ��Ÿ���� �߻�. �� ��Ʈ���� �ʱ�ȭ �Ѵ�.
	case WM_INITDIALOG:
	{
		pData = (DATA*)lParam;
		SetDlgItemText(hDlg, IDC_EDIT1, pData->str);
		SetDlgItemInt(hDlg, IDC_EDIT2, pData->num, 0);
		HWND h = GetDlgItem(hDlg, IDOK);
		SetWindowText(h, TEXT("����"));

	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case IDOK:
			GetDlgItemText(hDlg, IDC_EDIT1, pData->str, sizeof(pData->str));
			pData->num = GetDlgItemInt(hDlg, IDC_EDIT2, 0, 0);
			SendMessage(GetParent(g_hDlg), WM_APPLY, 0, 0);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
	}
	return FALSE; // �޼��� ó���� ���Ѱ��..
}

//������ ���ν���
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static DATA data = { TEXT("ȫ�浿"), 20 };

	switch (msg) 
	{
	case WM_CREATE:
		return 0;
		//dialog�� ������ �޼���
	case WM_APPLY:
	{
		TCHAR buf[128];
		wsprintf(buf, TEXT("%s / %d"), data.str, data.num);
		SetWindowText(hwnd, buf);

		return 0;
	}
	
	case WM_LBUTTONDOWN:
	{
		if (g_hDlg == 0)
		{
			// ��޸��� �����.
			g_hDlg = CreateDialogParam(GetModuleHandle(0),MAKEINTRESOURCE(IDD_DIALOG1),hwnd,DlgProc, (LPARAM)&data);
			ShowWindow(g_hDlg, SW_SHOW);
		}
		else
			SetFocus(g_hDlg);//�̹� ������� ��� focus�̵�

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
