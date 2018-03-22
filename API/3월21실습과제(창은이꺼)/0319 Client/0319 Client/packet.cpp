//packet.cpp

#include "std.h"

ADDMEMBER pack_SetAddMember(TCHAR*name, TCHAR*id, TCHAR*pw)
{
	ADDMEMBER data = { 0 };
	data.flag = PACK_ADDMEMBER;
	_tcscpy_s(data.name, name);
	_tcscpy_s(data.id, id);
	_tcscpy_s(data.pw, pw);
	return data;
}

ADDMEMBER pack_SetMinMember(TCHAR*name, TCHAR*id, TCHAR*pw)
{
	ADDMEMBER data = { 0 };
	data.flag = PACK_MINMEMBER;
	_tcscpy_s(data.name, name);
	_tcscpy_s(data.id, id);
	_tcscpy_s(data.pw, pw);
	return data;
}

LOGIN pack_SetLogiin(TCHAR *id, TCHAR *pw)
{
	LOGIN data = { 0 };
	data.flag = PACK_LOGIN;
	_tcscpy_s(data.id, id);
	_tcscpy_s(data.pw, pw);

	return data;

}

LOGIN pack_SetLogout(TCHAR *id, TCHAR *pw)
{
	LOGIN data = { 0 };
	data.flag = PACK_LOGOUT;
	_tcscpy_s(data.id, id);
	_tcscpy_s(data.pw, pw);

	return data;
}


SHORTMESSAGE pack_SetShortMessage(TCHAR *msg)
{
	SHORTMESSAGE data = { 0 };
	data.flag = PACK_SHORTMESSAGE;
	_tcscpy_s(data.msg, msg);

	return data;
}

ADDACCOUNT pack_SetAddAccount(TCHAR* id, int accnum, int balance, TCHAR* date)
{
	ADDACCOUNT data = { 0 };
	data.flag = PACK_ADDACCOUNT;

	_tcscpy_s(data.id, id);
	data.accnum = accnum;
	data.balance = balance;
	_tcscpy_s(data.date, date);

	return data;
}

ADDACCOUNT pack_SetDelAccount(TCHAR* id, int accnum, int balance, TCHAR* date)
{
	ADDACCOUNT data = { 0 };
	data.flag = PACK_DELACCOUNT;

	_tcscpy_s(data.id, id);
	data.accnum = accnum;
	data.balance = balance;
	_tcscpy_s(data.date, date);

	return data;
}

ADDMONEY pack_SetAddMoney(int accnum, int money)
{
	ADDMONEY data = { 0 };
	data.flag = PACK_ADDMONEY;

	data.accnum = accnum;
	data.money = money;

	return data;
}

SUBMONEY pack_SetSubMoney(int accnum, int money)
{
	SUBMONEY data = { 0 };
	data.flag = PACK_SUBMONEY;

	data.accnum = accnum;
	data.money = money;

	return data;
}