#include"std.h"

//��������
vector<Account> g_AccountList;
vector<AccountDetail> g_AccountDetailList;
//

Account * getAccount(int _idx)
{
	return &g_AccountList[_idx];
}

void createAccount(int _accountNum, TCHAR * _name, int _balance, TCHAR * _id, TCHAR * _password)
{
	Account temp;
	temp.accountNum = _accountNum;
	_tcscpy_s(temp.name,_name);

	temp.balance = _balance;
	_tcscpy_s(temp.id, _id);
	_tcscpy_s(temp.password, _password);
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
	int result=-1;

	for (int i=0;i<g_AccountList.size();i++)
	{
		if (_tcscmp(g_AccountList[i].id,_id)==0)
		{
			return i;
		}
		else
		{
			//�ùٸ��� ��ã�����. �ƹ����� ��ã�����
			return -1;
		}
	}

	//���� -1�̸� �ùٸ��� ���� ã�� ���� ����
	return result;
}

void createAccountDetail(int _accountNum, int _deposit, int _withraw)
{
	AccountDetail temp;
	temp.accountNum = _accountNum;
	//--��¥ ���ϱ�

	SYSTEMTIME st;
	GetSystemTime(&st);
	TCHAR buf[50];
	GetDateFormat(LOCALE_USER_DEFAULT, 0, &st, TEXT("yyy�� M�� d��"), buf, 50);
	_tcscpy_s(temp.day, buf);

	//====================�ð� ���ϱ�
	SYSTEMTIME st2;
	GetLocalTime(&st2);
	TCHAR buf2[50];
	GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st2, TEXT("tt h�� m�� s��"), buf2, 50);
	_tcscpy_s(temp.time, buf2);
	//=========================================================
	temp.deposit=_deposit;
	temp.withraw= _withraw;

	g_AccountDetailList.push_back(temp);

	
}

AccountDetail matcingAccountDetail(int _accountNum, int _idx)
{
	if (g_AccountDetailList[_idx].accountNum==_accountNum)
	{
		return g_AccountDetailList[_idx];
	}

	//�ùٸ��� ������ ���޴ٸ� �� ��ī��Ʈ ������ ������ ����. �ֳĸ� �̰� ���� �Լ��� ��� �Լ��� ��� �� ����� �ؾ� �� , ���ٸ� ���� �͵� ó�� �ؾ��ϴϱ�
	return AccountDetail();
}
