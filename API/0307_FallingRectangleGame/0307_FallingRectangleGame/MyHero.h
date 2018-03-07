#pragma once

class MyHero
{
private:
	TCHAR name[20];
	POINT currentPoint ;

	//Constructor
public :
	MyHero();
	~MyHero();

	//Getter Setter
public:
	const TCHAR * getName()const;
	void setName(TCHAR * _name);
	const POINT getCurrentPoint()const;
	void setCurrentPoint(POINT * pPoint);
	
	//Custom Function
	//move Function
	void moveCharacter(int x,int y);
	
};