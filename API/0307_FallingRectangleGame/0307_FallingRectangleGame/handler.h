#pragma once

//init Event
LRESULT OnCreate(HWND hwnd,MyHero * _hero);

//Key Down Event
LRESULT OnKeyDown(HWND hwnd, WPARAM wParam, MyHero * _hero);

//Draw window
LRESULT OnPaint(HWND hwnd, MyHero * _hero);