#include"std.h"

//extern MyHero  hero;

void draw_Charcter(HWND hwnd, HDC hdc, MyHero * _hero)
{
	Rectangle(hdc, 0, 0, 50, 50);
	MessageBox(hwnd, TEXT("sss"), TEXT("â"), MB_OK);
	//Rectangle(hdc, _hero->getCurrentPoint().x - 25, _hero->getCurrentPoint().y - 25, _hero->getCurrentPoint().x + 25, _hero->getCurrentPoint().y+25);
    
}
