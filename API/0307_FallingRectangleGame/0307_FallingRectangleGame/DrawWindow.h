#pragma once

//CallBackFunction
	//For Draw Current Time
void CALLBACK MyTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);


//ĳ���͸� ȭ�鿡 �׸��� �Լ�
void draw_Charcter(HWND hwnd, HDC hdc,MyHero * _hero);

//���͸� ȭ�鿡 �׸��� �Լ�
void draw_Monster(HWND hwnd, HDC hdc, Monster * _hero);
//UI�� ȭ�鿡 �׸��� �Լ�
void draw_UI(HWND hwnd, HDC hdc, MyHero * _hero);
void draw_CurrentTime(HWND hwnd, HDC hdc);