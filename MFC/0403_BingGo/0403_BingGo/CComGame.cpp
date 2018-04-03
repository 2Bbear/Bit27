#include "stdafx.h"
#include "CComGame.h"
#include "CGame.h"
#include "0403_BingGoDlg.h"

CComGame::CComGame(CMy0403BingGoDlg* p, CGame*pUser)
{
	InitGame();
	
	m_bStart = false;
	m_pDlg = p;
	//=================
	checkedNumIndex = 0;
	InitWinRateBoard();
	puser = pUser;
}


CComGame::~CComGame()
{
}

void CComGame::ForecastUserBoard(int selectednum)
{
	bestChoice[0] = 0;
	bestChoice[1] = 0;
	ForecastUserBoard(selectednum);
	//������ ���� ������ �� ���ϱ�
	int x = -1, y = -1;
	//���õ� cellã�Ƴ���
	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			if (puser->m_gameboard[i][j].number == selectednum)
			{
				x = i;
				y = j;
				break;
			}
		}
		if (x != -1)
		{
			break;
		}
	}
	//���õ� �κ� winrate -1 �ʱ�ȭ
	m_UserWinRateBoard[x][y] = -1;


	//���õ� cell ���� winrate ���ϱ�
	//���� ����
	for (int i = y + 1; i<5; i++)
	{
		if (puser->m_gameboard[x][i].bcheck) { continue; }
		m_UserWinRateBoard[x][i] += 1;
	}

	//���� ����
	for (int i = y - 1; i>-1; i--)
	{
		if (puser->m_gameboard[x][i].bcheck) { continue; }
		m_UserWinRateBoard[x][i] += 1;
	}
	//���� ����
	for (int i = x + 1; i<5; i++)
	{
		if (puser->m_gameboard[i][y].bcheck) { continue; }
		m_UserWinRateBoard[i][y] += 1;
	}

	//���� ����
	for (int i = x - 1; i>-1; i--)
	{
		if (puser->m_gameboard[i][y].bcheck) { continue; }
		m_UserWinRateBoard[i][y] += 1;
	}

	//�밢 �� cell winrate ���ϱ�
	int temp_x = x;
	int temp_y = y;
	//�밢���� �����ϴ��� �Ǵ��ϱ�
	// \ �밢��
	if (x == y)
	{
		temp_x += 1;
		temp_y += 1;

		/*TCHAR st2[20];
		wsprintf(st2, TEXT("\\ �밢��"));
		AfxMessageBox(st2);*/
		//�� �밢�� ����
		while (temp_x<5)
		{
			if (puser->m_gameboard[temp_x][temp_y].bcheck)
			{
				temp_x++;
				temp_y++;
				continue;
			}
			m_UserWinRateBoard[temp_x][temp_y] += 1;
			temp_x++;
			temp_y++;
		}

		//�ʱⰪ
		temp_x = x;
		temp_y = y;

		temp_x -= 1;
		temp_y -= 1;
		//�� �밢�� ����
		while (temp_x>-1)
		{
			if (puser->m_gameboard[temp_x][temp_y].bcheck)
			{
				temp_x--;
				temp_y--;
				continue;
			}
			m_UserWinRateBoard[temp_x][temp_y] += 1;
			temp_x--;
			temp_y--;
		}

	}
	int sumxy = x + y;
	// /�밢��
	if (sumxy == 4)
	{


		//�ʱⰪ
		temp_x = x;
		temp_y = y;

		temp_x += 1;
		temp_y -= 1;

		//�� �밢�� ����
		while (temp_x<5)
		{
			/*	TCHAR st2[20];
			wsprintf(st2, TEXT("tempx : %d tempy %d"), temp_x, temp_y);
			AfxMessageBox(st2);*/
			//Ʈ�簪�϶� �ε����� �������ؼ� ��� �ݺ���

			if (puser->m_gameboard[temp_x][temp_y].bcheck)
			{
				temp_x++;
				temp_y--;
				continue;
			}
			m_UserWinRateBoard[temp_x][temp_y] += 1;
			temp_x++;
			temp_y--;
		}



		//�ʱⰪ
		temp_x = x;
		temp_y = y;

		temp_x -= 1;
		temp_y += 1;

		//�� �밢�� ����
		while (temp_x>-1)
		{
			if (puser->m_gameboard[temp_x][temp_y].bcheck)
			{
				temp_x--;
				temp_y++;
				continue;
			}
			m_UserWinRateBoard[temp_x][temp_y] += 1;
			temp_x--;
			temp_y++;
		}
	}

	//=============================================
	//�м�
	int max = 0;
	int t_x = 0;
	int t_y = 0;

	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			if (m_UserWinRateBoard[i][j] >= max)
			{
				if (puser->m_gameboard[i][j].bcheck == true) { continue; }
				max = m_UserWinRateBoard[i][j];
				t_x = i;
				t_y = j;
			}
		}
	}
	bestChoice[0] = puser->m_gameboard[t_x][t_y].number;

	 max = 0;
	 t_x = 0;
	 t_y = 0;

	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			if (m_UserWinRateBoard[i][j] >= max)
			{
				if (puser->m_gameboard[i][j].bcheck == true) { continue; }
				if (puser->m_gameboard[i][j].number == bestChoice[0]) 
				{ continue; }
				max = m_UserWinRateBoard[i][j];
				t_x = i;
				t_y = j;
			}
		}
	}
	bestChoice[1] = puser->m_gameboard[t_x][t_y].number;

	//======================

	//======================
	
}

void CComGame::InitWinRateBoard()
{
	//��ü �ʱ�ȭ
	for (int i =0;i<5;i++)
	{
		for (int j=0;j<5;j++)
		{
			m_winRateBoard[i][j] = 0;
		}
	}
	//�߾Ӻ� setting
	m_winRateBoard[2][2] += 2;

	//�߾ӿܰ� setting
		//�¿�
	m_winRateBoard[2][1] += 0;
	m_winRateBoard[2][3] += 0;
		//��밢
	m_winRateBoard[1][1] += 0;
	m_winRateBoard[1][3] += 0;
		//����
	m_winRateBoard[1][2] += 0;
	m_winRateBoard[3][2] += 0;
		//�ϴ밢
	m_winRateBoard[3][1] += 0;
	m_winRateBoard[3][3] += 0;
	//=======================================
	//UserWinRateBoard Init Setting
	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			m_UserWinRateBoard[i][j] = 0;
		}
	}
	//�߾Ӻ� setting
	m_UserWinRateBoard[2][2] += 2;

	//�߾ӿܰ� setting
	//�¿�
	m_UserWinRateBoard[2][1] += 0;
	m_UserWinRateBoard[2][3] += 0;
	//��밢
	m_UserWinRateBoard[1][1] += 0;
	m_UserWinRateBoard[1][3] += 0;
	//����
	m_UserWinRateBoard[1][2] += 0;
	m_UserWinRateBoard[3][2] += 0;
	//�ϴ밢
	m_UserWinRateBoard[3][1] += 0;
	m_UserWinRateBoard[3][3] += 0;
}

void CComGame::InitGame()
{
	for (int i = 0; i<5; i++)
	{

		for (int j = 0; j<5; j++)
		{
			m_gameboard[i][j].number = 0;
			m_gameboard[i][j].bcheck = FALSE;

		}

	}

}


void CComGame::DrawRec(CDC * pDC)
{

	CBrush br;

	br.CreateSolidBrush(RGB(62, 62, 124));

	CBrush *lbr = pDC->SelectObject(&br);

	pDC->Rectangle(10+ MOVE_X, 10, 10+ MOVE_X + 250, 10 + 250);

	pDC->SelectObject(lbr);
}


void CComGame::DrawLine(CDC* pDC)
{
	CPen pen;

	pen.CreatePen(PS_SOLID, 2, RGB(128, 128, 128));

	CPen *lodp = pDC->SelectObject(&pen);

	for (int i = 0; i<6; i++) //���μ� �׸���
	{
		pDC->MoveTo(10+ MOVE_X, 10 + i * 50);
		pDC->LineTo(50 * 5 + 10+ MOVE_X, 10 + i * 50);
	}

	for (int i = 0; i<6; i++) //���μ� �׸���
	{
		pDC->MoveTo(10 + i * 50+ MOVE_X, 10);
		pDC->LineTo(10 + i * 50+ MOVE_X, 50 * 5 + 10);
	}

	pDC->SelectObject(pen);
}


void CComGame::DrawBlock(CDC* pDC)
{
	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			DrawNum(pDC, i, j, m_gameboard[i][j].number);

		}
	}
}

void CComGame::InitNumber()
{
	int count = 1;
	for (int i =0;i<5;i++)
	{
		for (int j=0;j<5;j++)
		{
			m_gameboard[i][j].number = count++;
		}
	}
	srand((unsigned int)time(0));
	for (int i=0;i<1000;i++)
	{
		int c1 = rand() % 5;
		int r1 = rand() % 5;
		int c2 = rand() % 5;
		int r2 = rand() % 5;
		int temp = m_gameboard[c1][r1].number;
		m_gameboard[c1][r1].number = m_gameboard[c2][r2].number;
		m_gameboard[c2][r2].number = temp;

	}

	m_pDlg->Invalidate();
	m_bStart = true;


}

void CComGame::ClickNumber(int num)
{
	for (int i =0;i<5;i++)
	{
		for (int j=0;j<5;j++)
		{
			if (m_gameboard[i][j].number==num)
			{
				m_gameboard[i][j].bcheck = true;
				m_pDlg->Invalidate(false);
				return;
			}
		}
	}
}

int CComGame::AI_SelectNumber()
{
	int result=0;
	//���� �˻�
		//���ο�
	int check_row[5] = { 0 };
	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			if (m_gameboard[i][j].bcheck)
			{
				check_row[i] += 1;
				if (check_row[i]>=5)
				{
					check_row[i] = 0;
				}
			}
		}
	}
		//���ο�
	int check_col[5] = {0};
	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			if (m_gameboard[i][j].bcheck)
			{
				check_col[j] += 1;
				if (check_col[j]>=5)
				{
					check_col[j] = 0;
				}
			}
		}
	}
	//���� �� 
	
	//���� �ְ� ��
	int Rmax = 0;
	int Rresult = 0;//���� ������ ��
	for (int i=0;i<5;i++)
	{
		if (check_row[i] > Rmax)
		{
			Rmax = check_row[i];
			Rresult = i;
			break;
		}
	}
	//���� �ְ� ��
	int Cmax = 0;
	int Cresult = 0;//���� ������ ��
	for (int i = 0; i<5; i++)
	{
		if (check_col[i] >= Cmax)
		{
			Cmax = check_col[i];
			Cresult = i;
			break;
		}
	}
	//���� ���� true ���� ���� ã�� ��
	if (Rmax>= Cmax)// ���μ����� ã���� ���,�Ǵ� �Ѵ� ���� ���
	{
		//ToDo
		for (int i=0;i<5;i++)
		{
			if (m_gameboard[Rresult][i].bcheck==false)
			{
				result = m_gameboard[Rresult][i].number;
				m_gameboard[Rresult][i].bcheck = true;
				return result;
			}
		}
	}
	if(Cmax)//���μ����� ã�������
	{
		//ToDo
		for (int i = 0; i<5; i++)
		{
			if (m_gameboard[i][Cresult].bcheck == false)
			{
				result = m_gameboard[i][Cresult].number;
				m_gameboard[i][Cresult].bcheck = true;
				return result;
			}
		}
	}

	//=================================================

	
	return result;
}

void CComGame::DrawNum(CDC * pDC, int iRow, int iCol, int iNum)
{
	// ���ڸ� �׷��ش�.

	CString str;
	str.Format(TEXT("%d"), iNum);



	// ���� �ִ� ����(0)�� �����
	CBrush br;
	CPen pen;
	CPen *lodp;
	CBrush *lbr;

	if (m_gameboard[iRow][iCol].bcheck == FALSE)
	{
		pen.CreatePen(PS_SOLID, 1, RGB(62, 62, 124));
		lodp = pDC->SelectObject(&pen);

		br.CreateSolidBrush(RGB(62, 62, 124));
		lbr = pDC->SelectObject(&br);
		pDC->Rectangle(12 + iCol * 50+ MOVE_X, 12 + iRow * 50, 12 + iCol * 50 + 45+ MOVE_X, 12 + iRow * 50 + 45);

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
		pDC->Rectangle(11 + iCol * 50+ MOVE_X, 11 + iRow * 50, 11 + iCol * 50 + 48+ MOVE_X, 11 + iRow * 50 + 48);

		// ���ϴ� ���ڸ� �׷��ش�.
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
	}


	if (str.GetLength() > 1) // ���ڰ� ���ڸ��϶� ó��
		pDC->TextOut(27 + iCol * 50+ MOVE_X, 30 + iRow * 50, str);
	else
		pDC->TextOut(30 + iCol * 50+ MOVE_X, 30 + iRow * 50, str);


	pDC->SelectObject(lbr);
	pDC->SelectObject(lodp);
}

bool CComGame::PointCheck(CPoint pt)
{
	if (pt.x > 260 || pt.y > 260) // ���Ӱ� ���� ���°� Ŭ����
		return false;
	if (pt.x <10 || pt.y <10)
		return false;

	return true;
}

void CComGame::PosToIndex(CPoint pnt, int & iRow, int & iCol)
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

void CComGame::OrderNum(CDC * pdc, int iRow, int iCol)
{

	static int oder = 1;
	// ���콺�� Ŭ���ϴ� ������� ��ȣ�� �ű��.
	if (!m_gameboard[iRow][iCol].number)
	{
		m_gameboard[iRow][iCol].number = oder++;
		DrawNum(pdc, iRow, iCol, m_gameboard[iRow][iCol].number);
	}
	if (oder>25)
	{
		m_bStart = TRUE;
		//������ ������ ���� �ʱ�ȭ
		oder = 1;
	}

}

void CComGame::CheckNum(int iRow, int iCol)
{
	if (m_gameboard[iRow][iCol].bcheck == false)
	{
		m_gameboard[iRow][iCol].bcheck = true;

	}
}

bool CComGame::IsGameEnd()
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


int CComGame::AI_SelectNumber2(int selectednum)
{
	
	int x=-1, y=-1;
	//���õ� cellã�Ƴ���
	for (int i = 0; i<5; i++)
	{
		for (int j = 0; j<5; j++)
		{
			if (m_gameboard[i][j].number == selectednum)
			{
				x = i;
				y = j;
				break;
			}
		}
		if (x != -1)
		{
			break;
		}
	}
	//���õ� �κ� winrate -1 �ʱ�ȭ
	m_winRateBoard[x][y] = -1;

	
	//���õ� cell ���� winrate ���ϱ�
		//���� ����
	for (int i= y+1;i<5;i++ )
	{
		if (m_gameboard[x][i].bcheck) { continue; }
		m_winRateBoard[x][i] += 1;
	}
	
		//���� ����
	for (int i=y-1;i>-1;i--)
	{
		if (m_gameboard[x][i].bcheck) { continue; }
		m_winRateBoard[x][i] += 1;
	}
		//���� ����
	for (int i= x+1;i<5;i++)
	{
		if (m_gameboard[i][y].bcheck) { continue; }
		m_winRateBoard[i][y] += 1;
	}

		//���� ����
	for (int i=x-1;i>-1;i--)
	{
		if (m_gameboard[i][y].bcheck) { continue; }
		m_winRateBoard[i][y] += 1;
	}
	
	//�밢 �� cell winrate ���ϱ�
	int temp_x = x;
	int temp_y = y;
		//�밢���� �����ϴ��� �Ǵ��ϱ�
		// \ �밢��
	if (x == y)
	{
		temp_x += 1;
		temp_y += 1;

		/*TCHAR st2[20];
		wsprintf(st2, TEXT("\\ �밢��"));
		AfxMessageBox(st2);*/
		//�� �밢�� ����
		while (temp_x<5)
		{
			if (m_gameboard[temp_x][temp_y].bcheck) 
			{ 
				temp_x++;
				temp_y++;
				continue; 
			}
			m_winRateBoard[temp_x][temp_y] += 1;
			temp_x++;
			temp_y++;
		}
		
		//�ʱⰪ
		temp_x = x;
		temp_y = y;

		temp_x -= 1;
		temp_y -= 1;
		//�� �밢�� ����
		while (temp_x>-1)
		{
			if (m_gameboard[temp_x][temp_y].bcheck) 
			{ 
				temp_x--;
				temp_y--;
				continue; 
			}
			m_winRateBoard[temp_x][temp_y] += 1;
			temp_x--;
			temp_y--;
		}
	
	}
	int sumxy = x + y;
		// /�밢��
	if (sumxy ==4)
	{
		

		//�ʱⰪ
		temp_x = x;
		temp_y = y;

		temp_x += 1;
		temp_y -= 1;
		
		//�� �밢�� ����
		while (temp_x<5)
		{
		/*	TCHAR st2[20];
			wsprintf(st2, TEXT("tempx : %d tempy %d"), temp_x, temp_y);
			AfxMessageBox(st2);*/
			//Ʈ�簪�϶� �ε����� �������ؼ� ��� �ݺ���

			if (m_gameboard[temp_x][temp_y].bcheck) 
			{ 
				temp_x++;
				temp_y--;
				continue; 
			}
			m_winRateBoard[temp_x][temp_y] += 1;
			temp_x++;
			temp_y--;
		}
		
	

		//�ʱⰪ
		temp_x = x;
		temp_y = y;

		temp_x -= 1;
		temp_y += 1;

		//�� �밢�� ����
		while (temp_x>-1)
		{
			if (m_gameboard[temp_x][temp_y].bcheck) 
			{ 
				temp_x--;
				temp_y++;
				continue; 
			}
			m_winRateBoard[temp_x][temp_y] += 1;
			temp_x--;
			temp_y++;
		}
	}
	
	//=============================================
	//�м�
	int max = 0;
	int t_x = 0;
	int t_y = 0;
	
	for (int i=0;i<5;i++)
	{
		for (int j=0 ;j<5;j++)
		{
			if (m_winRateBoard[i][j] >= max)
			{
				if (m_gameboard[i][j].bcheck == true) { continue; }
				if (m_gameboard[i][j].number == bestChoice[0]) 
				{
					if (m_winRateBoard[i][j]>2)
					{

					}
					else
					{
						continue;
					}
					
				}
				max = m_winRateBoard[i][j];
				t_x = i;
				t_y = j;
			}
		}
	}
	//�ְ� ������ cell ����
	m_gameboard[t_x][t_y].bcheck = true;
	
	//======================
	
	//======================
	return m_gameboard[t_x][t_y].number;
}

int CComGame::BlockClick(int n)
{

	//���� ����
	if (m_bStart == true)
	{
		int num= AI_SelectNumber2(n);
		IsGameEnd();
		if (IsGameEnd() == true)
		{
			AfxMessageBox(TEXT("Com Win"));
		}
		//��ȣ ����
		return num;
	}
	//���� ��ȣ�� Ŭ���� ������� ����
	else
	{
		return -1;
	}

}

