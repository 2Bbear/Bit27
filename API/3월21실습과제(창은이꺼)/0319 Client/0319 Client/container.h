//container.h

void con_InsertAccount(ADDACCOUNT acc);
void con_DeleteAccount(ADDACCOUNT acc);

void con_AddMoney(ADDMONEY *p);
void con_SubMoney(SUBMONEY *p);
vector<ADDACCOUNT> *wbcon_GetAccountList();