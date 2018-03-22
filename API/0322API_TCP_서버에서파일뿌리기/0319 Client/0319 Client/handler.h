//handler.h

BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

void OnAddMember(HWND hDlg);
void OnMinMember(HWND hDlg);
void OnLogin(HWND hDlg);
void OnLogout(HWND hDlg);
void OnSendCode(HWND hDlg);
void OnSendData(HWND hDlg);

void OnFileOpen(HWND hDlg);
void OnFileSend(HWND hDlg);


//wbnet->handler
void OnLogMessage(TCHAR *msg);
void OnMessage(char* buf, int nRead);