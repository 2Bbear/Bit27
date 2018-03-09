#include"std.h"


/////////================

/*
왜 안되는걸까아아아아아아아아아아아아
안된다아아아아아아아아
다이얼로그창으로 실시간으로 그려지지 않음 이유를 모르겠어

*/
/////////////=============

//------------------------------------
HWND g_hDlg; // Dialog 의 핸들.
#define WM_APPLY	WM_USER + 100
#define WM_CANCLEMUNU WM_USER+101
//------------------------------------


//대화 상자 프로시저.
BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	static LINEDATA *pData;
	switch (msg)
	{
		//
		// Dialog가 처음 나타날때 발생. 각 콘트롤을 초기화 한다.
		case WM_INITDIALOG:
		{
			pData = (LINEDATA*)lParam;
			//edit 초기화
			SetDlgItemInt(hDlg, IDC_EDIT1, pData->w_count, 0);
			SetDlgItemInt(hDlg, IDC_EDIT2, pData->h_count, 0);
			//슬라이더 초기화
			//1>범위 설정 
			SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_SETRANGE, FALSE, MAKELPARAM(1, 5));
			//2>초기값 입력
			SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_SETPOS, TRUE, pData->opa_pen);

			//OK버튼 초기화
			HWND h = GetDlgItem(hDlg, IDOK);
			SetWindowText(h, TEXT("적용"));
			
			return TRUE;

		}
		break;
		//스크롤 움직이면 발생하는 메세지
		case WM_HSCROLL:
		{
			int n = 0;

			pData->opa_pen = SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_GETPOS, TRUE, (LPARAM)&n);
			return 0;
		}
		//메세지를 받는 부분
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDOK:
			{
				pData->w_count = GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
				pData->h_count = GetDlgItemInt(hDlg, IDC_EDIT2, 0, 0);

				SendMessage(GetParent(g_hDlg), WM_APPLY, 0, 0);
				return TRUE;
			}
				

			case IDCANCEL:
			{
				SendMessage(GetParent(g_hDlg), WM_CANCLEMUNU, 0, 0);
				EndDialog(hDlg, IDCANCEL);
				return TRUE;
			}
				
			}
		}
		return FALSE; // 메세지 처리를 안한경우..
	}
	return FALSE; // 메세지 처리를 안한경우..
}

//윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static LINEDATA data = { 5,5,1 };

	switch (msg)
	{
		//초기화 메세지
		case WM_CREATE:
		{

			return 0;
		}
		//화면 그리는 메세지
		case WM_PAINT:
		{

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			RECT rc;
			GetClientRect(hwnd, &rc);

			//=======================================================
			//간격
			//세로 간격
			double w_Vvalue = rc.right / (data.w_count + 1);
			//가로 간격
			double w_Hvalue = rc.bottom / (double)(data.h_count + 1);
			//========================================================
			//그리기
			//hdc setting
			HPEN pen = CreatePen(PS_SOLID, 1, RGB(data.opa_pen * 50, data.opa_pen * 50, data.opa_pen * 50));
			HPEN oldPen = (HPEN)SelectObject(hdc, pen);
			//세로
			for (double i = 0; i<rc.right; i += w_Vvalue)
			{
				MoveToEx(hdc, i, 0, 0);
				LineTo(hdc, i, rc.bottom);
			}
			//가로
			for (double i = 0; i<rc.bottom; i += w_Hvalue)
			{
				MoveToEx(hdc, 0, i, 0);
				LineTo(hdc, rc.right, i);
			}

			//===================
			DeleteObject(SelectObject(hdc, oldPen));

			EndPaint(hwnd, &ps);
			return 0;
		}

		//dialog가 보내는 Custom Message================================================
			//OK버튼을 눌렀을 때
		case WM_APPLY:
		{
			
			//g_hDlg = 0;

			return 0;
		}
			//Cancle 버튼을 눌렀을 때
		case WM_CANCLEMUNU:
		{
			//g_hDlg = 0;
			return 0;
		}
		//======================================================================
		//왼쪽 클릭
		case WM_LBUTTONDOWN:
		{
			if (g_hDlg == 0)
			{
				// 모달리스 만들기.
				g_hDlg = CreateDialogParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc, (LPARAM)&data);
				//만들어진 모달리스 창을 출력하는 함수
				ShowWindow(g_hDlg, SW_SHOW);
			}
			else
				SetFocus(g_hDlg);//이미 만들어진 경우 focus이동

			return 0;
		}
		//오른족 클릭
		case WM_RBUTTONDOWN:
		{

			return 0;
		}


		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine,int nShowCmd)
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
