//wbcontainer.cpp
//데이터를 관리하는 모듈..

#include "std.h"

vector<MEMBER> g_member;

BOOL is_IdCheck(TCHAR *id)
{
	for (int i = 0l; i < (int)g_member.size(); i++)
	{
		MEMBER mem = g_member[i];
		if (_tcscmp(mem.id, id) == 0)
			return FALSE;

	}
	return TRUE;
}


BOOL wbcon_InsertMember(ADDMEMBER *mem)
{
	if (is_IdCheck(mem->id) == FALSE) //중복된 ID가 있을 경우 FALSE니까.
		return FALSE;
	MEMBER data;
	_tcscpy_s(data.name, mem->name);
	_tcscpy_s(data.id, mem->id);
	_tcscpy_s(data.pw, mem->pw);
	data.islogin = FALSE;

	g_member.push_back(data);
	return TRUE;
	//저장 하겠다고는 했지만 ,, 실제로도 저장이 잘 되는가? 확인..
	//id는 중복되면 안된다는 것을 구현..하기 위해 is_IdCheck..
}

BOOL wbcon_DeleteMember(ADDMEMBER *mem)
{
	if (is_IdCheck(mem->id) == TRUE) //중복된 ID가 있어야 삭제할 수 있음..
		return FALSE;


	//삭제할 부분의 mem객체 얻어오기..
	int i; 
	for (i = 0; i < (int)g_member.size(); i++)
	{
		MEMBER data = g_member[i];
		if (_tcscmp(data.id, mem->id) == 0)
			break;
	}

	// 삭제
	vector<MEMBER>::iterator p = g_member.begin();
	p = p + i;
	g_member.erase(p);

	return TRUE;

}

BOOL wbcon_CheckLogin(LOGIN *login)
{
	//벡터를 순회하면서 하나씩 멤버객체를 가져와서 id,pw값 일치 여부를 판단 .로그인 하기위해 
	for (int i = 0; i < (int)g_member.size(); i++)
	{
		MEMBER mem = g_member[i];
		if (_tcscmp(mem.id, login->id) == 0 && _tcscmp(mem.pw, login->pw) == 0)
		{
			g_member[i].islogin = TRUE;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL wbcon_CheckLogout(LOGIN *login)
{
	for (int i = 0; i < (int)g_member.size(); i++)
	{
		MEMBER mem = g_member[i];
		if (_tcscmp(mem.id, login->id) == 0 && _tcscmp(mem.pw, login->pw) == 0)
		{
			g_member[i].islogin = FALSE;
			return TRUE;
		}
	}
	return FALSE;
}


TCHAR*  wbcon_GetName(LOGIN *login)
{
	for (int i = 0; i < (int)g_member.size(); i++)
	{
		MEMBER mem = g_member[i];
		if (_tcscmp(mem.id, login->id) == 0 && _tcscmp(mem.pw, login->pw) == 0)
		{
			g_member[i].islogin = TRUE; //mem은 지역변수 이기땜ㄴ
			return g_member[i].name;
		}
	}
	return TEXT("");
}


vector<MEMBER> *wbcon_GetMemberList()
{
	return &g_member;
}

