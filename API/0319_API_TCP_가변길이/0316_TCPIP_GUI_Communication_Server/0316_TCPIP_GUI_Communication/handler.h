#pragma once
//Dlg init function
BOOL OnInitDlg(HWND hDlg, WPARAM wParam, LPARAM lParam);

//dlg message ó���ϴ� �Լ�
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

//======================================================
//���� �����Ű�� �Լ�
void OnStartServer(HWND hDlg);
//�������� �޼��� �޴� �Լ�
void OnLogMessage(TCHAR * msg);
//
void OnClientLogMessage(int flag, char * ip, int port);

//
void OnMessage(char * _buf, int _nRead);