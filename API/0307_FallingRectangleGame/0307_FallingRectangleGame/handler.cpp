#include"std.h"

#define MOVESPEED 25
#define MONSTERMOVESPEED 50

#define T_ID_CURRENTTIME 1
#define T_ID_MOVEMONSTER 2



extern MyHero g_currentCharacter;
extern Monster g_currentMonster;

//CallBackFunction
typedef VOID(CALLBACK * TIMERPOC)(HWND, UINT, UINT_PTR, DWORD);
	//For Draw Move Monster
void CALLBACK monsterMoveTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{

	RECT rc = { g_currentMonster.currentPoint.x - 25,g_currentMonster.currentPoint.y - 25,g_currentMonster.currentPoint.x + 25,
		g_currentMonster.currentPoint.y + MONSTERMOVESPEED+25 };


	g_currentMonster.moveCharacter(0, MONSTERMOVESPEED);
	
	InvalidateRect(hWnd, &rc, TRUE);

	if (0)
	{
		MessageBox(0, TEXT("�浹"), TEXT("�߿������"), MB_YESNOCANCEL | MB_ICONQUESTION);
	}
	else if (g_currentMonster.currentPoint.y>g_currentCharacter.currentPoint.y+50)
	{
		g_currentMonster.setCurrentPoint(rand()%1000, 0);
		//MessageBox(0, TEXT("��ܻ���"), TEXT("��ܻ���������"), MB_YESNOCANCEL | MB_ICONQUESTION);
	}
}
////////////////////=====================================================

LRESULT OnCreate(HWND hwnd)
{
	//Character Init
	g_currentCharacter.setCurrentPoint(500, 500);
	SendMessage(hwnd,WM_PAINT,0,0);
	//Monster Init
	g_currentMonster.setCurrentPoint(500,0);
	//Timer Init
		//for draw current time
	SetTimer(hwnd, T_ID_CURRENTTIME, 1000, MyTimerProc);//(Ÿ�̸� �޼����� ���� ������,Ÿ�̸��� ��ȣ ����,�ֱⰪ,ȣ��� �Լ�) ���� ������ WM_TIMER �޼����� ���� wParam�� Timer ID�� ���� �־ ����
	SendMessage(hwnd, WM_TIMER, T_ID_CURRENTTIME, NULL);//������ WM_TIMER�� �����Ű�� �Լ�
		//for move monster
	SetTimer(hwnd, T_ID_MOVEMONSTER, 1000, monsterMoveTimerProc);


	return 0;
}
LRESULT OnKeyDown(HWND hwnd, WPARAM wParam)
{
	switch (wParam)
	{
	//Arrow Keys
	case VK_UP:
	{
		RECT rc = { g_currentCharacter.currentPoint.x - 25, g_currentCharacter.currentPoint.y - 25,
			g_currentCharacter.currentPoint.x + 25, g_currentCharacter.currentPoint.y + 25 };
		g_currentCharacter.moveCharacter(0,-MOVESPEED);
		InvalidateRect(hwnd, 0, TRUE);
				  return 0;
	}
	case VK_DOWN:
	{
		RECT rc = { g_currentCharacter.currentPoint.x - 25, g_currentCharacter.currentPoint.y - 25,
			g_currentCharacter.currentPoint.x + 25, g_currentCharacter.currentPoint.y + 25 };
		InvalidateRect(hwnd, &rc, TRUE);
		g_currentCharacter.moveCharacter(0, MOVESPEED);
		InvalidateRect(hwnd, 0, TRUE);
					return 0;
	}
	case VK_LEFT:
	{
		RECT rc = { g_currentCharacter.currentPoint.x - 25, g_currentCharacter.currentPoint.y - 25,
			g_currentCharacter.currentPoint.x + 25, g_currentCharacter.currentPoint.y + 25 };
		InvalidateRect(hwnd, &rc, TRUE);
		g_currentCharacter.moveCharacter(-MOVESPEED, 0);
		InvalidateRect(hwnd, 0, TRUE);
					return 0;
	}
	case VK_RIGHT:
	{
		RECT rc = { g_currentCharacter.currentPoint.x - 25, g_currentCharacter.currentPoint.y - 25,
			g_currentCharacter.currentPoint.x + 25, g_currentCharacter.currentPoint.y + 25 };
		InvalidateRect(hwnd, &rc, TRUE);
		g_currentCharacter.moveCharacter(MOVESPEED, 0);
		InvalidateRect(hwnd, 0, TRUE);
					 return 0;
	}
	}
	return 0;
}

LRESULT OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	//======================================
	//UI �׸���
	draw_UI(hwnd,hdc,&g_currentCharacter);
	draw_CurrentTime(hwnd,hdc);
	//ĳ���� �׸���
	draw_Charcter(hwnd, hdc, &g_currentCharacter);
	//���� �׸���
	draw_Monster(hwnd,hdc,&g_currentMonster);

	//======================================
	EndPaint(hwnd, &ps);
	return 0;
}

LRESULT OnDestroy(HWND hwnd)
{
	
	KillTimer(hwnd, T_ID_CURRENTTIME);
	KillTimer(hwnd, T_ID_MOVEMONSTER);

	PostQuitMessage(0);
	return 0;
}
