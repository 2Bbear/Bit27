#pragma once

//Command 처리
LRESULT  OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);
//프로그램 종료
LRESULT OnDestroy();
//마우스 처리 //L은 라인, R은 마커
LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnLButtonUp(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnRButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam);
//Paint 처리
LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam);