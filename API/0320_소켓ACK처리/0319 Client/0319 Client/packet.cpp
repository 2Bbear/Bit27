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

LOGIN pack_SetLogin(TCHAR * id, TCHAR * pw)
{
	LOGIN data = { 0 };
	data.flag = PACK_LOGIN;
	_tcscpy_s(data.id, id);
	_tcscpy_s(data.pw, pw);
	return data;
}

LOGIN pack_SetLogOut(TCHAR * id, TCHAR * pw, BOOL * _bIsLogin)
{
	printf("pack_SetLogOut\n");

	LOGIN data = { 0 };
	data.flag = PACK_LOGOUT;
	_tcscpy_s(data.id, id);
	_tcscpy_s(data.pw, pw);

	if (*_bIsLogin==TRUE)
	{
		*_bIsLogin = FALSE;
		printf("current IsLogin value %d", *_bIsLogin);
	}
	

	return data;
}
LOGIN pack_SetUnregister(TCHAR * id, TCHAR * pw, BOOL * _bIsLogin)
{
	printf("pack_SetUnregister\n");

	LOGIN data = { 0 };
	data.flag = PACK_UNREGISTER;
	_tcscpy_s(data.id, id);
	_tcscpy_s(data.pw, pw);

	if (*_bIsLogin == TRUE)
	{
		*_bIsLogin = FALSE;
		printf("current IsLogin value %d", *_bIsLogin);
	}


	return data;
}

SHORTMESSAGE pack_SetShortMessage(TCHAR * msg)
{
	printf("pack_SetShortMessage\n");
	SHORTMESSAGE data = { 0 };
	data.flag = PACK_SHORTMESSAGE;
	_tcscpy_s(data.msg, msg);

	return data;
}
