#pragma once
void ui_InitDialog(HWND hwnd);

void ui_LogMessage(TCHAR * _msg);

void ui_getAddress(HWND hDlg,TCHAR * ip, int *port);

void ui_SetButtonString(TCHAR * str);

void ui_GetSendMessage(HWND hDlg,TCHAR * msg);

void OnMessage(char * _buf, int _nRead);