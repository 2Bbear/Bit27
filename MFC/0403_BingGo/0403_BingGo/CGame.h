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
	//BLOCK �Լ� �ʱ�ȭ �Լ�
	void InitGame();
	//������� �׷��ش�
	void DrawRec(CDC * pDC);
	//���� �׸��� �Լ�
	void DrawLine(CDC* pDC);
	//���� �׸��� �Լ�
	void DrawBlock(CDC* pDC);
	
public:
	int BlockClick(CMy0403BingGoDlg * p,CPoint pt);

	void ClickNumber(int num);
private:
	//���ڸ� �׸��� �Լ�
	void DrawNum(CDC * pDC, int iRow, int iCol, int iNum);
	//Ŀ���� �������� �����ߴ��� �Ǵ��ϴ� �Լ�
	bool PointCheck(CPoint pt);

	void PosToIndex(CPoint pnt, int &iRow, int &iCol);

	void OrderNum(CDC * pdc ,int iRow, int iCol);

	void CheckNum(int iRow, int iCol);
	bool IsGameEnd();
};

