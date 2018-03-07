#include"std.h"
#define MOVERATE 10



LRESULT OnCreate(HWND hwnd, MyHero * _hero)
{
	//캐릭터 생성
	_hero = new MyHero();
	//캐릭터 초기화
	_hero->setName(TEXT("로우바둑이"));
	POINT current = {50,50};
	_hero->setCurrentPoint(&current);
	//캐릭터를 화면에 초기 출력
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
	//UI 그리기

	//캐릭터 그리기
	draw_Charcter(hwnd, hdc, _hero);

	//======================================
	EndPaint(hwnd, &ps);
	return 0;
}