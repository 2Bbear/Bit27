//handler.cpp

#include "std.h"

#define TIMER_ID_TITLENAME 1
#define TIMER_ID_TITLEICON 2

extern vector<SHAPE*> g_drawList;//��ǥ�� �ִ� ������ ������ ����Ʈ
extern SHAPE g_drawCurrent;// ���� ��� ���� �׸� �������� ��� �ִ� ����

LRESULT OnInitMenuPoUp(HWND hwnd, WPARAM wParam)
{
	HMENU hmenu = (HMENU) wParam;
	EnableMenuItem(hmenu, ID_40007,g_drawCurrent.color== RGB(255, 0, 0)?MF_GRAYED : MF_ENABLED);
	EnableMenuItem(hmenu, ID_40008, g_drawCurrent.color == RGB(0, 255, 0) ? MF_GRAYED : MF_ENABLED);
	EnableMenuItem(hmenu, ID_40009, g_drawCurrent.color == RGB(0, 0, 255) ? MF_GRAYED : MF_ENABLED);
	return LRESULT();
}


LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	
	switch (LOWORD(wParam))
	{
		//File menu
	case ID_40001:
	{
		
		draw_NewDocument(hwnd,&g_drawList);
		break;
	}
	case ID_40005:
	{
		SendMessage(hwnd, WM_CLOSE, 0, 0);
		break;
	}
		//Brush color
	case ID_40007:
	{
		g_drawCurrent.color = RGB(255, 0, 0);
		break;
	}
	case ID_40008:
	{
		g_drawCurrent.color = RGB(0, 255, 0);
		break;
	}
	case ID_40009:
	{
		g_drawCurrent.color = RGB(0, 0, 255);
		break;
	}
	}
	return 0;
}

LRESULT OnConTextMenu(HWND hwnd, LPARAM lParam)
{
	HMENU hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
	HMENU hSubMenu = GetSubMenu(hMenu, 1);
	POINT  pt = { LOWORD(lParam), HIWORD(lParam) };
	// ��ũ�� ��ǥ...
	TrackPopupMenu(hSubMenu, TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, 0);

	return 0;
}

LRESULT OnCreate(HWND hwnd)
{
	//Timer Init
		//for print title current Time
	SetTimer(hwnd, TIMER_ID_TITLENAME, 1000, NULL);//(Ÿ�̸� �޼����� ���� ������,Ÿ�̸��� ��ȣ ����,�ֱⰪ,ȣ��� �Լ�) ���� ������ WM_TIMER �޼����� ���� wParam�� Timer ID�� ���� �־ ����
	SendMessage(hwnd, WM_TIMER, 1, NULL);//������ WM_TIMER�� �����Ű�� �Լ�

		//for print title ICON Animation
	SetTimer(hwnd, TIMER_ID_TITLEICON,500,NULL);

	//GUI obj Init
	draw_curDataInit(&g_drawCurrent);

	return 0;
}

LRESULT OnDestroy(HWND hwnd)
{
	KillTimer(hwnd, TIMER_ID_TITLENAME);
	KillTimer(hwnd, TIMER_ID_TITLEICON);
	PostQuitMessage(0);
	return 0;
}

LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//	�����ڵ�
	if (wParam&MK_CONTROL)
	{
		if (g_drawList.size() <= 0)
			return 0;

		g_drawList.pop_back();

	}
	//==========================================================================
	else
	{
		//�� ��ǥ ���� ���
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		g_drawCurrent.pt = { LOWORD(lParam), HIWORD(lParam) };
		//����
		SHAPE *p = (SHAPE*)malloc(sizeof(SHAPE));
		*p = g_drawCurrent;

		g_drawList.push_back(p);
		//RECT rc = { x - 25, y - 25, x + 25, y + 25 };
		//InvalidateRect(hwnd, &rc, FALSE);
	}
	
	//===================================================================================
	InvalidateRect(hwnd, 0, FALSE);

	draw_TiltePrint(hwnd, g_drawList.size());

	return 0;
}

LRESULT OnRButtonDown(HWND hwnd)
{
	return 0;
}

LRESULT OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	//======================================
	draw_CurPrint(hdc, g_drawCurrent, g_drawList.size());

	draw_Print(hdc, &g_drawList);
	//======================================
	EndPaint(hwnd, &ps);
	return 0;
}
LRESULT OnKeyDown(HWND hwnd, WPARAM wParam)
{
	printf("����Ű :%d\n",wParam); //��¥ 0Ű�� ���� ���� ���� ������ �˾ƺ��� ���ؼ� �����
	switch (wParam)
	{
	case VK_NUMPAD0:{
						g_drawCurrent.type = 0;
						break;

	}
	case '0':{
			   g_drawCurrent.type = 0;
			   break;
	}
	case VK_NUMPAD1:{
						g_drawCurrent.type = 1;
						break;
	}
	case '1':{
			   g_drawCurrent.type = 1;
			   break;
	}
	}
	InvalidateRect(hwnd,0,TRUE);
	return 0;
}
LRESULT OnChar(HWND hwnd, WPARAM wParam)
{
	printf("����Ű :%d\n", wParam); //��¥ 0Ű�� ���� ���� ���� ������ �˾ƺ��� ���ؼ� �����
	switch (wParam)
	{
	case 'r':
	{
				g_drawCurrent.color = RGB(255,0,0);
				break;
	}
	case 'g':
	{
				g_drawCurrent.color = RGB(0,255, 0);
				break;
	}
	case 'b':
	{
				g_drawCurrent.color = RGB(0, 0, 255);
				break;
	}
	case 'n':
	{
				g_drawCurrent.color = RGB(0, 0, 0);
				break;
	}
	}

	return 0;
}

LRESULT OnTimer(HWND hwnd, WPARAM wParam,LPARAM lParam)
{
	//���� �ð� ���� ����ǥ���ٿ� �����
	if (wParam == 1)
	{
		draw_TiltePrint(hwnd, g_drawList.size());
	}
	//���� ������ �ִϸ��̼�
	else if (wParam==2)
	{
		draw_ChangeIcon(hwnd);
	}
	return 0;
}