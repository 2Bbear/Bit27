#pragma once

//Command 처리
LRESULT  OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);
//프로그램 종료
LRESULT OnDestroy();
//마우스 L 버튼 처리
LRESULT OnLbuttonDown(HWND hwnd, WPARAM wParam, LPARAM lParam);