#include<windows.h>
#include<tchar.h>

/*
@ hwnd : handle key value for handling of your window object
@ msg : Message that passed on Translate Que
@ wParam
@ lParam
This Function is Processing of MSG.
if you take some default key event. you must fined this WinUser.h
�ٸ� Ű �̺�Ʈ�� �ϰ� �ʹٸ� WinUser.h�� ã�Ƽ� �̺�Ʈ�� �߰�����
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//��ť �޼��� ó��
	case WM_CREATE: //CreateWindowEx �Լ��� ���� ���� ������ ��ü�� ���� �� �� �ڵ����� msg�� ������ �� ���� ���⼭ �ʱ�ȭ ������ ���ָ� �ȴ�.
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

		//ť �޼��� ó��
		//Mouse ���콺 ó��
	case WM_MBUTTONDOWN:
		return 0;
	case WM_LBUTTONDOWN:
		MessageBox(0, TEXT("This is L button"), TEXT("First"), MB_YESNOCANCEL | MB_ICONQUESTION);
		return 0;
	case WM_RBUTTONDOWN:
		return 0;


		//eyboard Ű���� ó��
	case WM_KEYDOWN:
		switch (wParam)
		{
			//Function ���Ű
			/*case VK_MENU: // �̰� ������ �̻��ѵ�?
			MessageBox(0, TEXT("alt key"), TEXT("First"), MB_YESNOCANCEL);*/
			return 0;
		case VK_CONTROL:
			MessageBox(0, TEXT("ctrl key"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_SPACE:
			MessageBox(0, TEXT("SpaeceŰ"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_ESCAPE:
			MessageBox(0, TEXT("ESCŰ"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_TAB:
			MessageBox(0, TEXT("TABŰ"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_BACK:
			MessageBox(0, TEXT("BackSpaceŰ"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
			//cursor key ����Ű 
		case VK_DOWN:
			MessageBox(0, TEXT("�Ʒ� ����Ű"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_UP:
			MessageBox(0, TEXT("�� ����Ű"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_RIGHT:
			MessageBox(0, TEXT("������ ����Ű"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
		case VK_LEFT:
			MessageBox(0, TEXT("���� ����Ű"), TEXT("First"), MB_YESNOCANCEL);
			return 0;
			//char key ����Ű

		}

		return 0;
		//���� ó��
	case WM_DESTROY: //���� �����찡 ���� �� ������ MSG�� �ݵ�� �̰� �̷��� ó���� ����� �޸� �� ���α׷��� �� �̻� ���� ���� �ʰ� �ȴ�.
		PostQuitMessage(0);//ť�� WM_QUIT�� �ִ� �Լ�
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);//�𸣴� msg������ ����Ʈ������ ���ν����� ó�� �� �� �ֵ��� ȣ���ϰ� �� �Ű��������� �� �������ش�.
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
	_wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH); // ���� , �̸� �����Ǵ� ��ü���� �ִµ� �ű⼭ ȭ��Ʈ �귯���� ������
	_wc.hCursor = LoadCursor(0, IDC_ARROW);//Ŀ�� , 0 �κп� hinst�� ������ ���� ���� ���� �ְڴٴ� �ǹ�
	_wc.hIcon = LoadIcon(0, IDI_APPLICATION);//������
	_wc.hInstance = _hInst;
	_wc.lpfnWndProc = WndProc;			// DefWindowProc; �ڽ��� ���� ���� �޼��� ó�� �Լ��� ����ؾ���. 

	_wc.lpszClassName = str;//TEXT("First");//�˻��� ���� Ű��
	_wc.lpszMenuName = 0;
	_wc.style = 0;
}
void windowClassSetting2(WNDCLASS & _wc, HINSTANCE _hInst, LPTSTR  str)
{
	_wc.cbWndExtra = 0; //������ ������ ������ �� �ִ� ���� �����̴�. ������� ���� ��� 0���� �����Ѵ�
	_wc.cbClsExtra = 0; //Ŭ���� ������ ������ �� �ִ� ���� �����̴�. ������� ���� ���� 0���� �����Ѵ�.
	_wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH); // ���� , �̸� �����Ǵ� ��ü���� �ִµ� �ű⼭ ȭ��Ʈ �귯���� ������
	_wc.hCursor = LoadCursor(0, IDC_ARROW);//Ŀ�� , 0 �κп� hinst�� ������ ���� ���� ���� �ְڴٴ� �ǹ�
	_wc.hIcon = LoadIcon(0, IDI_APPLICATION);//������
	_wc.hInstance = _hInst; //������ ���ν����� ���� ����� �ڵ��̸� WinMain�� ù��° ���ڷ� ���޵� ���� �����Ѵ�.
	_wc.lpfnWndProc = WndProc;			// DefWindowProc; �ڽ��� ���� ���� �޼��� ó�� �Լ��� ����ؾ���. 

	_wc.lpszClassName = str;//TEXT("First");//�˻��� ���� Ű��
	_wc.lpszMenuName = 0; //�����쿡 ������ �޴��� �����Ѵ�. �޴��� �Ϲ������� ���ҽ� �����Ϳ� ���� ������ ���������. ������� ���� ���� �η� �����Ѵ�.
	_wc.style = 0;
}


int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR IpCmdLine, int nShowCmd)
{
	MessageBox(0, TEXT("Hello,API"), TEXT("First"), MB_YESNOCANCEL | MB_ICONQUESTION);

	// 1. ������ Ŭ���� ����� 
	WNDCLASS wc,wc2;
	windowClassSetting(wc, hInst, TEXT("First"));
	windowClassSetting2(wc2, hInst, TEXT("Second"));
	// 2. ���(������Ʈ����)
	RegisterClass(&wc);
	RegisterClass(&wc2);

	// 3. ������ â ����� 
	HWND hwnd = CreateWindowEx(0,					// WS_EX_TOPMOST
		TEXT("first"),				// Ŭ���� �� �� Ű�� ������Ʈ���� ��ϵ� Ű���� �˻��Ѵ�.
		TEXT("Hello"),				// ĸ�ǹ� ���� ==title bar name
		WS_OVERLAPPEDWINDOW, //window style �̰� ��Ʈ ������ �̿��Ѵ�. ���� ���� ���� &~�� �̿��ؼ� ����
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,	// �ʱ� ��ġ 
		0, 0,			// �θ� ������ �ڵ�, �޴� �ڵ�
		hInst,		// WinMain�� 1��° �Ķ���� (exe �ּ�)
		0);			// ���� ����

	HWND hwnd2 = CreateWindowEx(0,					// WS_EX_TOPMOST
		TEXT("Second"),				// Ŭ���� �� �� Ű�� ������Ʈ���� ��ϵ� Ű���� �˻��Ѵ�.
		TEXT("Hello222"),				// ĸ�ǹ� ���� ==title bar name
		WS_OVERLAPPEDWINDOW, //window style �̰� ��Ʈ ������ �̿��Ѵ�. ���� ���� ���� &~�� �̿��ؼ� ����
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 100,	// �ʱ� ��ġ 
		0, 0,			// �θ� ������ �ڵ�, �޴� �ڵ�
		hInst,		// WinMain�� 1��° �Ķ���� (exe �ּ�)
		0);			// ���� ����

	// 4. ������ �����ֱ�
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	ShowWindow(hwnd2, SW_SHOW);
	UpdateWindow(hwnd);

	// 5. Message  
	/*
	ť�� �ִ� �޼����� ó���ϴ� ���
	*/
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))//�޼��� ť���� �޼����� �������� �Լ� ����â�� ���� �� ����ȴ�.
	{
		//TranslateMessage(&msg);
		DispatchMessage(&msg);// ������ �޼����� ���ν����� ������ �Լ�
	}


	return 0;
}