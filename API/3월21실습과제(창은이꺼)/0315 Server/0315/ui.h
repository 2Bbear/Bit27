//ui.h

void ui_InitControl(HWND hDlg);

int ui_getPort(HWND hDlg);

void ui_LogMessage(TCHAR *msg);

void ui_MemberPrintALL(vector<MEMBER> *memlist);
void ui_AddListData(int idx, MEMBER mem);

void ui_AccListData(int idx, ACCOUNT acc);
void ui_AccountPrintALL(vector<ACCOUNT> *acclist);