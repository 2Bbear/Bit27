//draw.cpp

#include "std.h"

void draw_curDataInit(SHAPE * curData)
{
	curData->pt.x = 10;
	curData->pt.y = 10;
	curData->type = 0; //RECT
	curData->color = RGB(0,0,255);
}
//야 이거 안되
void draw_NewDocument(HWND hwnd, vector<SHAPE*>* datalist)
{
	datalist->clear();
	InvalidateRect(hwnd, 0, TRUE);
}
void draw_Print(HDC hdc, vector<SHAPE*> *datalist)
{
	for (int i = 0; i < (int)datalist->size(); i++)
	{
		SHAPE *sh = (*datalist)[i];
		draw_ShapePrint(hdc,sh);
	}
}
void draw_ShapePrint(HDC hdc, SHAPE *sh)
{
	//dc Setting
	HBRUSH brush = (HBRUSH)CreateSolidBrush(sh->color);

	HBRUSH old = (HBRUSH)SelectObject(hdc,brush);

	//형태 분배
	if (sh->type == 0)
		draw_RectanglewPrint(hdc, sh);
	else if (sh->type == 1)
		draw_EllipsePrint(hdc, sh);

	//dc Delete
	DeleteObject(SelectObject(hdc,old));
}
void draw_RectanglewPrint(HDC hdc, SHAPE * sh)
{
	POINT pt = sh->pt;
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldpen = (HPEN)SelectObject(hdc, pen);
	Rectangle(hdc, pt.x - 25, pt.y - 25, pt.x + 25, pt.y + 25);
	DeleteObject(SelectObject(hdc, oldpen));
}
void draw_EllipsePrint(HDC hdc, SHAPE * sh)
{
	POINT pt = sh->pt;
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldpen = (HPEN)SelectObject(hdc, pen);
	Ellipse(hdc, pt.x - 25, pt.y - 25, pt.x + 25, pt.y + 25);
	DeleteObject(SelectObject(hdc, oldpen));
}
void draw_TiltePrint(HWND hwnd, int size)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	TCHAR buf[20];
	wsprintf(buf, TEXT("현재 시간 : %d:%d:%d"),st.wHour, st.wMinute, st.wSecond);
	SetWindowText(hwnd, buf);
}

//제목 아이콘 출력 함수
void draw_ChangeIcon(HWND hwnd)
{
	//한번만 리소스를 불러오니까 스태틱으로 해놓음
	static HICON iconlist[4] = { LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON2)),
		LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON3)),
	LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON4)),
	LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON5))
	};
	static int idx = 0;
	++idx;
	if (idx == 4)
	{
		idx = 0;
	}
	SetClassLong(hwnd, GCL_HICON, (LONG)iconlist[idx]);
	
	
	
	
}
void draw_CurPrint(HDC hdc, SHAPE g_drawCurrent, int size)
{
	TCHAR buf[30];
	wsprintf(buf,TEXT("저장개수 : %d"),size);
	TextOut(hdc, 5, 5, buf, _tcslen(buf));

	wsprintf(buf, TEXT("좌 표 : %d : %d"), g_drawCurrent.pt.x, g_drawCurrent.pt.y );
	TextOut(hdc, 5, 25, buf, _tcslen(buf));

	wsprintf(buf, TEXT("도형타입 : %s"),g_drawCurrent.type==0?TEXT("사각형"):TEXT("타원"));
	TextOut(hdc, 5, 45, buf, _tcslen(buf));

	wsprintf(buf, TEXT("색    상 : R%d  ,G%d   B%d"), GetRValue(g_drawCurrent.color), GetGValue(g_drawCurrent.color), GetBValue(g_drawCurrent.color));
	TextOut(hdc, 5, 65, buf, _tcslen(buf));
	
}