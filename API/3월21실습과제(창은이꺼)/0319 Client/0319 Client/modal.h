//modal.h

BOOL CALLBACK Acc_DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

void Acc_InitDialog(HWND hDlg, LPARAM lParam);
BOOL Acc_Command(HWND hDlg, WPARAM wParam, LPARAM lParam);
void Acc_Create(HWND hDlg);
void Acc_Delete(HWND hDlg);
void Acc_AddMoney(HWND hDlg);
void Acc_SubMoney(HWND hDlg);

//°èÁÂ OnMessage==============================================================
void Acc_OnAddcount_s(char* buf);
void Acc_OnAddcount_f();

void Acc_OnDelcount_s(char* buf);
void Acc_OnDelcount_f();

void Acc_OnAddMoney(char* buf);

void Acc_OnSubMoney_s(char* buf);
void Acc_OnSubMoney_f();
