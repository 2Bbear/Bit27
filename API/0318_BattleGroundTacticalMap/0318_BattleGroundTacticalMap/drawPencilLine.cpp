#include"std.h"

static POINTS ptFrom;

void DPL_LButton(LPARAM lParam)
{
	ptFrom = MAKEPOINTS(lParam); 
}

void DPL_MouseMove(HDC hdc, HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//if need hdc , try GetDC(hwnd) function.
	if (wParam & MK_LBUTTON)
	{
		POINTS pt = MAKEPOINTS(lParam);
		HDC hdc = GetDC(hwnd);
		MoveToEx(hdc, ptFrom.x, ptFrom.y, 0);
		LineTo(hdc, pt.x, pt.y);
		ReleaseDC(hwnd, hdc);
		
		ptFrom = pt;
	}
}
