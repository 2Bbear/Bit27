#include"std.h"


/////////================

/*
�� �ȵǴ°ɱ�ƾƾƾƾƾƾƾƾƾƾƾ�
�ȵȴپƾƾƾƾƾƾƾ�
���̾�α�â���� �ǽð����� �׷����� ���� ������ �𸣰ھ�

*/
/////////////=============

//------------------------------------
HWND g_hDlg; // Dialog �� �ڵ�.
#define WM_APPLY	WM_USER + 100
#define WM_CANCLEMUNU WM_USER+101
//------------------------------------


//��ȭ ���� ���ν���.
BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	static LINEDATA *pData;
	switch (msg)
	{
		//
		// Dialog�� ó�� ��Ÿ���� �߻�. �� ��Ʈ���� �ʱ�ȭ �Ѵ�.
		case WM_INITDIALOG:
		{
			pData = (LINEDATA*)lParam;
			//edit �ʱ�ȭ
			SetDlgItemInt(hDlg, IDC_EDIT1, pData->w_count, 0);
			SetDlgItemInt(hDlg, IDC_EDIT2, pData->h_count, 0);
			//�����̴� �ʱ�ȭ
			//1>���� ���� 
			SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_SETRANGE, FALSE, MAKELPARAM(1, 5));
			//2>�ʱⰪ �Է�
			SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_SETPOS, TRUE, pData->opa_pen);

			//OK��ư �ʱ�ȭ
			HWND h = GetDlgItem(hDlg, IDOK);
			SetWindowText(h, TEXT("����"));
			
			return TRUE;

		}
		break;
		//��ũ�� �����̸� �߻��ϴ� �޼���
		case WM_HSCROLL:
		{
			int n = 0;

			pData->opa_pen = SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_GETPOS, TRUE, (LPARAM)&n);
			return 0;
		}
		//�޼����� �޴� �κ�
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDOK:
			{
				pData->w_count = GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
				pData->h_count = GetDlgItemInt(hDlg, IDC_EDIT2, 0, 0);

				SendMessage(GetParent(g_hDlg), WM_APPLY, 0, 0);
				return TRUE;
			}
				

			case IDCANCEL:
			{
				SendMessage(GetParent(g_hDlg), WM_CANCLEMUNU, 0, 0);
				EndDialog(hDlg, IDCANCEL);
				return TRUE;
			}
				
			}
		}
		return FALSE; // �޼��� ó���� ���Ѱ��..
	}
	return FALSE; // �޼��� ó���� ���Ѱ��..
}

//������ ���ν���
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static LINEDATA data = { 5,5,1 };

	switch (msg)
	{
		//�ʱ�ȭ �޼���
		case WM_CREATE:
		{

			return 0;
		}
		//ȭ�� �׸��� �޼���
		case WM_PAINT:
		{

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			RECT rc;
			GetClientRect(hwnd, &rc);

			//=======================================================
			//����
			//���� ����
			double w_Vvalue = rc.right / (data.w_count + 1);
			//���� ����
			double w_Hvalue = rc.bottom / (double)(data.h_count + 1);
			//========================================================
			//�׸���
			//hdc setting
			HPEN pen = CreatePen(PS_SOLID, 1, RGB(data.opa_pen * 50, data.opa_pen * 50, data.opa_pen * 50));
			HPEN oldPen = (HPEN)SelectObject(hdc, pen);
			//����
			for (double i = 0; i<rc.right; i += w_Vvalue)
			{
				MoveToEx(hdc, i, 0, 0);
				LineTo(hdc, i, rc.bottom);
			}
			//����
			for (double i = 0; i<rc.bottom; i += w_Hvalue)
			{
				MoveToEx(hdc, 0, i, 0);
				LineTo(hdc, rc.right, i);
			}

			//===================
			DeleteObject(SelectObject(hdc, oldPen));

			EndPaint(hwnd, &ps);
			return 0;
		}

		//dialog�� ������ Custom Message================================================
			//OK��ư�� ������ ��
		case WM_APPLY:
		{
			
			//g_hDlg = 0;

			return 0;
		}
			//Cancle ��ư�� ������ ��
		case WM_CANCLEMUNU:
		{
			//g_hDlg = 0;
			return 0;
		}
		//======================================================================
		//���� Ŭ��
		case WM_LBUTTONDOWN:
		{
			if (g_hDlg == 0)
			{
				// ��޸��� �����.
				g_hDlg = CreateDialogParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG1), hwnd, DlgProc, (LPARAM)&data);
				//������� ��޸��� â�� ����ϴ� �Լ�
				ShowWindow(g_hDlg, SW_SHOW);
			}
			else
				SetFocus(g_hDlg);//�̹� ������� ��� focus�̵�

			return 0;
		}
		//������ Ŭ��
		case WM_RBUTTONDOWN:
		{

			return 0;
		}


		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine,int nShowCmd)
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
