#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100
void PrintTime(const SYSTEMTIME* pst, HDC hdc, int y)
{
	TCHAR date[256] = { 0 };
	TCHAR time[256] = { 0 };
	GetDateFormat(LOCALE_USER_DEFAULT, 0, pst, TEXT("yyyy년 M월d일"), date, 256);
	GetTimeFormat(LOCALE_USER_DEFAULT, 0, pst, TEXT("tt h시 m분 s초"), time, 256);
	TextOut(hdc, 10, y + 10, date, wcslen(date));
	TextOut(hdc, 10, y + 30, time, wcslen(time));
}

BOOL PrintFileTime(HANDLE hFile, HDC hdc)
{
	FILETIME ftCreate, ftAccess, ftWrite;
	SYSTEMTIME stUTCCreate, stLocalCreate, stUTCAccess, stLocalAccess, stUTCWrite, stLocalWrite;
	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))  return FALSE;
	FileTimeToSystemTime(&ftWrite, &stUTCCreate);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTCCreate, &stLocalCreate);
	FileTimeToSystemTime(&ftAccess, &stUTCAccess);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTCAccess, &stLocalAccess);
	FileTimeToSystemTime(&ftWrite, &stUTCWrite);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTCWrite, &stLocalWrite);
	//Creation Time
	PrintTime(&stLocalCreate, hdc, 0);
	//Last-Access Time :
	PrintTime(&stLocalAccess, hdc, 50);
	//"Last-Write Time :
	PrintTime(&stLocalWrite, hdc, 100);
	return TRUE;
}
typedef VOID(CALLBACK * TIMERPOC)(HWND, UINT, UINT_PTR, DWORD);
void CALLBACK MyTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	RECT rc = { 200, 0, 500, 100 };
	//InvalidateRect(hWnd, &rc, TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)	{
	case WM_CREATE:
	{
		//Timer Init
		 SetTimer(hwnd, 1, 1000, MyTimerProc);//(타이머 메세지를 받을 윈도우,타이머의 번호 지정,주기값,호출될 함수) 내부 적으로 WM_TIMER 메세지를 보냄 wParam에 Timer ID를 같이 넣어서 보냄
		SendMessage(hwnd, WM_TIMER, 1, NULL);//강제로 WM_TIMER를 실행시키는 함수

		return 0;
	}
		return 0;
	case WM_LBUTTONDOWN:
	{
						   //C:\Users\User\Desktop\ffff.txt
						   HANDLE hFile = CreateFile(TEXT("C:\\Users\\User\\Desktop\\ffff.txt"), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);//파일 객체 생성 함수
						   HDC hdc = GetDC(hwnd);
						   PrintFileTime(hFile, hdc);
						   ReleaseDC(hwnd, hdc);
						   return 0;
	}
	case WM_PAINT:
	{
					 PAINTSTRUCT ps;
					 HDC hdc = BeginPaint(hwnd, &ps);
					 //======================================
					 SYSTEMTIME st;
					 GetLocalTime(&st);
					 TCHAR buf[20];
					 wsprintf(buf, TEXT("현재 시간 : %d:%d:%d\0"), st.wHour, st.wMinute, st.wSecond);
					 
					 RECT rc = {200,0,500,100};
					 
					 DrawText(hdc, buf, -1, &rc, DT_LEFT);
					 //SetWindowText(hwnd, buf);
					 //======================================
					 EndPaint(hwnd, &ps);
					 return 0;
	}
	case WM_DESTROY:
	{
		KillTimer(hwnd, 1);
		PostQuitMessage(0);
		return 0;
	}
		
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
