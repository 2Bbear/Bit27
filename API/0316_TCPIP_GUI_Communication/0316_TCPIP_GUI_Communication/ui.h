#pragma once


//ui 초기화 하는 함수
void ui_InitControl(HWND hDlg);

//접속개수 설정하는 함수
void ui_SetCurrentConnectCountStatic(int n);

//port 번호 dlg에서 읽어오는 함수
int ui_getPort(HWND hDlg);

//메세지 창에 메세지를 출력하는 함수
void ui_LogMessage(TCHAR * _msg);