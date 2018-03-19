#include"std.h"

ADDMEMBER  pack_SetAddMember(TCHAR * _name, TCHAR * _id, TCHAR * _password)
{
	ADDMEMBER data = {0};
	data.flag = PACK_ADDMEMBER;

	_tcscpy_s(data.name, _name);
	_tcscpy_s(data.id, _id);
	_tcscpy_s(data.pw, _password);


	return data;
}

LOGIN pack_SetLoginData(TCHAR * _id, TCHAR * _password)
{
	LOGIN data = { 0 };
	data.flag = PACK_LOGIN;
	_tcscpy_s(data.id, _id);
	_tcscpy_s(data.pw, _password);

	return data;
}

SHORTMESSAGE pack_SetShortMessage()
{
	SHORTMESSAGE data = { 0 };
	data.flag = PACK_SHORTMESSAGE;

	return data;
}