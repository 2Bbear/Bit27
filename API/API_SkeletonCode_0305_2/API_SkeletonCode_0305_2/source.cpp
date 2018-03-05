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
�ٸ� Ű �̺�Ʈ�� �ϰ� �ʹٸ� WinUser.h�� ã�Ƽ� �̺�Ʈ�� �߰�����
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)//.5 Message Proccessing
{
	
	switch (msg)
	{
	//��ť �޼��� ó��
	case WM_CREATE: //CreateWindowEx �Լ��� ���� ���� ������ ��ü�� ���� �� �� �ڵ����� msg�� ������ �� ���� ���⼭ �ʱ�ȭ ������ ���ָ� �ȴ�.
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

	//ť �޼��� ó��
		//Mouse ���콺 ó��
	case WM_MBUTTONDOWN:
		return 0;
	case WM_LBUTTONDOWN:
		MessageBox(0, TEXT("This is L button"), TEXT("L"), MB_YESNOCANCEL | MB_ICONQUESTION);
		return 0;
	case WM_RBUTTONDOWN:
		return 0;
	
	
		//keyboard Ű���� ó��
	case WM_KEYDOWN:
		switch (wParam)
		{
			//11. Function ���Ű
		/*case VK_MENU: // �̰� ������ �̻��ѵ�?
			MessageBox(0, TEXT("alt key"), TEXT("First"), MB_YESNOCANCEL);*/
		//	return 0;
		case VK_CONTROL://///////////////////////////////////////////////////////////6.���� ���� �ϴ� �ڵ�
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
			SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)backColor); // ������ Ŭ���� ���� ���� (LONG)GetStockObject(++brush)
			InvalidateRect(hwnd, NULL, TRUE);
			brush++;
			if (brush > 5){ brush = 0; }
			
			//MessageBox(0, TEXT("ctrl key"), TEXT("ctrl"), MB_YESNOCANCEL);
			return 0;
		case VK_SPACE:
			MessageBox(0, TEXT("SpaeceŰ"), TEXT("Spaece"), MB_YESNOCANCEL);
			return 0;
		case VK_ESCAPE:
			MessageBox(0, TEXT("ESCŰ"), TEXT("ESC"), MB_YESNOCANCEL);
			return 0;
		case VK_TAB:
			MessageBox(0, TEXT("TABŰ"), TEXT("TAB"), MB_YESNOCANCEL);
			return 0;
		case VK_BACK:
			MessageBox(0, TEXT("BackSpaceŰ"), TEXT("BackSpace"), MB_YESNOCANCEL);
			return 0;
			//cursor key ����Ű 
		case VK_DOWN:
			MessageBox(0, TEXT("�Ʒ� ����Ű"), TEXT("�Ʒ�"), MB_YESNOCANCEL);
			return 0;
		case VK_UP:
			MessageBox(0, TEXT("�� ����Ű"), TEXT("��"), MB_YESNOCANCEL);
			return 0;
		case VK_RIGHT://///////////////////////////////////////////////////////////////7.������ â �����̴� ���
			RECT rcCalc;
			GetWindowRect(hwnd, &rcCalc);
			MoveWindow(hwnd, x++, 10, 500, 500, TRUE); //������ �����̱�
			//MessageBox(0, TEXT("������ ����Ű"), TEXT("������"), MB_YESNOCANCEL);
			return 0;
		case VK_LEFT:
			MessageBox(0, TEXT("���� ����Ű"), TEXT("����"), MB_YESNOCANCEL);
			return 0;
		}
		//10. char key ����Ű ó��
		/*
		TranslateMessage(&msg); �� main �ش� proccessing �κп� �ۼ��ؾ��� ���ڰ��� �Է� ���� �� ���� ����ü �̰� �� �ϴ� �Լ����� ...
		*/
	case WM_CHAR: 
	{
			MessageBox(0, TEXT("���ڰ� ������"), TEXT("����"), MB_YESNOCANCEL);
			return 0;
	}
		
		
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
	MessageBox(0, TEXT("Hello,API"), TEXT("Hello"), MB_OK);

	// 1. ������ Ŭ���� ����� 
	WNDCLASS wc;
	windowClassSetting(wc, hInst, TEXT("First"));

	// 2. ���(������Ʈ����)
	RegisterClass(&wc);

	// 3. ������ â ����� 
	HWND hwnd = CreateWindowEx(0,					// WS_EX_TOPMOST
		TEXT("first"),				// Ŭ���� �� �� Ű�� ������Ʈ���� ��ϵ� Ű���� �˻��Ѵ�.
		TEXT("window"),				// ĸ�ǹ� ���� ==title bar name
		WS_OVERLAPPEDWINDOW , //window style �̰� ��Ʈ ������ �̿��Ѵ�. ���� ���� ���� &~�� �̿��ؼ� ����
		500, 250, 500, 500,	// x��ǥ,y��ǥ,xũ��,yũ��
		0, 0,			// �θ� ������ �ڵ�, �޴� �ڵ�
		hInst,		// WinMain�� 1��° �Ķ���� (exe �ּ�) �̰� �����ص� �Ǳ���
		0);			// ���� ���ڸ� �ѱ�, ���� �̰��� �ֻ��� �����̱� ������ 0 ���� �ѱ�, 


	// 4. ������ �����ֱ�
	ShowWindow(hwnd, SW_SHOW); 	//�̷��� ������ ������ â�� Application Que�� �ڵ鰪�� ����ǰ� �ȴ�.
	UpdateWindow(hwnd);

	// 8. Message  ���� ���� �޼����� �޴� ��� ���¸� ����� ��
	/*
	ť�� �ִ� �޼����� ó���ϴ� ���
	*/
	MSG msg;

	//while (GetMessage(&msg, 0, 0, 0))//�޼��� ť���� �޼����� �������� �Լ� ����â�� ���� �� ����ȴ�. �޼��� ť�� Out Message�� ������ false�� ��ȯ�Ѵ�.
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);// ������ �޼����� ���ν����� ������ �Լ�
	//}

	//9.�޼��� ť�� �ƹ� �͵� ���� ���� �۵��ϴ� ���
	while (true)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) //peekmessage�Լ��� �޼��� ť���� �޼����� ������ �˻� �Լ�,  ���ٸ� true �ִٸ� flase ��ȯ, ���� ������ PM_REMOVE�� ������ ���� ť�� ������ �ʰ� ���� �ϰڴٴ� �ǹ� PM_NOREMOVE�� �������� �ʴ´�
		{
			if (msg.message == WM_QUIT)   break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			HDC hdc = GetDC(hwnd);
			SetPixel(hdc, rand() % 500, rand() % 500, RGB(rand() % 256, rand() % 256, rand() % 256)); // �Ǽ� ���� �ٲٴ� �Լ�
			ReleaseDC(hwnd, hdc);
		}
	}

	return 0;
}