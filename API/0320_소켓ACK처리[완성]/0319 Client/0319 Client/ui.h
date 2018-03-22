//ui.h

void ui_EnableButton(BOOL bmin, BOOL out, BOOL send, BOOL login);

void ui_InitControl(HWND hDlg);

void ui_LogMessage(TCHAR *msg);

void ui_getAddress(HWND hDlg, TCHAR* ip, int *port);

void ui_SetButtonString(TCHAR * msg);

void ui_SetLoginButtonString(TCHAR * msg);

void ui_GetAddMember(HWND hDlg, TCHAR*name, TCHAR *id, TCHAR*pw);

void ui_GetMinMember(HWND hDlg, TCHAR* name, TCHAR* id, TCHAR* pw);

void ui_GetLogin(HWND hDlg, TCHAR *id, TCHAR *pw);

void ui_GetSendMessage(HWND hDlg, TCHAR* msg);

void 	ui_GetSendCodeMessage(HWND hDlg, TCHAR* msg);

void ui_PrintCodeLine(TCHAR *msg);

void ui_GetFileInfo(HWND hDlg, TCHAR * path, TCHAR * name);

void ui_GetFileName(TCHAR * _name);

void ui_GetFilePathOrName(HWND hDlg, TCHAR * _path, TCHAR * _name);