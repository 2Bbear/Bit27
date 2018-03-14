#include"std.h"

vector<Account> g_AccountList;
vector<AccountDetail> g_AccountDetailList;

Account * B_FindAccount(TCHAR * _id)
{
	
	for (int i=0;i<(int)g_AccountList.size();i++)
	{
		if (_tcscmp(g_AccountList[i].id,_id)==0)
		{
			return &g_AccountList[i];
		}
	}
	return NULL;
}

void B_CreateAccountDetail(int _accountNum, int _depo, int _withraw,TCHAR * pBalance)
{
	AccountDetail temp = {0};
	temp.accountNum = _accountNum;
	temp.deposit += _depo;
	temp.withdraw += _withraw;
	_tcscpy(temp.balance, pBalance);
	//====================날짜 구하기

	SYSTEMTIME st;
	GetSystemTime(&st);
	TCHAR buf[50];
	GetDateFormat(LOCALE_USER_DEFAULT, 0, &st, TEXT("yyy년 M월 d일"), buf, 50);
	_tcscpy(temp.day, buf);
	
	//====================시간 구하기
	SYSTEMTIME st2;
	GetLocalTime(&st2);
	TCHAR buf2[50];
	GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st2, TEXT("tt h시 m분 s초"), buf2, 50);
	_tcscpy(temp.time, buf2);
	//=================================
	g_AccountDetailList.push_back(temp);
}
