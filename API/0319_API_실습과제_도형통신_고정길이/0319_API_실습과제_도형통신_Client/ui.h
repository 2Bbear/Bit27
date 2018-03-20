#pragma once

//Dlg 초기화
void ui_InitDlg(HWND hDlg);

//도형 그리기
void ui_Draw(HDC hdc,int flag,int x, int y, int width, TCHAR * str);