#pragma once

#include"CGame.h"
class CMy0403BingGoDlg;
#define MOVE_X 400



class CComGame
{
public:
	BLOCK m_gameboard[5][5];
	bool m_bStart;
	CMy0403BingGoDlg * m_pDlg;
public:
	int m_winRateBoard[5][5];

	int m_UserWinRateBoard[5][5];
	CGame* puser;
	int bestChoice[2];
private:
	int checkedNum[25];
	int checkedNumIndex;
public:
	CComGame(CMy0403BingGoDlg * p, CGame * pUser);
	~CComGame();

public:
	//������ ���� �� ���� �ϴ� �Լ�
	void ForecastUserBoard(int selectednum);
	//Ȯ�� ���� �ʱ�ȭ
	void InitWinRateBoard();
	
	//BLOCK �Լ� �ʱ�ȭ �Լ�
	void InitGame();
	//������� �׷��ش�
	void DrawRec(CDC * pDC);
	//���� �׸��� �Լ�
	void DrawLine(CDC* pDC);
	//���� �׸��� �Լ�
	void DrawBlock(CDC* pDC);
	// ��ȣ���� �����ϰ� �����ϴ� �Լ�
	void InitNumber();
	
	void ClickNumber(int num);
	/*
	����, ���θ��� ���� �Ǵ��Ѵ�
	������ ���� true������ �����ϰ� �ش� block�� ���� ��ȯ�Ѵ�.
	*/
	int AI_SelectNumber();
	/*
	��� ������ Ȯ������ �����ϰ� ���� ���� Ȯ���� ��ġ�� ���� �д�.
	������ ���� true������ �����ϰ� �ش� block�� ���� ��ȯ�Ѵ�.
	*/
	int AI_SelectNumber2(int selectednum);
public:
	int BlockClick(int num);
private:
	//���ڸ� �׸��� �Լ�
	void DrawNum(CDC * pDC, int iRow, int iCol, int iNum);
	//Ŀ���� �������� �����ߴ��� �Ǵ��ϴ� �Լ�
	bool PointCheck(CPoint pt);

	void PosToIndex(CPoint pnt, int &iRow, int &iCol);

	void OrderNum(CDC * pdc, int iRow, int iCol);

	void CheckNum(int iRow, int iCol);
	bool IsGameEnd();
};

