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

CODEMESSAGE pack_SetCodeMessage(TCHAR *msg)
{
	CODEMESSAGE data = { 0 };
	data.flag = PACK_CODEMESSAGE;
	_tcscpy_s(data.msg, msg);

	return data;
}