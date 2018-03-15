#include"std.h"

//전역변수
vector<Account> g_AccountList;
vector<AccountDetail> g_AccountDetailList;
//

void depositAccount(int money, int _accountNum)
{
	Account * temp = findAccount(-1, _accountNum);
	
	if (temp->balance <= 0)
	{
		temp->balance = 0;
	}
	createAccountDetail(_accountNum, money, 0, temp->balance);
	temp->balance += money;
}

void withdrawAccount(int money, int _accountNum)
{
	Account * temp = findAccount(-1, _accountNum);
	temp->balance -= money;
	if (temp->balance<=0)
	{
		temp->balance = 0;
	}
	//0315 출금이 2번 되서 변경함=========================================================
	//createAccountDetail(_accountNum, 0, 0, temp->balance);
	//=================================
	createAccountDetail(_accountNum, 0, money, temp->balance);
	
	if (temp->balance <= 0)
	{
		temp->balance = 0;
	}
}

Account * findAccount(int _idx, int _accountNum)
{
	if (_idx!=-1)
	{
		return &g_AccountList[_idx];
	}
	else if (_accountNum!=-1)
	{
		for (int i =0;i<(int)g_AccountList.size();i++)
		{
			if (g_AccountList[i].accountNum==_accountNum)
			{
				return &g_AccountList[i];
			}
		}
		return 0;
	}
	else
	{
		return 0;
	}
}

void createAccount(int _accountNum, TCHAR * _name, int _balance, TCHAR * _id, TCHAR * _password)
{
	Account temp;
	temp.accountNum = _accountNum;
	_tcscpy_s(temp.name, _name);

	temp.balance = _balance;
	_tcscpy_s(temp.id, _id);
	_tcscpy_s(temp.password, _password);
	g_AccountList.push_back(temp);
}

void createAccount(Account temp)
{
	g_AccountList.push_back(temp);
}

void deleteAccount(int _idx)
{
	vector<Account>::iterator iter;
	iter = g_AccountList.begin();

	iter += _idx;
	g_AccountList.erase(iter);


}

int findeIdxAccount(TCHAR * _id)
{
	int result = -1;

	for (int i = 0; i<(int)g_AccountList.size(); i++)
	{
		if (_tcscmp(g_AccountList[i].id, _id) == 0)
		{
			return i;
		}
	
	}

	//만약 -1이면 올바르게 값을 찾지 못한 상태
	return result;
}

void createAccountDetail(int _accountNum, int _deposit, int _withraw, int _balance)
{
	AccountDetail temp;
	temp.accountNum = _accountNum;
	//--날짜 구하기

	SYSTEMTIME st;
	GetSystemTime(&st);
	TCHAR buf[50];
	GetDateFormat(LOCALE_USER_DEFAULT, 0, &st, TEXT("yyy년 M월 d일"), buf, 50);
	_tcscpy_s(temp.day, buf);

	//====================시간 구하기
	SYSTEMTIME st2;
	GetLocalTime(&st2);
	TCHAR buf2[50];
	GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st2, TEXT("tt h시 m분 s초"), buf2, 50);
	_tcscpy_s(temp.time, buf2);
	//=========================================================
	temp.deposit = _deposit;
	temp.withraw = -(_withraw);
	//출금 오류 발생 대처==========================
	temp.balance = _deposit + _balance; // 야 이거 문제야
	//=============================================
	//temp.balance = _deposit+ _balance-_withraw ; // 야 이거 문제야

	if (temp.balance<=0)
	{
		temp.balance = 0;
	}
	g_AccountDetailList.push_back(temp);


}

AccountDetail matcingAccountDetail(int _accountNum, int _idx)
{
	if (g_AccountDetailList[_idx].accountNum == _accountNum)
	{
		return g_AccountDetailList[_idx];
	}

	//올바르게 구하지 못햇다면 빈 어카운트 디테일 데이터 전달. 왜냐면 이걸 쓰는 함수는 출력 함수라서 어떻게 든 출력은 해야 함 , 없다면 없는 것도 처리 해야하니까
	return AccountDetail();
}

vector<Account>* getAccountList()
{
	return &g_AccountList;
}

int getCurrentAccountCount()
{
	return (int)g_AccountList.size();
}
