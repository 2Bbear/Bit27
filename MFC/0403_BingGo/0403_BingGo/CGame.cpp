#include "stdafx.h"
#include "CGame.h"

#include "0403_BingGoDlg.h"
CGame::CGame(CMy0403BingGoDlg* p)
{
	InitGame();
	m_bStart = true;
	//m_bStart = false;
	m_pDlg = p;
}


CGame::~CGame()
{
	
}


void  CGame::GetUserGameBoard(BLOCK ** pUser)
{
	for (int i =0;i<5;i++)
	{
		for (int j =0;j<5;j++)
		{
			pUser[i][j] = m_gameboard[i][j];
		}
	}
	
}

void CGame::InitGame()
{
	int n = 1;
	for (int i=0;i<5;i++)
	{

		for (int j = 0; j<5; j++)
		{
			m_gameboard[i][j].number=n;
			m_gameboard[i][j].bcheck = FALSE;
			n++;
			
		}

	}

}


void CGame::DrawRec(CDC * pDC)
{
	
	CBrush br;

	br.CreateSolidBrush(RGB(62, 62, 124));

	CBrush *lbr = pDC->SelectObject(&br);

	pDC->Rectangle(10, 10, 10 + 250, 10 + 250);

	pDC->SelectObject(lbr);
}


void CGame::DrawLine(CDC* pDC)
{
	CPen pen;

	pen.CreatePen(PS_SOLID, 2, RGB(128, 128, 128));

	CPen *lodp = pDC->SelectObject(&pen);

	for (int i = 0; i<6; i++) //���μ� �׸���
	{
		pDC->MoveTo(10, 10 + i * 50);
		pDC->LineTo(50 * 5 + 10, 10 + i * 50);
	}

	for (int i = 0; i<6; i++) //���μ� �׸���
	{
		pDC->MoveTo(10 + i * 50, 10);
		pDC->LineTo(10 + i * 50, 50 * 5 + 10);
	}

	pDC->SelectObject(pen);
}


void CGame::DrawBlock(CDC* pDC)
{
	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			DrawNum(pDC,i,j, m_gameboard[i][j].number);
			
		}
	}
}

void CGame::DrawNum(CDC * pDC,int iRow, int iCol, int iNum)
{
	// ���ڸ� �׷��ش�.

	CString str;
	str.Format(TEXT("%d"), iNum);



	// ���� �ִ� ����(0)�� �����
	CBrush br;
	CPen pen;
	CPen *lodp;
	CBrush *lbr;

	if (m_gameboard[iRow][iCol].bcheck==FALSE)
	{
		pen.CreatePen(PS_SOLID, 1, RGB(62, 62, 124));
		lodp = pDC->SelectObject(&pen);

		br.CreateSolidBrush(RGB(62, 62, 124));
		lbr = pDC->SelectObject(&br);
		pDC->Rectangle(12 + iCol * 50, 12 + iRow * 50, 12 + iCol * 50 + 45, 12 + iRow * 50 + 45);

		// ���ϴ� ���ڸ� �׷��ش�.
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
	}
	else
	{
		pen.CreatePen(PS_SOLID, 1, RGB(124, 0, 0));
		lodp = pDC->SelectObject(&pen);

		br.CreateSolidBrush(RGB(124, 0, 0));
		lbr = pDC->SelectObject(&br);
		pDC->Rectangle(11 + iCol * 50, 11 + iRow * 50, 11 + iCol * 50 + 48, 11 + iRow * 50 + 48);

		// ���ϴ� ���ڸ� �׷��ش�.
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
	}
	

	if (str.GetLength() > 1) // ���ڰ� ���ڸ��϶� ó��
		pDC->TextOut(27 + iCol * 50, 30 + iRow * 50, str);
	else
		pDC->TextOut(30 + iCol * 50, 30 + iRow * 50, str);


	pDC->SelectObject(lbr);
	pDC->SelectObject(lodp);
}

bool CGame::PointCheck(CPoint pt)
{
	if (pt.x > 260 || pt.y > 260) // ���Ӱ� ���� ���°� Ŭ����
		return false;
	if (pt.x <10 || pt.y <10)
		return false;
	
	return true;
}

void CGame::PosToIndex(CPoint pnt, int & iRow, int & iCol)
{
	int i, j;
	for (i = 0; i<5; i++) //�� ����(Row)
	{
		if ((pnt.y > 10 + i * 50) &&
			pnt.y <= (10 + (i + 1) * 50)
			)
			break;
	}

	for (j = 0; j<5; j++) //�� ����(Col)
	{
		if ((pnt.x > 10 + j * 50) &&
			pnt.x <= (10 + (j + 1) * 50)
			)
			break;
	}

	iRow = i;
	iCol = j;
}

void CGame::OrderNum(CDC * pdc, int iRow, int iCol)
{
	
	static int oder = 1;
	// ���콺�� Ŭ���ϴ� ������� ��ȣ�� �ű��.
	if (!m_gameboard[iRow][iCol].number)
	{
		m_gameboard[iRow][iCol].number = oder++;
		DrawNum(pdc,iRow, iCol, m_gameboard[iRow][iCol].number);
	}
	if (oder>25)
	{
		m_bStart = TRUE;
		//������ ������ ���� �ʱ�ȭ
		oder = 1;
	}

}

void CGame::CheckNum(int iRow, int iCol)
{
	if (m_gameboard[iRow][iCol].bcheck==false)
	{
		m_gameboard[iRow][iCol].bcheck = true;
		
	}
}

bool CGame::IsGameEnd()
{
	int iLine = 0;
	int i, j;
	for (i = 0; i<5; i++) // ���� �˻�
	{
		for (j = 0; j<5; j++)
		{
			if (!m_gameboard[i][j].bcheck)
				break;
		}
		if (j == 5)
			iLine++;
	}


	for (i = 0; i<5; i++) // ���� �˻�
	{
		for (j = 0; j<5; j++)
		{
			if (!m_gameboard[j][i].bcheck)
				break;
		}
		if (j == 5)
			iLine++;
	}

	for (i = 0; i<5; i++) // �밢�� �˻�(�� ����)
	{
		if (!m_gameboard[i][i].bcheck)
			break;
	}
	if (i == 5)
		iLine++;

	for (i = 0, j = 4; i<5; i++, j--) // �밢�� �˻�(�� ����)
	{
		if (!m_gameboard[i][j].bcheck)
			break;
	}
	if (i == 5) // 5�� �̻��̸� ����
		iLine++;

	if (iLine >= 5)
		return TRUE;
	else
		return FALSE;
}


int CGame::BlockClick(CMy0403BingGoDlg * p,CPoint pt)
{
	//�߸��� ��ǥ�� ��ġ ���͸�
	if (PointCheck(pt)==FALSE)
	{
		return -1;
	}
	//pt��ǥ�� �� �ε����� ����
	int iRow = -1, iCol = -1;
	PosToIndex(pt, iRow, iCol);
	//���� ����
	if (m_bStart == true)
	{
		CheckNum(iRow, iCol);
		p->Invalidate(false);
		if (IsGameEnd()==true)
		{
			AfxMessageBox(TEXT("���ӳ� ������"));
		}
		return m_gameboard[iRow][iCol].number;
	}
	//���� ��ȣ�� Ŭ���� ������� ����
	else
	{
		CClientDC dc(p);
		OrderNum(&dc, iRow, iCol);
		return -1;
	}
	
}

void CGame::ClickNumber(int num)
{
	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			if (m_gameboard[i][j].number == num)
			{
				m_gameboard[i][j].bcheck = true;
				m_pDlg->Invalidate(false);
				return;
			}
		}
	}
}

