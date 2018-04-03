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
	//유저의 다음 최적의 수 구하기
	int x = -1, y = -1;
	//선택된 cell찾아내기
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
	//선택된 부분 winrate -1 초기화
	m_UserWinRateBoard[x][y] = -1;


	//선택된 cell 십자 winrate 구하기
	//우측 가산
	for (int i = y + 1; i<5; i++)
	{
		if (puser->m_gameboard[x][i].bcheck) { continue; }
		m_UserWinRateBoard[x][i] += 1;
	}

	//좌측 가산
	for (int i = y - 1; i>-1; i--)
	{
		if (puser->m_gameboard[x][i].bcheck) { continue; }
		m_UserWinRateBoard[x][i] += 1;
	}
	//하측 가산
	for (int i = x + 1; i<5; i++)
	{
		if (puser->m_gameboard[i][y].bcheck) { continue; }
		m_UserWinRateBoard[i][y] += 1;
	}

	//상측 가산
	for (int i = x - 1; i>-1; i--)
	{
		if (puser->m_gameboard[i][y].bcheck) { continue; }
		m_UserWinRateBoard[i][y] += 1;
	}

	//대각 선 cell winrate 구하기
	int temp_x = x;
	int temp_y = y;
	//대각선에 존재하는지 판단하기
	// \ 대각선
	if (x == y)
	{
		temp_x += 1;
		temp_y += 1;

		/*TCHAR st2[20];
		wsprintf(st2, TEXT("\\ 대각선"));
		AfxMessageBox(st2);*/
		//하 대각선 가산
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

		//초기값
		temp_x = x;
		temp_y = y;

		temp_x -= 1;
		temp_y -= 1;
		//상 대각선 가산
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
	// /대각선
	if (sumxy == 4)
	{


		//초기값
		temp_x = x;
		temp_y = y;

		temp_x += 1;
		temp_y -= 1;

		//하 대각선 가산
		while (temp_x<5)
		{
			/*	TCHAR st2[20];
			wsprintf(st2, TEXT("tempx : %d tempy %d"), temp_x, temp_y);
			AfxMessageBox(st2);*/
			//트루값일때 인덱스가 증가안해서 계속 반복함

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



		//초기값
		temp_x = x;
		temp_y = y;

		temp_x -= 1;
		temp_y += 1;

		//상 대각선 가산
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
	//분석
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
	//전체 초기화
	for (int i =0;i<5;i++)
	{
		for (int j=0;j<5;j++)
		{
			m_winRateBoard[i][j] = 0;
		}
	}
	//중앙부 setting
	m_winRateBoard[2][2] += 2;

	//중앙외각 setting
		//좌우
	m_winRateBoard[2][1] += 0;
	m_winRateBoard[2][3] += 0;
		//상대각
	m_winRateBoard[1][1] += 0;
	m_winRateBoard[1][3] += 0;
		//상하
	m_winRateBoard[1][2] += 0;
	m_winRateBoard[3][2] += 0;
		//하대각
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
	//중앙부 setting
	m_UserWinRateBoard[2][2] += 2;

	//중앙외각 setting
	//좌우
	m_UserWinRateBoard[2][1] += 0;
	m_UserWinRateBoard[2][3] += 0;
	//상대각
	m_UserWinRateBoard[1][1] += 0;
	m_UserWinRateBoard[1][3] += 0;
	//상하
	m_UserWinRateBoard[1][2] += 0;
	m_UserWinRateBoard[3][2] += 0;
	//하대각
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

	for (int i = 0; i<6; i++) //가로선 그리기
	{
		pDC->MoveTo(10+ MOVE_X, 10 + i * 50);
		pDC->LineTo(50 * 5 + 10+ MOVE_X, 10 + i * 50);
	}

	for (int i = 0; i<6; i++) //세로선 그리기
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
	//패턴 검색
		//가로열
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
		//세로열
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
	//누를 곳 
	
	//세로 최고 값
	int Rmax = 0;
	int Rresult = 0;//행을 저장할 곳
	for (int i=0;i<5;i++)
	{
		if (check_row[i] > Rmax)
		{
			Rmax = check_row[i];
			Rresult = i;
			break;
		}
	}
	//가로 최고 값
	int Cmax = 0;
	int Cresult = 0;//열을 저장할 곳
	for (int i = 0; i<5; i++)
	{
		if (check_col[i] >= Cmax)
		{
			Cmax = check_col[i];
			Cresult = i;
			break;
		}
	}
	//가장 많은 true 값의 선을 찾아 냄
	if (Rmax>= Cmax)// 가로선에서 찾았을 경우,또는 둘다 같을 경우
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
	if(Cmax)//세로선에서 찾았을경우
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
	// 숫자를 그려준다.

	CString str;
	str.Format(TEXT("%d"), iNum);



	// 원래 있던 숫자(0)을 지운다
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

		// 원하는 숫자를 그려준다.
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

		// 원하는 숫자를 그려준다.
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
	}


	if (str.GetLength() > 1) // 숫자가 두자리일때 처리
		pDC->TextOut(27 + iCol * 50+ MOVE_X, 30 + iRow * 50, str);
	else
		pDC->TextOut(30 + iCol * 50+ MOVE_X, 30 + iRow * 50, str);


	pDC->SelectObject(lbr);
	pDC->SelectObject(lodp);
}

bool CComGame::PointCheck(CPoint pt)
{
	if (pt.x > 260 || pt.y > 260) // 게임과 관련 없는곳 클릭시
		return false;
	if (pt.x <10 || pt.y <10)
		return false;

	return true;
}

void CComGame::PosToIndex(CPoint pnt, int & iRow, int & iCol)
{
	int i, j;
	for (i = 0; i<5; i++) //행 결정(Row)
	{
		if ((pnt.y > 10 + i * 50) &&
			pnt.y <= (10 + (i + 1) * 50)
			)
			break;
	}

	for (j = 0; j<5; j++) //열 결정(Col)
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
	// 마우스를 클릭하는 순서대로 번호를 매긴다.
	if (!m_gameboard[iRow][iCol].number)
	{
		m_gameboard[iRow][iCol].number = oder++;
		DrawNum(pdc, iRow, iCol, m_gameboard[iRow][iCol].number);
	}
	if (oder>25)
	{
		m_bStart = TRUE;
		//다음번 게임을 위해 초기화
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
	for (i = 0; i<5; i++) // 가로 검사
	{
		for (j = 0; j<5; j++)
		{
			if (!m_gameboard[i][j].bcheck)
				break;
		}
		if (j == 5)
			iLine++;
	}


	for (i = 0; i<5; i++) // 세로 검사
	{
		for (j = 0; j<5; j++)
		{
			if (!m_gameboard[j][i].bcheck)
				break;
		}
		if (j == 5)
			iLine++;
	}

	for (i = 0; i<5; i++) // 대각선 검사(＼ 방향)
	{
		if (!m_gameboard[i][i].bcheck)
			break;
	}
	if (i == 5)
		iLine++;

	for (i = 0, j = 4; i<5; i++, j--) // 대각선 검사(／ 방향)
	{
		if (!m_gameboard[i][j].bcheck)
			break;
	}
	if (i == 5) // 5줄 이상이면 빙고
		iLine++;

	if (iLine >= 5)
		return TRUE;
	else
		return FALSE;
}


int CComGame::AI_SelectNumber2(int selectednum)
{
	
	int x=-1, y=-1;
	//선택된 cell찾아내기
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
	//선택된 부분 winrate -1 초기화
	m_winRateBoard[x][y] = -1;

	
	//선택된 cell 십자 winrate 구하기
		//우측 가산
	for (int i= y+1;i<5;i++ )
	{
		if (m_gameboard[x][i].bcheck) { continue; }
		m_winRateBoard[x][i] += 1;
	}
	
		//좌측 가산
	for (int i=y-1;i>-1;i--)
	{
		if (m_gameboard[x][i].bcheck) { continue; }
		m_winRateBoard[x][i] += 1;
	}
		//하측 가산
	for (int i= x+1;i<5;i++)
	{
		if (m_gameboard[i][y].bcheck) { continue; }
		m_winRateBoard[i][y] += 1;
	}

		//상측 가산
	for (int i=x-1;i>-1;i--)
	{
		if (m_gameboard[i][y].bcheck) { continue; }
		m_winRateBoard[i][y] += 1;
	}
	
	//대각 선 cell winrate 구하기
	int temp_x = x;
	int temp_y = y;
		//대각선에 존재하는지 판단하기
		// \ 대각선
	if (x == y)
	{
		temp_x += 1;
		temp_y += 1;

		/*TCHAR st2[20];
		wsprintf(st2, TEXT("\\ 대각선"));
		AfxMessageBox(st2);*/
		//하 대각선 가산
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
		
		//초기값
		temp_x = x;
		temp_y = y;

		temp_x -= 1;
		temp_y -= 1;
		//상 대각선 가산
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
		// /대각선
	if (sumxy ==4)
	{
		

		//초기값
		temp_x = x;
		temp_y = y;

		temp_x += 1;
		temp_y -= 1;
		
		//하 대각선 가산
		while (temp_x<5)
		{
		/*	TCHAR st2[20];
			wsprintf(st2, TEXT("tempx : %d tempy %d"), temp_x, temp_y);
			AfxMessageBox(st2);*/
			//트루값일때 인덱스가 증가안해서 계속 반복함

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
		
	

		//초기값
		temp_x = x;
		temp_y = y;

		temp_x -= 1;
		temp_y += 1;

		//상 대각선 가산
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
	//분석
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
	//최고 점수의 cell 선택
	m_gameboard[t_x][t_y].bcheck = true;
	
	//======================
	
	//======================
	return m_gameboard[t_x][t_y].number;
}

int CComGame::BlockClick(int n)
{

	//게임 진행
	if (m_bStart == true)
	{
		int num= AI_SelectNumber2(n);
		IsGameEnd();
		if (IsGameEnd() == true)
		{
			AfxMessageBox(TEXT("Com Win"));
		}
		//번호 선택
		return num;
	}
	//블럭의 번호를 클릭된 순서대로 변경
	else
	{
		return -1;
	}

}

