//ui.h

void ui_InitControl(HWND hDlg);

void ui_LogMessage(TCHAR *msg);

void ui_getAddress(HWND hDlg, TCHAR* ip, int *port);

void ui_SetButtonString(TCHAR * msg);

void ui_SetLoginButtonString(TCHAR * msg);

void ui_GetAddMember(HWND hDlg, TCHAR*name, TCHAR *id, TCHAR*pw);

void ui_GetMinMember(HWND hDlg, TCHAR* name, TCHAR* id, TCHAR* pw);

void ui_GetLogin(HWND hDlg, TCHAR *id, TCHAR *pw);

void ui_GetSendMessage(HWND hDlg, TCHAR* msg);