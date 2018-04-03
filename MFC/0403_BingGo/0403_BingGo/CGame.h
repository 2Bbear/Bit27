#pragma once
struct BLOCK
{
	int number;
	bool bcheck;
};
class CMy0403BingGoDlg;

class CGame
{
public:
	BLOCK m_gameboard[5][5];
	bool m_bStart;

	CMy0403BingGoDlg * m_pDlg;

public:
	CGame(CMy0403BingGoDlg* p);
	~CGame();

public:
	void GetUserGameBoard(BLOCK ** pUser);
	//BLOCK 함수 초기화 함수
	void InitGame();
	//사격형을 그려준다
	void DrawRec(CDC * pDC);
	//선을 그리는 함수
	void DrawLine(CDC* pDC);
	//블럭을 그리는 함수
	void DrawBlock(CDC* pDC);
	
public:
	int BlockClick(CMy0403BingGoDlg * p,CPoint pt);

	void ClickNumber(int num);
private:
	//숫자를 그리는 함수
	void DrawNum(CDC * pDC, int iRow, int iCol, int iNum);
	//커서가 보드판을 선택했는지 판단하는 함수
	bool PointCheck(CPoint pt);

	void PosToIndex(CPoint pnt, int &iRow, int &iCol);

	void OrderNum(CDC * pdc ,int iRow, int iCol);

	void CheckNum(int iRow, int iCol);
	bool IsGameEnd();
};

