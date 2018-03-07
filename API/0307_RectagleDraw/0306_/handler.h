//handler.h
#ifndef MYHANDLE
#define MYHANDLE
LRESULT OnCreate(HWND hwnd);
LRESULT OnDestroy();
LRESULT OnLButtonDown(HWND hwnd, LPARAM lParam);
LRESULT OnRButtonDown(HWND hwnd);
LRESULT OnPaint(HWND hwnd);
LRESULT OnKeyDown(HWND hwnd, WPARAM wParam);
LRESULT OnChar(HWND hwnd, WPARAM wParam);

#endif