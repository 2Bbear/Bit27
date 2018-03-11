#include <windows.h>
#include <tchar.h>
#include"resource.h"
#define WM_JJHMESSAGE WM_USER+100
/////////

typedef struct tagDATA {
	TCHAR str[20];
	int   num;
}DATA;
/////////////
//대화 상자 프로시저
BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	//
	static DATA *pData;//static인 이유는 이 다이얼로그 가 끝나게 되면 데이타가 날라가기 때문에 static 형태 해서 데이터가 남아 있도록 해야한다.

	switch (msg)
	{
		// Dialog가 처음 나타날때 발생. 각 콘트롤을 초기화 한다.
	case WM_INITDIALOG: {
		pData = (DATA*)lParam;
		SetDlgItemText(hDlg, IDC_EDIT1, pData->str);
		SetDlgItemInt(hDlg, IDC_EDIT2, pData->num, 0);
	}
						break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			//종료될때 불려와지는 메세지
		case IDOK:
			GetDlgItemText(hDlg, IDC_EDIT1, pData->str, sizeof(pData->str));
			pData->num = GetDlgItemInt(hDlg, IDC_EDIT2, 0, 0);
			//다이얼로그를 죽이는 함수, 두번째 매개변수는 부모 윈도우에게 보내지는 메세지
			EndDialog(hDlg, IDOK);
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
	switch (msg) {
	//초기 생성 메세지
	case WM_CREATE:
		return 0;
	//마우스 왼쪽 버튼 메세지
	case WM_LBUTTONDOWN:
	{
		//자료 생성
		DATA  data = { TEXT("홍길동"), 20 };
		//대화 창 기본 코드
			//dialogBox 생성
		UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
			MAKEINTRESOURCE(IDD_DIALOG1),
			hwnd,		// 부모
			DlgProc, // 메세지 함수.
			(LPARAM)&data); // WM_INITDIALOG의 lParam로 전달된다. //이 함수가 끝날 때까지 메인 윈도우는 아무것도 못한다
		//ret이 성공적으로 수행 되었을 때
		if (ret == IDOK) {
			// 이제 Dialog에 입력한 값은 data에 있다.
			TCHAR buf[128];
			wsprintf(buf, TEXT("%s / %d"), data.str, data.num);
			SetWindowText(hwnd, buf);
		}
		return 0;
	}
	//프로그램 종료 메세지
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
