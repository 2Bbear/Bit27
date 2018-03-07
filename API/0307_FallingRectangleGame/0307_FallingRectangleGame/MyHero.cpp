#include"std.h"
#include"MyHero.h"
using namespace std;

MyHero::MyHero()
{

}
MyHero::~MyHero()
{

}

const TCHAR  * MyHero::getName() const
{
	return name;
}
void MyHero::setName(TCHAR * _name)
{
	_tcscpy(name, _name);
	//strcpy_s(name,strlen(name),_name);
}
const POINT MyHero::getCurrentPoint()const
{
	return currentPoint;
}
void MyHero:: setCurrentPoint(POINT * pPoint)
{
	currentPoint = *pPoint;
}

void MyHero:: moveCharacter(int x, int y)
{
	currentPoint.x += x;
	currentPoint.y += y;
}