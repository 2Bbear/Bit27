//handler.cpp

#include"std.h"

extern vector<POINT> g_drawList;// 참조 선언

LRESULT OnDestroy()
{
	PostQuitMessage(0);
	return 0;
}

LRESULT OnLButtonDown(HWND hwnd, LPARAM lParam)
{
	
	//=========================================
	//POINTS pt = MAKEPOINTS(lParam);
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	POINT pt1 = { LOWORD(lParam), HIWORD(lParam) };

	g_drawList.push_back(pt1);// 만들어진 사각형의 위치 값을 저장
	
	RECT rc = { x - 25, y - 25, x + 25, y + 25 };
	InvalidateRect(hwnd, &rc, FALSE);
	
	draw_TiltePrint(hwnd, g_drawList.size());
	//=========================================
	return 0;
}

LRESULT OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);// 이 함수를 이용해야지 무효화 영역이 삭제되서 더이상 WM_PAINT 메세지가 안날라오게 된다
	//===========================================
	draw_Print(hdc, &g_drawList);//계속해서 모든 사각형을 그림, 무효화 영역을 없애기 위해 채워져도 형태를 남기기 위해
	//===========================================
	EndPaint(hwnd, &ps);
	return 0;
}
LRESULT  OnRButtonDown(HWND hwnd)
{
	//벡터가 남아 있는지 확인
	if (g_drawList.size()<=0)
	{
		return 0;
	}
	//벡터의 맨 뒤의 값을 삭제
	g_drawList.pop_back();
	//윈도우 다시 그리기
	InvalidateRect(hwnd, 0, TRUE);//화면을 다시 그리는 함수
	//제목처리
	draw_TiltePrint(hwnd, g_drawList.size());
	return 0;
}
LRESULT OnCreate(HWND hwnd)
{
	//제목 초기화
	draw_TiltePrint(hwnd, g_drawList.size());
	return 0;
}