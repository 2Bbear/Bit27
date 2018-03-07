#include <windows.h>
#include <tchar.h>

#define WM_JJHMESSAGE WM_USER+100
void PrintTime(const SYSTEMTIME* pst, HDC hdc, int y)
{
	TCHAR date[256] = { 0 };
	TCHAR time[256] = { 0 };
	GetDateFormat(LOCALE_USER_DEFAULT, 0, pst, TEXT("yyyy�� M��d��"), date, 256);
	GetTimeFormat(LOCALE_USER_DEFAULT, 0, pst, TEXT("tt h�� m�� s��"), time, 256);
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
		 SetTimer(hwnd, 1, 1000, MyTimerProc);//(Ÿ�̸� �޼����� ���� ������,Ÿ�̸��� ��ȣ ����,�ֱⰪ,ȣ��� �Լ�) ���� ������ WM_TIMER �޼����� ���� wParam�� Timer ID�� ���� �־ ����
		SendMessage(hwnd, WM_TIMER, 1, NULL);//������ WM_TIMER�� �����Ű�� �Լ�

		return 0;
	}
		return 0;
	case WM_LBUTTONDOWN:
	{
						   //C:\Users\User\Desktop\ffff.txt
						   HANDLE hFile = CreateFile(TEXT("C:\\Users\\User\\Desktop\\ffff.txt"), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);//���� ��ü ���� �Լ�
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
					 wsprintf(buf, TEXT("���� �ð� : %d:%d:%d\0"), st.wHour, st.wMinute, st.wSecond);
					 
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
