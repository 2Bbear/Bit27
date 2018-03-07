#include"std.h"

#define CURTIMEPOSITION {0,0,300,20}
#define UI_HPPOSITION {0,20,300,40};
#define UI_SCOREPOSITION {0,40,300,60};


//CallBackFunction
typedef VOID(CALLBACK * TIMERPOC)(HWND, UINT, UINT_PTR, DWORD);

//For Draw Current Time
void CALLBACK MyTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	RECT rc = CURTIMEPOSITION;
	InvalidateRect(hWnd, &rc, TRUE);
}

void draw_Charcter(HWND hwnd, HDC hdc, MyHero * _hero)
{
	Rectangle(hdc, _hero->currentPoint.x-25, _hero->currentPoint.y - 25, _hero->currentPoint.x + 25, _hero->currentPoint.y + 25);
}

void draw_Monster(HWND hwnd, HDC hdc, Monster * _monster)
{
	Rectangle(hdc, _monster->currentPoint.x - 25, _monster->currentPoint.y - 25, _monster->currentPoint.x + 25, _monster->currentPoint.y + 25);
}

void draw_UI(HWND hwnd, HDC hdc, MyHero * _hero)
{
	TCHAR buf[30];

	//hp 표시
	
	wsprintf(buf, TEXT("HP : %d"), _hero->hp);
	RECT rc = UI_HPPOSITION;
	DrawText(hdc, buf, -1, &rc, DT_LEFT);

	//점수 표시
	wsprintf(buf, TEXT("SCORE : %d"), _hero->score);
	rc = UI_SCOREPOSITION;
	DrawText(hdc, buf, -1, &rc, DT_LEFT);
}

void draw_CurrentTime(HWND hwnd, HDC hdc)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	TCHAR buf[100];
	wsprintf(buf, TEXT("CurrentTime : %d:%d:%d"), st.wHour, st.wMinute, st.wSecond);

	RECT rc = CURTIMEPOSITION;

	DrawText(hdc, buf, -1, &rc, DT_LEFT);
}
