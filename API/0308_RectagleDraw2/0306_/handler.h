//handler.h
#ifndef MYHANDLE
#define MYHANDLE
LRESULT OnInitMenuPoUp(HWND hwnd,WPARAM wParam);
LRESULT OnCommand(HWND hwnd,WPARAM wParam,LPARAM lParam);

LRESULT OnConTextMenu(HWND hwnd,LPARAM lParam);

LRESULT OnCreate(HWND hwnd);
LRESULT OnDestroy(HWND hwnd);
LRESULT OnLButtonDown(HWND hwnd,WPARAM wParam, LPARAM lParam);
LRESULT OnRButtonDown(HWND hwnd);
LRESULT OnPaint(HWND hwnd);
LRESULT OnKeyDown(HWND hwnd, WPARAM wParam);
LRESULT OnChar(HWND hwnd, WPARAM wParam);
LRESULT OnTimer(HWND hwnd,WPARAM wParam,LPARAM lParam);

#endif