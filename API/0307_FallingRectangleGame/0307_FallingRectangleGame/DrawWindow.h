#pragma once

//CallBackFunction
	//For Draw Current Time
void CALLBACK MyTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);


//캐릭터를 화면에 그리는 함수
void draw_Charcter(HWND hwnd, HDC hdc,MyHero * _hero);

//몬스터를 화면에 그리는 함수
void draw_Monster(HWND hwnd, HDC hdc, Monster * _hero);
//UI를 화면에 그리는 함수
void draw_UI(HWND hwnd, HDC hdc, MyHero * _hero);
void draw_CurrentTime(HWND hwnd, HDC hdc);