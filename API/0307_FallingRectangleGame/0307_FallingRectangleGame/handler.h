#pragma once

//init Event
LRESULT OnCreate(HWND hwnd);

//Key Down Event
LRESULT OnKeyDown(HWND hwnd, WPARAM wParam);

//Draw window
LRESULT OnPaint(HWND hwnd);

//Destroy Event
LRESULT OnDestroy(HWND hwnd);