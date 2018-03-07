#pragma once
class MyHero
{
public:

	POINT currentPoint;
	int type;
	COLORREF color;
	int hp=100;
	int score=0;
public:
	MyHero();
	~MyHero();
public:
	void setCurrentPoint(int x, int y);
public:
	void moveCharacter(int x, int y);
};
