//wbcontainer.h
BOOL is_IdCheck(TCHAR *id);
BOOL wbcon_InsertMember(ADDMEMBER *mem);
BOOL wbcon_DeleteMember(ADDMEMBER *mem);
BOOL wbcon_CheckLogin(LOGIN *login);
BOOL wbcon_CheckLogout(LOGIN *login);
TCHAR*  wbcon_GetName(LOGIN *login);

vector<MEMBER> *wbcon_GetMemberList();