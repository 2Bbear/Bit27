BOOL is_idCheck(TCHAR *id);


BOOL wbcon_InsertMember(ADDMEMBER *mem);
BOOL wbcon_CheckLogin(LOGIN * login);


vector<MEMBER> *wbcon_GetMemberList();

TCHAR * wbcon_GetName(LOGIN * login);

//�ش� ����� login���� �� ����
BOOL wbcon_CheckLogOut(LOGIN * login);
//�ش� ����� ����
BOOL wbcon_CheckUnregister(LOGIN * login);