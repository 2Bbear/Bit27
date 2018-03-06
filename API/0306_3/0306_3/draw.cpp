//draw.cpp

#include"std.h"
int changePattern = 0;
void draw_RectanglePrint(HDC hdc, POINT pt1)
{
	// GDI 객체를 이용하는 기본적인 방법
	//Pen 관련
	HPEN pen; //생성
	//Brush 관련
	HBRUSH backColor;
	switch (changePattern)
	{
	case 0:{
			   backColor = CreateSolidBrush(RGB(255, 0, 0));
			   pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			   break;
	}
	case 1:{
			   backColor = CreateSolidBrush(RGB(255, 94, 0));
			   pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			   break;
	}
	case 2:{
			   backColor = CreateSolidBrush(RGB(255, 228, 0));
			   pen = CreatePen(PS_SOLID, 1, RGB(255, 94, 0));
			   break;
	}
	case 3:{
			   backColor = CreateSolidBrush(RGB(29, 219, 22));
			   pen = CreatePen(PS_SOLID, 1, RGB(255, 228, 0));
			   break;
	}
	case 4:{
			   backColor = CreateSolidBrush(RGB(0, 0, 255));
			   pen = CreatePen(PS_SOLID, 1, RGB(29, 219, 22));
			   break;
	}
	case 5:{
			   backColor = CreateSolidBrush(RGB(95, 0, 255));
			   pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			   break;
	}

	}
	//hdc 옵션 셋팅
	HPEN old = (HPEN)SelectObject(hdc, pen);// 객체 선택 후 교환

	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, backColor);

	Rectangle(hdc,pt1.x-25,pt1.y-25,pt1.x+25,pt1.y+25);
	DeleteObject(SelectObject(hdc, old));//gDI 객체 삭제
	DeleteObject(SelectObject(hdc, oldbrush));//gDI 객체 삭제
	changePattern++;
	if (changePattern > 5){ changePattern = 0; }
}

void draw_Print(HDC hdc, vector<POINT> * datalist)
{
	for (int i = 0;i<(int)datalist->size();i++)
	{
		POINT pt = (*datalist)[i];
		draw_RectanglePrint(hdc,pt);

	}
}

void draw_TiltePrint(HWND hwnd, int size)
{
	TCHAR str[20];
	wsprintf(str, TEXT("저장개수 : %d개"),size);
	SetWindowText(hwnd,str);
}