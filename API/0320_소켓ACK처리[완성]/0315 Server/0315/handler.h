//handler.h

BOOL OnInitDialog(HWND hDlg);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

void OnStartServer(HWND hDlg);


void OnLogMessage(TCHAR *msg);
BOOL OnMessage(char* buf, int nRead);

void OnRecvMember(ADDMEMBER *mem);
void OnRecvMinMember(ADDMEMBER *mem);
void OnRecvLogin(LOGIN *login);
void OnRecvLogout(LOGIN *login);
void OnRecvShortMessage(SHORTMESSAGE *msg);

void OnClientLogMessage(int flag, char* ip, int port);