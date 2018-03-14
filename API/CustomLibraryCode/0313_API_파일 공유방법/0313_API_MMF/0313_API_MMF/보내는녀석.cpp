#pragma comment (linker, "/subsystem:windows")

#include<Windows.h>
#include<tchar.h>

typedef struct _LINE {
	POINTS ptFrom;
	POINTS ptTo;
} LINE;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static HANDLE hEvent, hMap;
	static LINE*  pData;//페이징 파일에 잡힌 메모리로 쓸 변수
	static POINTS ptFrom;
	switch (msg)
	{
	case WM_LBUTTONDOWN: ptFrom = MAKEPOINTS(lParam); return 0;
	case WM_MOUSEMOVE:
		if (wParam & MK_LBUTTON)
		{
			POINTS pt = MAKEPOINTS(lParam);
			HDC hdc = GetDC(hwnd);
			MoveToEx(hdc, ptFrom.x, ptFrom.y, 0);
			LineTo(hdc, pt.x, pt.y);
			ReleaseDC(hwnd, hdc);

			//3  MMF 에 넣는다.
			pData->ptFrom = ptFrom;
			pData->ptTo = pt;
			//해당 핸들의 커널 오브젝트를 signal로 변경한다.
			SetEvent(hEvent);
			//구해진 커서 좌표 값을 저장 하기 위해 전역 POINT에 저장한다.
			ptFrom = pt;
		}
		return 0;
	case WM_CREATE:
		//자식 프로세스가 이 핸들을 상속 할 수 없음,자동으로 재설정하는 이벤트 객체를 만들고 스레드가 해제 된 후 이벤트 상태를 unsignal로 설정한다, 객체의 초기 상태를 알리지 않는다, 객체의 이름
		//마지막 텍스트가 이벤트 이름
		hEvent = CreateEvent(0, 0, 0, TEXT("DRAW_SIGNAL"));

		//1 맵핑 객체 생성
		hMap = CreateFileMapping((HANDLE)-1,0, PAGE_READWRITE, 0, sizeof(LINE), TEXT("map"));
		//2 가상 주소와 파일을 연결
		pData = (LINE*)MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, 0);
		if (pData == 0)
		{
			MessageBox(0, TEXT("Fail"), TEXT(""), MB_OK);			
		}
		return 0;
	case WM_DESTROY:
		UnmapViewOfFile(pData);
		CloseHandle(hMap);
		CloseHandle(hEvent);
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
		TEXT("보내는녀석"),		// 캡션바 내용
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
