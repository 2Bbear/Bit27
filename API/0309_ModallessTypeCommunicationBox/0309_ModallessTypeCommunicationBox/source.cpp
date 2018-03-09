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
HWND g_hDlg; // Dialog 의 핸들.
#define WM_APPLY	WM_USER + 100
//------------------------------------


//대화 상자 프로시저.
BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	static DATA *pData;
	switch (msg)
	{
	// Dialog가 처음 나타날때 발생. 각 콘트롤을 초기화 한다.
	case WM_INITDIALOG:
	{
		pData = (DATA*)lParam;
		SetDlgItemText(hDlg, IDC_EDIT1, pData->str);
		SetDlgItemInt(hDlg, IDC_EDIT2, pData->num, 0);
		HWND h = GetDlgItem(hDlg, IDOK);
		SetWindowText(h, TEXT("적용"));

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
	return FALSE; // 메세지 처리를 안한경우..
}

//윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static DATA data = { TEXT("홍길동"), 20 };

	switch (msg) 
	{
	case WM_CREATE:
		return 0;
		//dialog가 보내는 메세지
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
			// 모달리스 만들기.
			g_hDlg = CreateDialogParam(GetModuleHandle(0),MAKEINTRESOURCE(IDD_DIALOG1),hwnd,DlgProc, (LPARAM)&data);
			ShowWindow(g_hDlg, SW_SHOW);
		}
		else
			SetFocus(g_hDlg);//이미 만들어진 경우 focus이동

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
	// 1. 윈도우 클래스 만들기 
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
	// 2. 등록(레지스트리에)
	RegisterClass(&wc);
	// 3. 윈도우 창 만들기 
	HWND hwnd = CreateWindowEx(0,	// WS_EX_TOPMOST
		TEXT("first"),		// 클래스 명
		TEXT("Hello"),		// 캡션바 내용
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,// 초기 위치 
		0, 0,			// 부모 윈도우 핸들, 메뉴 핸들
		hInst,		// WinMain의 1번째 파라미터 (exe 주소)
		0);		// 생성 인자
				// 4. 윈도우 보여주기
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// 5. Message 
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); //분배기의 역할
	}
	return 0;
}
