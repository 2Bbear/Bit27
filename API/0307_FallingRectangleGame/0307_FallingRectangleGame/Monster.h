#pragma once
class Monster
{
public:
	POINT currentPoint;

public:
	Monster();
	~Monster();
public:
	void setCurrentPoint(int x, int y);
public:
	void moveCharacter(int x, int y);
};

