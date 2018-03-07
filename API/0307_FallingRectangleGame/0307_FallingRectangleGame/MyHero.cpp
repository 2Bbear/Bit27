#include"std.h"

MyHero::MyHero()
{
}

MyHero::~MyHero()
{
}

void MyHero::setCurrentPoint(int x,int y)
{
	currentPoint.x = x;
	currentPoint.y = y;
}

void MyHero::moveCharacter(int x, int y)
{
	currentPoint.x += x;
	currentPoint.y += y;
}
