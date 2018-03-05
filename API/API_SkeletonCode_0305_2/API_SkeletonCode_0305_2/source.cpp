#include<windows.h>
#include<tchar.h>
int x=0; //move for window
int brush = 0; //for change BackGround

/*
@ hwnd : handle value for handling of your window object
@ msg : Message that passed on Translate Que
@ wParam
@ lParam
This Function is Processing of MSG.
if you take some default key event. you must fined this WinUser.h
다른 키 이벤트를 하고 싶다면 WinUser.h를 찾아서 이벤트를 추가하자
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)//.5 Message Proccessing
{
	
	switch (msg)
	{
	//비큐 메세지 처리
	case WM_CREATE: //CreateWindowEx 함수를 통해 메인 윈도우 객체가 생성 될 때 자동으로 msg에 들어오는 값 따라서 여기서 초기화 값들을 해주면 된다.
		MessageBox(0, TEXT("create widow"), TEXT("create"), MB_OK);
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
		MessageBox(0, TEXT("This is L button"), TEXT("L"), MB_YESNOCANCEL | MB_ICONQUESTION);
		return 0;
	case WM_RBUTTONDOWN:
		return 0;
	
	
		//keyboard 키보드 처리
	case WM_KEYDOWN:
		switch (wParam)
		{
			//11. Function 기능키
		/*case VK_MENU: // 이거 반응이 이상한데?
			MessageBox(0, TEXT("alt key"), TEXT("First"), MB_YESNOCANCEL);*/
		//	return 0;
		case VK_CONTROL://///////////////////////////////////////////////////////////6.배경색 변경 하는 코드
			HBRUSH backColor;
			switch (brush)
			{
			case 0:{
					   backColor = CreateSolidBrush(RGB(255, 0, 0));
					  break;
			}
			case 1:{
					   backColor = CreateSolidBrush(RGB(255, 94, 0));
					   break;
			}
			case 2:{
					   backColor = CreateSolidBrush(RGB(255, 228, 0));
					   break;
			}
			case 3:{
					   backColor = CreateSolidBrush(RGB(29, 219, 22));
					   break;
			}
			case 4:{
					   backColor = CreateSolidBrush(RGB(0, 0, 255));
					   break;
			}
			case 5:{
					   backColor = CreateSolidBrush(RGB(95, 0, 255));
					   break;
			}

			}
			SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)backColor); // 윈도우 클래스 값을 변경 (LONG)GetStockObject(++brush)
			InvalidateRect(hwnd, NULL, TRUE);
			brush++;
			if (brush > 5){ brush = 0; }
			
			//MessageBox(0, TEXT("ctrl key"), TEXT("ctrl"), MB_YESNOCANCEL);
			return 0;
		case VK_SPACE:
			MessageBox(0, TEXT("Spaece키"), TEXT("Spaece"), MB_YESNOCANCEL);
			return 0;
		case VK_ESCAPE:
			MessageBox(0, TEXT("ESC키"), TEXT("ESC"), MB_YESNOCANCEL);
			return 0;
		case VK_TAB:
			MessageBox(0, TEXT("TAB키"), TEXT("TAB"), MB_YESNOCANCEL);
			return 0;
		case VK_BACK:
			MessageBox(0, TEXT("BackSpace키"), TEXT("BackSpace"), MB_YESNOCANCEL);
			return 0;
			//cursor key 방향키 
		case VK_DOWN:
			MessageBox(0, TEXT("아래 방향키"), TEXT("아래"), MB_YESNOCANCEL);
			return 0;
		case VK_UP:
			MessageBox(0, TEXT("위 방향키"), TEXT("위"), MB_YESNOCANCEL);
			return 0;
		case VK_RIGHT://///////////////////////////////////////////////////////////////7.윈도우 창 움직이는 기능
			RECT rcCalc;
			GetWindowRect(hwnd, &rcCalc);
			MoveWindow(hwnd, x++, 10, 500, 500, TRUE); //윈도우 움직이기
			//MessageBox(0, TEXT("오른쪽 방향키"), TEXT("오른쪽"), MB_YESNOCANCEL);
			return 0;
		case VK_LEFT:
			MessageBox(0, TEXT("왼쪽 방향키"), TEXT("왼쪽"), MB_YESNOCANCEL);
			return 0;
		}
		//10. char key 문자키 처리
		/*
		TranslateMessage(&msg); 를 main 밑단 proccessing 부분에 작성해야지 문자값을 입력 받을 수 있음 도대체 이게 뭘 하는 함수인지 ...
		*/
	case WM_CHAR: 
	{
			MessageBox(0, TEXT("문자가 쳐졌어"), TEXT("문자"), MB_YESNOCANCEL);
			return 0;
	}
		
		
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
		WS_OVERLAPPEDWINDOW , //window style 이건 비트 연산을 이용한다. 쓰기 싫은 것은 &~을 이용해서 빼자
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
			HDC hdc = GetDC(hwnd);
			SetPixel(hdc, rand() % 500, rand() % 500, RGB(rand() % 256, rand() % 256, rand() % 256)); // 피셀 값을 바꾸는 함수
			ReleaseDC(hwnd, hdc);
		}
	}

	return 0;
}