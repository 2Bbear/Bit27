#include<windows.h>
#include<tchar.h>

/*
@ hwnd : handle key value for handling of your window object
@ msg : Message that passed on Translate Que
@ wParam
@ lParam
This Function is Processing of MSG.
if you take some default key event. you must fined this WinUser.h
다른 키 이벤트를 하고 싶다면 WinUser.h를 찾아서 이벤트를 추가하자
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//비큐 메세지 처리
	case WM_CREATE: //CreateWindowEx 함수를 통해 메인 윈도우 객체가 생성 될 때 자동으로 msg에 들어오는 값 따라서 여기서 초기화 값들을 해주면 된다.
		MessageBox(0, TEXT("create widow"), TEXT("create"), MB_YESNOCANCEL | MB_ICONQUESTION);
		return 0;
		//case WM_SIZE:	//will Active that chage window Application size
		//	MessageBox(0, TEXT("resize?"), TEXT("resize"), MB_YESNOCANCEL | MB_ICONQUESTION);
		//	return 0;
		//case WM_MOVE:	//will Active that moved windw Application with mouse console
		//	MessageBox(0, TEXT("move move"), TEXT("move"), MB_YESNOCANCEL | MB_ICONQUESTION);
		//	return 0;
		//case WM_ACTIVATE: // will Active that change window Application
		//	MessageBox(0, TEXT("active"), TEXT("Active"), MB_YESNOCANCEL | MB_ICONQUESTION);
		//	return 0;

		//큐 메세지 처리
		//Mouse 마우스 처리
	case WM_MBUTTONDOWN:
		return 0;
	case WM_LBUTTONDOWN:
		MessageBox(0, TEXT("This is L button"), TEXT("First"), MB_YESNOCANCEL | MB_ICONQUESTION);
		return 0;
	case WM_RBUTTONDOWN:
		return 0;


		//eyboard 키보드 처리
	case WM_KEYDOWN:
		switch (wParam)
		{
			//Function 기능키
			/*case VK_MENU: // 이거 반응이 이상한데?
			MessageBox(0, TEXT("alt key"), TEXT("First"), MB_YESNOCANCEL);*/
			return 0;
		case VK_CONTROL:
			MessageBox(0, TEXT("ctrl key"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_SPACE:
			MessageBox(0, TEXT("Spaece키"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_ESCAPE:
			MessageBox(0, TEXT("ESC키"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_TAB:
			MessageBox(0, TEXT("TAB키"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_BACK:
			MessageBox(0, TEXT("BackSpace키"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
			//cursor key 방향키 
		case VK_DOWN:
			MessageBox(0, TEXT("아래 방향키"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_UP:
			MessageBox(0, TEXT("위 방향키"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_RIGHT:
			MessageBox(0, TEXT("오른쪽 방향키"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_LEFT:
			MessageBox(0, TEXT("왼쪽 방향키"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
			//char key 문자키

		}

		return 0;
		//종료 처리
	case WM_DESTROY: //메인 윈도우가 죽을 때 들어오는 MSG다 반드시 이건 이렇게 처리르 해줘야 메모리 상에 프로그램이 더 이상 남아 있지 않게 된다.
		PostQuitMessage(0);//큐에 WM_QUIT를 넣는 함수
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);//모르는 msg값들을 디폴트윈도우 프로시저로 처리 할 수 있도록 호출하고 각 매개변수들을 다 전달해준다.
}


/*
@ _wc : your class object
@ _hInst : handle that your widow handle.
@ _str :your class registry Key value.
This Function is setting of your windowClass
*/
void windowClassSetting(WNDCLASS & _wc, HINSTANCE _hInst, LPTSTR  str)
{
	_wc.cbWndExtra = 0;
	_wc.cbClsExtra = 0;
	_wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH); // 배경색 , 미리 제공되는 객체들이 있는데 거기서 화이트 브러쉬를 가져옴
	_wc.hCursor = LoadCursor(0, IDC_ARROW);//커서 , 0 부분에 hinst를 넣으면 내가 만든 것을 넣겠다는 의미
	_wc.hIcon = LoadIcon(0, IDI_APPLICATION);//아이콘
	_wc.hInstance = _hInst;
	_wc.lpfnWndProc = WndProc;			// DefWindowProc; 자신이 직접 만든 메세지 처리 함수를 등록해야함. 

	_wc.lpszClassName = str;//TEXT("First");//검색을 위한 키값
	_wc.lpszMenuName = 0;
	_wc.style = 0;
}
void windowClassSetting2(WNDCLASS & _wc, HINSTANCE _hInst, LPTSTR  str)
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
	MessageBox(0, TEXT("Hello,API"), TEXT("First"), MB_YESNOCANCEL | MB_ICONQUESTION);

	// 1. 윈도우 클래스 만들기 
	WNDCLASS wc,wc2;
	windowClassSetting(wc, hInst, TEXT("First"));
	windowClassSetting2(wc2, hInst, TEXT("Second"));
	// 2. 등록(레지스트리에)
	RegisterClass(&wc);
	RegisterClass(&wc2);

	// 3. 윈도우 창 만들기 
	HWND hwnd = CreateWindowEx(0,					// WS_EX_TOPMOST
		TEXT("first"),				// 클래스 명 이 키는 레지스트리에 등록된 키값을 검색한다.
		TEXT("Hello"),				// 캡션바 내용 ==title bar name
		WS_OVERLAPPEDWINDOW, //window style 이건 비트 연산을 이용한다. 쓰기 싫은 것은 &~을 이용해서 빼자
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	// 초기 위치 
		0, 0,			// 부모 윈도우 핸들, 메뉴 핸들
		hInst,		// WinMain의 1번째 파라미터 (exe 주소)
		0);			// 생성 인자

	HWND hwnd2 = CreateWindowEx(0,					// WS_EX_TOPMOST
		TEXT("Second"),				// 클래스 명 이 키는 레지스트리에 등록된 키값을 검색한다.
		TEXT("Hello222"),				// 캡션바 내용 ==title bar name
		WS_OVERLAPPEDWINDOW, //window style 이건 비트 연산을 이용한다. 쓰기 싫은 것은 &~을 이용해서 빼자
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 100,	// 초기 위치 
		0, 0,			// 부모 윈도우 핸들, 메뉴 핸들
		hInst,		// WinMain의 1번째 파라미터 (exe 주소)
		0);			// 생성 인자

	// 4. 윈도우 보여주기
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	ShowWindow(hwnd2, SW_SHOW);
	UpdateWindow(hwnd);

	// 5. Message  
	/*
	큐에 있는 메세지를 처리하는 방법
	*/
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))//메세지 큐에서 메세지를 가져오는 함수 메인창이 죽을 때 실행된다.
	{
		//TranslateMessage(&msg);
		DispatchMessage(&msg);// 가져온 메세지를 프로시저로 보내는 함수
	}


	return 0;
}