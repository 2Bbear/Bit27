#include<Windows.h>
#include<tchar.h>
#include <math.h>
#define NUM    1000
#define TWOPI  (2 * 3.14159)//사인값

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)  {
	static int  	cxClient, cyClient;
	HDC         	hdc;
	int         	i;
	PAINTSTRUCT 	ps;
	POINT       	apt[NUM];
	switch (message)      
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		MoveToEx(hdc, 0, cyClient / 2, NULL);
		LineTo(hdc, cxClient, cyClient / 2);
		for (i = 0; i < NUM; i++)           {
			apt[i].x = i * cxClient / NUM;
			apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / NUM)));
		}
		Polyline(hdc, apt, NUM);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
void windowClassSetting(WNDCLASS & _wc, HINSTANCE _hInst, LPTSTR  str)
{
	_wc.cbWndExtra = 0; //윈도우 정보를 저장할 수 있는 예약 영역이다. 사용하지 않을 경우 0으로 지정한다
	_wc.cbClsExtra = 0; //클래스 정보를 저장할 수 있는 예약 영역이다. 사용하지 않을 경우는 0으로 지정한다.
	_wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH); // 배경색 , 미리 제공되는 객체들이 있는데 거기서 화이트 브러쉬를 가져옴
	_wc.hCursor = LoadCursor(0, IDC_ARROW);//커서 , 0 부분에 hinst를 넣으면 내가 만든 것을 넣겠다는 의미
	_wc.hIcon = LoadIcon(0, IDI_APPLICATION);//아이콘
	_wc.hInstance = _hInst; //윈도우 프로시저를 담은 모듈의 핸들이며 WinMain의 첫번째 인자로 전달된 값을 대입한다.
	_wc.lpfnWndProc = WndProc;			// DefWindowProc; 자신이 직접 만든 메세지 처리 함수를 등록해야함. 

	_wc.lpszClassName = str;//TEXT("First");//검색을 위한 키값
	_wc.lpszMenuName = 0; //윈도우에 부착할 메뉴를 지정한다. 메뉴는 일반적으로 리소스 에디터에 의해 별도로 만들어진다. 사용하지 않을 경우는 널로 지정한다.
	_wc.style = 0;
}
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR IpCmdLine, int nShowCmd)
{
	MessageBox(0, TEXT("Hello,API"), TEXT("Hello"), MB_OK);

	// 1. 윈도우 클래스 만들기 
	WNDCLASS wc;
	windowClassSetting(wc, hInst, TEXT("First"));

	// 2. 등록(레지스트리에)
	RegisterClass(&wc);

	// 3. 윈도우 창 만들기 
	HWND hwnd = CreateWindowEx(0,					// WS_EX_TOPMOST
		TEXT("first"),				// 클래스 명 이 키는 레지스트리에 등록된 키값을 검색한다.
		TEXT("window"),				// 캡션바 내용 ==title bar name
		WS_OVERLAPPEDWINDOW, //window style 이건 비트 연산을 이용한다. 쓰기 싫은 것은 &~을 이용해서 빼자
		500, 250, 500, 500,	// x좌표,y좌표,x크기,y크기
		0, 0,			// 부모 윈도우 핸들, 메뉴 핸들
		hInst,		// WinMain의 1번째 파라미터 (exe 주소) 이거 무시해도 되긴함
		0);			// 생성 인자를 넘김, 현재 이것은 최상위 윈도이기 때문에 0 값을 넘김, 


	// 4. 윈도우 보여주기
	ShowWindow(hwnd, SW_SHOW); 	//이렇게 보여진 윈도우 창은 Application Que에 핸들값이 저장되게 된다.
	UpdateWindow(hwnd);

	// 8. Message  무한 루프 메세지를 받는 대기 상태를 만드는 법
	/*
	큐에 있는 메세지를 처리하는 방법
	*/
	MSG msg;

	//while (GetMessage(&msg, 0, 0, 0))//메세지 큐에서 메세지를 가져오는 함수 메인창이 죽을 때 실행된다. 메세지 큐에 Out Message를 만나면 false를 반환한다.
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);// 가져온 메세지를 프로시저로 보내는 함수
	//}

	//9.메세지 큐에 아무 것도 없을 때도 작동하는 방법
	while (true)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) //peekmessage함수는 메세지 큐에서 메세지를 꺼내고 검사 함수,  없다면 true 있다면 flase 반환, 제일 마지막 PM_REMOVE는 추출한 값을 큐에 남기지 않고 삭제 하겠다는 의미 PM_NOREMOVE는 제거하지 않는다
		{
			if (msg.message == WM_QUIT)   break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//HDC hdc = GetDC(hwnd);
			//SetPixel(hdc, rand() % 500, rand() % 500, RGB(rand() % 256, rand() % 256, rand() % 256)); // 피셀 값을 바꾸는 함수
			//ReleaseDC(hwnd, hdc);
		}
	}

	return 0;
}