#include<Windows.h>
#include<tchar.h>
#include <math.h>
#define NUM    1000
#define TWOPI  (2 * 3.14159)//���ΰ�

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
		WS_OVERLAPPEDWINDOW, //window style �̰� ��Ʈ ������ �̿��Ѵ�. ���� ���� ���� &~�� �̿��ؼ� ����
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
			//HDC hdc = GetDC(hwnd);
			//SetPixel(hdc, rand() % 500, rand() % 500, RGB(rand() % 256, rand() % 256, rand() % 256)); // �Ǽ� ���� �ٲٴ� �Լ�
			//ReleaseDC(hwnd, hdc);
		}
	}

	return 0;
}