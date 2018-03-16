#include"std.h"

//
 SHAPE g_CurData;

//dlg handle
HWND g_Modal_ComboBox;
HWND g_Modal_XEdit;
HWND g_Modal_YEdit;
HWND g_Modal_ColorEdit;
BOOL CALLBACK ModalProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//COLORREF tt;
	static	SHAPE * _temp;
	TCHAR str[128];
	int i;

	switch (msg)
	{
		

		//초기화 event
	case WM_INITDIALOG:
	{
		g_Modal_ComboBox = GetDlgItem(hDlg, IDC_MODAL_COMBOBOX);
		_temp = (SHAPE*)lParam;
		SendMessage(g_Modal_ComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT("빨간색"));
		SendMessage(g_Modal_ComboBox, CB_ADDSTRING, 1, (LPARAM)TEXT("녹색"));
		SendMessage(g_Modal_ComboBox, CB_ADDSTRING, 2, (LPARAM)TEXT("파란색"));
		
	/*	TCHAR bf[50];
		TCHAR bf2[50];
		wsprintf(bf,TEXT("%d"), g_CurData.pt.x);
		wsprintf(bf2, TEXT("%d"), g_CurData.pt.y);*/
		SetDlgItemInt(hDlg, IDC_EDIT11, _temp->pt.x, 0);
		SetDlgItemInt(hDlg, IDC_EDIT22, _temp->pt.y, 0);
		switch (_temp->color)//g_CurData.color
		{
		case RGB(255,0,0):
		{
			SetDlgItemText(hDlg, IDC_MODAL_COMBOBOX, TEXT("빨강")); break;
		}
		case  RGB(0, 255, 0):
		{
			SetDlgItemText(hDlg, IDC_MODAL_COMBOBOX, TEXT("녹  색")); break;
		}
		case  RGB(0, 0, 255):
		{
			SetDlgItemText(hDlg, IDC_MODAL_COMBOBOX, TEXT("파  랑")); break;
		}

		}
		//tt = _temp->color;

		return TRUE;
	}
	//메세지 받는 event를 처리하기 위한 영역
	case WM_COMMAND:
	{
		//버튼 입력을 받는 event를 처리하기 위한 영역
		switch (LOWORD(wParam))
		{
		case IDC_MODAL_COMBOBOX:
		{
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
			{
				i = SendMessage(g_Modal_ComboBox, CB_GETCURSEL, 0, 0);
				switch (i)
				{
				case 0: _temp->color = RGB(255, 0,0 ); break; //블루
				case 1:_temp->color = RGB(0, 255, 0); break;
				case 2:_temp->color = RGB(0, 0, 255); break;
				}
				SendMessage(g_Modal_ComboBox, CB_GETLBTEXT, i, (LPARAM)str);
			}
				break;
			case CBN_EDITCHANGE:
			{
			}
				break;
			}
			return 0;
		}
		case IDCANCEL:
		{
			//_temp->color = tt;

			EndDialog(hDlg, IDCANCEL);	return 0;
		}
		case IDOK:
		{
			_temp = (SHAPE*)lParam;
			
			//x 받아오기			
			g_CurData.pt.x = GetDlgItemInt(hDlg, IDC_EDIT11, 0, 0);
			
			//y 받아오기
			g_CurData.pt.y = GetDlgItemInt(hDlg, IDC_EDIT22, 0, 0);
			//색상 받아오기	
			
			EndDialog(hDlg, IDOK);	return 0;
		}

		}
		return TRUE;
	}

	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITMENUPOPUP:
	{
		HMENU hmenu = (HMENU)wParam;
		EnableMenuItem(hmenu, ID_MENU_RED, g_CurData.color == RGB(255, 0, 0) ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hmenu, ID_MENU_GREEN, g_CurData.color == RGB(0, 255, 0) ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hmenu, ID_MENU_BLUE, g_CurData.color == RGB(0, 0, 255) ? MF_GRAYED : MF_ENABLED);
		return 0;
		
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		//======================================
		/*RECT rc = { g_CurData.pt.x-25,g_CurData.pt.y-25,g_CurData.pt.x+25,g_CurData.pt.y+25 };
		InvalidateRect(hwnd, &rc, TRUE);
*/
		HPEN pen = CreatePen(PS_SOLID, 1, g_CurData.color);
		HPEN oldpen = (HPEN)SelectObject(hdc, pen);
		Rectangle(hdc, g_CurData. pt.x - 25, g_CurData. pt.y - 25, g_CurData. pt.x + 25, g_CurData. pt.y + 25);
		DeleteObject(SelectObject(hdc, oldpen));
		//======================================
		EndPaint(hwnd, &ps);
		return 0;
	}
	//마우스 입력
	case WM_LBUTTONDOWN:
	{
		g_CurData.pt.x = LOWORD(lParam);
		g_CurData.pt.y = HIWORD(lParam);
		InvalidateRect(hwnd, 0, TRUE);


		TCHAR buf[40];
		wsprintf(buf, TEXT("마우스 좌표 :X %d  Y %d"), g_CurData.pt.x, g_CurData.pt.y);
		SetWindowText(hwnd, buf);

		return 0;
	}
	//Menu Event
	case WM_COMMAND:
	{
		//버튼 입력을 받는 event를 처리하기 위한 영역
		switch (LOWORD(wParam))
		{
		case ID_MENU_MODAL:
		{
			//SHAPE temp=g_CurData;

			UINT	ret = DialogBoxParam(GetModuleHandle(0),// instance
				MAKEINTRESOURCE(IDD_DIALOG2),	// 다이얼로그 선택 
				hwnd,			// 부모 윈도우
				ModalProc,
				(LPARAM)&g_CurData);			// Proc..
			if (ret == IDOK)
			{
				InvalidateRect(hwnd,0,TRUE);

				TCHAR buf[40];
				wsprintf(buf, TEXT("마우스 좌표 :X %d  Y %d"), g_CurData.pt.x, g_CurData.pt.y);
				SetWindowText(hwnd, buf);

			}
			else
			{

			}
			return 0;
		
		}
		case ID_MENU_RED:
		{
			g_CurData.color = RGB(255, 0, 0);
			InvalidateRect(hwnd, 0, TRUE);
			return 0;
		}
		case ID_MENU_GREEN:
		{
			g_CurData.color = RGB(0, 255, 0);
			InvalidateRect(hwnd, 0, TRUE);
			return 0;
		}
		case ID_MENU_BLUE:
		{
			g_CurData.color = RGB(0, 0, 255);
			InvalidateRect(hwnd, 0, TRUE);
			return 0;
		}
		//파일 종료 기능 응용프로그램 종료
		case ID_MENU_PROGRAMEND:
		{
			PostQuitMessage(0);
			return 0;
		}
		
		}
		
		return 0;
	}
	//Init Event
	case WM_CREATE:	
	{
		g_CurData.color = RGB(255,0,0);
		g_CurData.pt.x = 0;
		g_CurData.pt.y = 0;
		return 0;
	}

		//Re Draw Window Event
	
		//Destroy Event
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPTSTR lpCmdLine, int nShowCmd)
{
	
	WNDCLASS wc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);//LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;			// DefWindowProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	// 2. 등록(레지스트리에)
	RegisterClass(&wc);

	// 3. 윈도우 창 만들기 
	HWND hwnd = CreateWindowEx(0,	// WS_EX_TOPMOST
		TEXT("first"),				// 클래스 명
		TEXT("Hello"),				// 캡션바 내용
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	// 초기 위치 
		0, 0,			// 부모 윈도우 핸들, 메뉴 핸들
		hInst,		// WinMain의 1번째 파라미터 (exe 주소)
		0);			// 생성 인자

					// 4. 윈도우 보여주기
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// 5. Message 
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);//WM_CAHR을 내부적으로 실행 시킨다. 
		DispatchMessage(&msg);
	}
	return 0;
}