#pragma once
typedef struct _LINE {
	POINTS ptFrom;
	POINTS ptTo;
} LINE;


void DPL_LButton(LPARAM lParam);
void DPL_MouseMove(HDC hdc, HWND hwnd,WPARAM wParam, LPARAM lParam);
