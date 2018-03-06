//draw.cpp

#include"std.h"
int changePattern = 0;
void draw_RectanglePrint(HDC hdc, POINT pt1)
{
	// GDI ��ü�� �̿��ϴ� �⺻���� ���
	//Pen ����
	HPEN pen; //����
	//Brush ����
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
	//hdc �ɼ� ����
	HPEN old = (HPEN)SelectObject(hdc, pen);// ��ü ���� �� ��ȯ

	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, backColor);

	Rectangle(hdc,pt1.x-25,pt1.y-25,pt1.x+25,pt1.y+25);
	DeleteObject(SelectObject(hdc, old));//gDI ��ü ����
	DeleteObject(SelectObject(hdc, oldbrush));//gDI ��ü ����
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
	wsprintf(str, TEXT("���尳�� : %d��"),size);
	SetWindowText(hwnd,str);
}