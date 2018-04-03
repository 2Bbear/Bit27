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
	//유저의 다음 수 예측 하는 함수
	void ForecastUserBoard(int selectednum);
	//확률 보드 초기화
	void InitWinRateBoard();
	
	//BLOCK 함수 초기화 함수
	void InitGame();
	//사격형을 그려준다
	void DrawRec(CDC * pDC);
	//선을 그리는 함수
	void DrawLine(CDC* pDC);
	//블럭을 그리는 함수
	void DrawBlock(CDC* pDC);
	// 번호들을 랜덤하게 지정하는 함수
	void InitNumber();
	
	void ClickNumber(int num);
	/*
	세로, 가로만을 보고 판단한다
	선택한 블럭을 true값으로 변경하고 해당 block의 값을 반환한다.
	*/
	int AI_SelectNumber();
	/*
	모든 구역에 확률값을 대입하고 가장 높은 확율의 위치에 수를 둔다.
	선택한 블럭을 true값으로 변경하고 해당 block의 값을 반환한다.
	*/
	int AI_SelectNumber2(int selectednum);
public:
	int BlockClick(int num);
private:
	//숫자를 그리는 함수
	void DrawNum(CDC * pDC, int iRow, int iCol, int iNum);
	//커서가 보드판을 선택했는지 판단하는 함수
	bool PointCheck(CPoint pt);

	void PosToIndex(CPoint pnt, int &iRow, int &iCol);

	void OrderNum(CDC * pdc, int iRow, int iCol);

	void CheckNum(int iRow, int iCol);
	bool IsGameEnd();
};

