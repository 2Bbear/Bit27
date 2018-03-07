//handler.cpp

#include "std.h"


extern vector<SHAPE*> g_drawList;//좌표가 있는 값들을 저장할 리스트
extern SHAPE g_drawCurrent;// 현재 어떠한 것을 그릴 것인지를 담고 있는 정보

LRESULT OnCreate(HWND hwnd)
{
	draw_curDataInit(&g_drawCurrent);
	draw_TiltePrint(hwnd, g_drawList.size());
	return 0;
}

LRESULT OnDestroy()
{
	PostQuitMessage(0);
	return 0;
}

LRESULT OnLButtonDown(HWND hwnd, LPARAM lParam)
{
//	POINTS pt = MAKEPOINTS(lParam);
	//현 좌표 정보 얻기
	int x  = LOWORD(lParam);
	int y = HIWORD(lParam);
	g_drawCurrent.pt = { LOWORD(lParam), HIWORD(lParam) };

	//저장
	SHAPE *p = (SHAPE*)malloc(sizeof(SHAPE));
	*p = g_drawCurrent;

	g_drawList.push_back(p);
	//RECT rc = { x - 25, y - 25, x + 25, y + 25 };
	//InvalidateRect(hwnd, &rc, FALSE);
	InvalidateRect(hwnd, 0, FALSE);

	draw_TiltePrint(hwnd, g_drawList.size());

	return 0;
}

LRESULT OnRButtonDown(HWND hwnd)
{
	if (g_drawList.size() <= 0)
		return 0;

	g_drawList.pop_back();
	InvalidateRect(hwnd, 0, TRUE);
	draw_TiltePrint(hwnd, g_drawList.size());

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
	printf("가상키 :%d\n",wParam); //진짜 0키가 무슨 값을 가져 오는지 알아보기 위해서 사용함
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
	printf("가상키 :%d\n", wParam); //진짜 0키가 무슨 값을 가져 오는지 알아보기 위해서 사용함
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