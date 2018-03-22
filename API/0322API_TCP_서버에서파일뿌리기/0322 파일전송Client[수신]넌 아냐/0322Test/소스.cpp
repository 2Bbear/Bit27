
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#pragma comment( lib, "ws2_32.lib")

struct FILE_INFO
{
	TCHAR FileName[260];
	int  size;
};

FILE_INFO g_info;

DWORD WINAPI FileClient(void* p)
{
	MessageBox(NULL, TEXT("����"), TEXT(""), MB_OK);
	HWND hwnd = (HWND)p;

	WSADATA w;
	WSAStartup(MAKEWORD(2, 2), &w);

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = inet_addr("192.168.0.33");

	if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		MessageBox(0, TEXT("Connect Error"), TEXT(""), MB_OK);
		return 0;
	}
	//------------------------------------------
	// ȭ�� ������ �����Ѵ�.
	recv(s, (char*)&g_info, sizeof(g_info), 0);

	// �ֽ����忡 �˷��ش�. ->�ֽ����尡 UI�� Update �Ѵ�.!
	PostMessage(hwnd, WM_USER + 100, 0, 0);
	//--------------------------------------------
	TCHAR name[260];
	_tcscpy_s(name, g_info.FileName);
	//_tcscat_s(name, TEXT("_bak"));

	HANDLE hFile = CreateFile(name, GENERIC_WRITE, FILE_SHARE_READ,
		0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	int total = g_info.size;
	int current = 0;
	char buf[4096];
	while (total > current)
	{
		int nRecv = recv(s, buf, 4096, 0);
		if (nRecv <= 0) break;

		DWORD len;
		WriteFile(hFile, buf, nRecv, &len, 0);

		current += nRecv;
		PostMessage(hwnd, WM_USER + 200, 0, (LPARAM)current);
	}
	if (current != total) MessageBox(0, TEXT("Error"), TEXT(""), MB_OK);
	else                    MessageBox(0, TEXT("Success"), TEXT(""), MB_OK);
	closesocket(s);
	CloseHandle(hFile);
	WSACleanup();
	return 0;
}







LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit1, hEdit2, hPrg;

	switch (msg)
	{
	case WM_USER + 100:
	{
		SetWindowText(hEdit1, g_info.FileName);
		TCHAR buf[256];
		wsprintf(buf, TEXT("%d"), g_info.size);
		SetWindowText(hEdit2, buf);

		// ���α׷��� �ʱ�ȭ.
		SendMessage(hPrg, PBM_SETRANGE32, 0, g_info.size);
	}
		return 0;

	case WM_USER + 200:	// lParam �� ���� ���� ũ�Ⱑ �ִ�.
		SendMessage(hPrg, PBM_SETPOS, lParam, 0);
		return 0;

	case WM_LBUTTONDOWN:
	{
		CloseHandle(CreateThread(0, 0, FileClient, (void*)hwnd, 0, 0));
	}
		return 0;







	case WM_CREATE:

		hEdit1 = CreateWindow(TEXT("edit"), 0, WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 10, 200, 20, hwnd, (HMENU)1, 0, 0);

		hEdit2 = CreateWindow(TEXT("edit"), 0, WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 40, 200, 20, hwnd, (HMENU)2, 0, 0);

		hPrg = CreateWindow(PROGRESS_CLASS, 0,
			WS_CHILD | WS_VISIBLE | WS_BORDER | PBS_SMOOTH,
			10, 70, 400, 20, hwnd, (HMENU)3, 0, 0);


		return 0;












	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR	  lpCmdLine, int nShowCmd)
{
	ATOM atom;
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = 0;
	wc.style = 0;

	atom = RegisterClass(&wc);

	if (atom == 0)
	{
		MessageBox(0, TEXT("Fail To RegisterClass"), TEXT("Error"), MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(0, TEXT("first"), TEXT("Hello"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 0, 0,
		hInstance, 0);
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

