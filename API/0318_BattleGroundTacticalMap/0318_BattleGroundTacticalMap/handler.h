#pragma once

//Command ó��
LRESULT  OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);
//���α׷� ����
LRESULT OnDestroy();
//���콺 ó�� //L�� ����, R�� ��Ŀ
LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnLButtonUp(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnRButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam);
//Paint ó��
LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam);