#include "std.h"

vector<MEMBER> g_member;

BOOL is_idCheck(TCHAR *id)
{
	for (int i = 0; i < (int)g_member.size(); i++)
	{
		MEMBER mem = g_member[i];
		if (_tcscmp(mem.id, id) == 0)
			return FALSE;
	}
	return TRUE;
}

BOOL wbcon_InsertMember(ADDMEMBER *mem)
{
	if (is_idCheck(mem->id) == FALSE)
		return FALSE;
	MEMBER data;
	_tcscpy_s(data.name, mem->name);
	_tcscpy_s(data.id, mem->id);
	_tcscpy_s(data.pw, mem->pw);
	data.islogin = FALSE;

	g_member.push_back(data);
	return TRUE;
}
BOOL wbcon_CheckLogin(LOGIN * login)
{
	//��� ����Ʈ���� �ش� ������ �ִ��� �˻�
	for (int i=0;i<(int)g_member.size();i++)
	{
		MEMBER mem = g_member[i];
		//���� �༮�� ã���� ���
		if (_tcscmp(mem.id,login->id)==0&&_tcscmp(mem.pw,login->pw)==0)
		{
			g_member[i].islogin = TRUE;
			return TRUE;
		}
	}
	//���� �༮�� �� ã���� ���
	return FALSE;
}
BOOL wbcon_CheckLogOut(LOGIN * login)
{
	//��� ����Ʈ���� �ش� ������ �ִ��� �˻�
	for (int i = 0; i<(int)g_member.size(); i++)
	{
		MEMBER mem = g_member[i];
		//���� �༮�� ã���� ���
		if (_tcscmp(mem.id, login->id) == 0 && _tcscmp(mem.pw, login->pw) == 0)
		{
			g_member[i].islogin = FALSE;
			return TRUE;
		}
	}
	//���� �༮�� �� ã���� ���
	return FALSE;
}
BOOL wbcon_CheckUnregister(LOGIN * login)
{
	vector<MEMBER> ::iterator d;
	d = g_member.begin();

	//��� ����Ʈ���� �ش� ������ �ִ��� �˻�
	for (int i = 0; i<(int)g_member.size(); i++)
	{
		MEMBER mem = g_member[i];
		//���� �༮�� ã���� ���
		if (_tcscmp(mem.id, login->id) == 0 && _tcscmp(mem.pw, login->pw) == 0)
		{
			d=d + i;
			//����ó��
			g_member.erase(d);

			return TRUE;
		}
	}
	//���� �༮�� �� ã���� ���
	return FALSE;
}

vector<MEMBER> *wbcon_GetMemberList()
{
	return &g_member;
}


TCHAR * wbcon_GetName(LOGIN * login)
{
	for (int i = 0; i<(int)g_member.size(); i++)
	{
		MEMBER mem = g_member[i];
		if (_tcscmp(mem.id, login->id) == 0 && _tcscmp(mem.pw, login->pw) == 0)
		{
			g_member[i].islogin = TRUE;
			return g_member[i].name;
		}
	}
	return TEXT("");
}
