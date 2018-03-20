//handler.h

BOOL OnInitDialog(HWND hDlg);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

void OnStartServer(HWND hDlg);


void OnLogMessage(TCHAR *msg);
BOOL OnMessage(char* buf, int nRead);

void OnRecvLogin(LOGIN * p);
void OnRecvLogOunt(LOGIN * login);
void OnRecvMember(ADDMEMBER *mem);
void OnRecvUnregister(LOGIN * login);
void OnRecvShortMessage(SHORTMESSAGE * msg);

void OnClientLogMessage(int flag, char* ip, int port);