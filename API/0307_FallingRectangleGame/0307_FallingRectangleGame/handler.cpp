#include"std.h"
#define MOVERATE 10



LRESULT OnCreate(HWND hwnd, MyHero * _hero)
{
	//ĳ���� ����
	_hero = new MyHero();
	//ĳ���� �ʱ�ȭ
	_hero->setName(TEXT("�ο�ٵ���"));
	POINT current = {50,50};
	_hero->setCurrentPoint(&current);
	//ĳ���͸� ȭ�鿡 �ʱ� ���
	SendMessage(hwnd,WM_PAINT,0,0);

	return 0;
}
LRESULT OnKeyDown(HWND hwnd, WPARAM wParam,MyHero * _hero)
{
	switch (wParam)
	{
	//Arrow Keys
	case VK_UP:
	{
				 _hero->moveCharacter( 0, -MOVERATE);
				  return 0;
	}
	case VK_DOWN:
	{
					_hero->moveCharacter(0, MOVERATE);
					return 0;
	}
	case VK_LEFT:
	{
					_hero->moveCharacter(-MOVERATE, 0);
					return 0;
	}
	case VK_RIGHT:
	{
					 _hero->moveCharacter(MOVERATE, 0);
					 return 0;
	}
	}
	return 0;
}

LRESULT OnPaint(HWND hwnd,MyHero *_hero)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	//======================================
	//UI �׸���

	//ĳ���� �׸���
	draw_Charcter(hwnd, hdc, _hero);

	//======================================
	EndPaint(hwnd, &ps);
	return 0;
}