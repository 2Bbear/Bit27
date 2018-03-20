#pragma once
//Dlg init function
BOOL OnInitDlg(HWND hDlg, WPARAM wParam, LPARAM lParam);

//dlg message 처리하는 함수
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

//======================================================
//서버 실행시키는 함수
void OnStartServer(HWND hDlg);
//서버에서 메세지 받는 함수
void OnLogMessage(TCHAR * msg);
//
void OnClientLogMessage(int flag, char * ip, int port);

//
void OnMessage(char * _buf, int _nRead);