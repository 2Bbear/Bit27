//wbcontainer.cpp
//�����͸� �����ϴ� ���..

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
	if (is_IdCheck(mem->id) == FALSE) //�ߺ��� ID�� ���� ��� FALSE�ϱ�.
		return FALSE;
	MEMBER data;
	_tcscpy_s(data.name, mem->name);
	_tcscpy_s(data.id, mem->id);
	_tcscpy_s(data.pw, mem->pw);
	data.islogin = FALSE;

	g_member.push_back(data);
	return TRUE;
	//���� �ϰڴٰ�� ������ ,, �����ε� ������ �� �Ǵ°�? Ȯ��..
	//id�� �ߺ��Ǹ� �ȵȴٴ� ���� ����..�ϱ� ���� is_IdCheck..
}

BOOL wbcon_DeleteMember(ADDMEMBER *mem)
{
	if (is_IdCheck(mem->id) == TRUE) //�ߺ��� ID�� �־�� ������ �� ����..
		return FALSE;


	//������ �κ��� mem��ü ������..
	int i; 
	for (i = 0; i < (int)g_member.size(); i++)
	{
		MEMBER data = g_member[i];
		if (_tcscmp(data.id, mem->id) == 0)
			break;
	}

	// ����
	vector<MEMBER>::iterator p = g_member.begin();
	p = p + i;
	g_member.erase(p);

	return TRUE;

}

BOOL wbcon_CheckLogin(LOGIN *login)
{
	//���͸� ��ȸ�ϸ鼭 �ϳ��� �����ü�� �����ͼ� id,pw�� ��ġ ���θ� �Ǵ� .�α��� �ϱ����� 
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
			g_member[i].islogin = TRUE; //mem�� �������� �̱ⶫ��
			return g_member[i].name;
		}
	}
	return TEXT("");
}


vector<MEMBER> *wbcon_GetMemberList()
{
	return &g_member;
}

