#pragma once
typedef struct tagAccountDetail
{
	int accountNum;
	TCHAR day[50];
	TCHAR time[50];
	//입금
	int deposit;
	//출금
	int withdraw=0;
	//잔금
	TCHAR balance[50];

}AccountDetail;