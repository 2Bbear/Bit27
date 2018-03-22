//wbcontainer.h
BOOL is_IdCheck(TCHAR *id);
BOOL wbcon_InsertMember(ADDMEMBER *mem);
BOOL wbcon_DeleteMember(ADDMEMBER *mem);
BOOL wbcon_CheckLogin(LOGIN *login);
BOOL wbcon_CheckLogout(LOGIN *login);
TCHAR*  wbcon_GetName(LOGIN *login);

vector<MEMBER> *wbcon_GetMemberList();
vector<ACCOUNT> *wbcon_GetAccountList();

BOOL is_AccNumCheck(int accnum);
ACCOUNT* wbcon_GetAccount(ADDMONEY* money);
BOOL wbcon_InsertAccount(ADDACCOUNT* acc);
BOOL wbcon_DeleteAccount(ADDACCOUNT* acc);
void wbcon_AddMoney(ADDMONEY* money, ACCOUNT* acc);
BOOL wbcon_SubPossible(ACCOUNT* acc, SUBMONEY* money);
void wbcon_SubMoney(SUBMONEY* money, ACCOUNT* acc);