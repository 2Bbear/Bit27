#include"std.h"



Monster::Monster()
{
}


Monster::~Monster()
{
}

void Monster::setCurrentPoint(int x, int y)
{
	currentPoint.x = x;
	currentPoint.y = y;
}

void Monster::moveCharacter(int x, int y)
{
	currentPoint.x += x;
	currentPoint.y += y;
}
