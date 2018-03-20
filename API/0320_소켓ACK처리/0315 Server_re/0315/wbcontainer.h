BOOL is_idCheck(TCHAR *id);


BOOL wbcon_InsertMember(ADDMEMBER *mem);
BOOL wbcon_CheckLogin(LOGIN * login);


vector<MEMBER> *wbcon_GetMemberList();

TCHAR * wbcon_GetName(LOGIN * login);

//해당 멤버의 login상태 값 변경
BOOL wbcon_CheckLogOut(LOGIN * login);
//해당 멤버를 삭제
BOOL wbcon_CheckUnregister(LOGIN * login);