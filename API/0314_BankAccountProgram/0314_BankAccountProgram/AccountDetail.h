#pragma once
typedef struct tagAccountDetail
{
	int accountNum;
	TCHAR day[50];
	TCHAR time[50];
	//�Ա�
	int deposit;
	//���
	int withdraw=0;
	//�ܱ�
	TCHAR balance[50];

}AccountDetail;