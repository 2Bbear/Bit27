//modal_ui.h

void modal_ui_InitPrint(HWND hDlg, LOGIN* info);
void modal_ui_DataPrint(HWND hDlg);
void modal_ui_GetAccount(HWND hDlg, TCHAR* id, int* accnum, int* balance, TCHAR* date);
void modal_ui_ListPrint(int idx, ADDACCOUNT acc);
void modal_ui_ListPrintALL(vector<ADDACCOUNT> *acclist);
void modal_ui_GetAddMoney(HWND hDlg, int* accnum, int* money);
void modal_ui_GetSubMoney(HWND hDlg, int* accnum, int* money);