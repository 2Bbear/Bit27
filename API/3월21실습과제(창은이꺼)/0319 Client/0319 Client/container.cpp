//container.cpp

#include "std.h"

vector<ADDACCOUNT>		g_account;

void con_InsertAccount(ADDACCOUNT acc)
{
	ADDACCOUNT data;
	data.accnum = acc.accnum;
	data.balance = acc.balance;
	_tcscpy_s(data.id, acc.id);
	_tcscpy_s(data.date, acc.date);

	g_account.push_back(data);
}

void con_DeleteAccount(ADDACCOUNT acc)
{
	//삭제할 부분의 acc객체 얻어오기..
	int i;
	for (i = 0; i < (int)g_account.size(); i++)
	{
		ADDACCOUNT data = g_account[i];
		if (data.accnum == acc.accnum)
			break;
	}

	// 삭제
	vector<ADDACCOUNT>::iterator p = g_account.begin();
	p = p + i;
	g_account.erase(p);
}

void con_AddMoney(ADDMONEY *p)
{
	for (int i = 0; i < (int)g_account.size(); i++)
	{
		if (p->accnum == g_account[i].accnum)
			g_account[i].balance = p->balance;
	}
}

void con_SubMoney(SUBMONEY *p)
{
	for (int i = 0; i < (int)g_account.size(); i++)
	{
		if (p->accnum == g_account[i].accnum)
			g_account[i].balance = p->balance;
	}
}

vector<ADDACCOUNT> *wbcon_GetAccountList()
{
	return &g_account;
}