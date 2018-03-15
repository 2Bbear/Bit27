#pragma once

//�Ա�
void depositAccount(int money,int _accountNum);
//���
void withdrawAccount(int money, int _accountNum);

//idx�� Account��� - 1�� ��� �ش� �Ű������� �Ⱦ��� ã��
Account * findAccount(int _idx,int _accountNum);


//Account ����
void createAccount(int _accountNum, TCHAR * _name, int _balance, TCHAR * _id, TCHAR *_password);
void createAccount(Account temp);
//Account ����
void deleteAccount(int _idx);
//id������ �ε��� �� ���
int findeIdxAccount(TCHAR * _id);


//AccountDetail����
void createAccountDetail(int _accountNum, int _deposit, int _withraw,int _balance);

//�ش� ���� �ε������� ���¹�ȣ�� �´ٸ� �� ���� ������ ��ȯ
AccountDetail matcingAccountDetail(int _accountNum, int _idx);

//Getter Setter========================================================
//AccountList �����͸� �ִ� �Լ�
vector<Account> * getAccountList();
//���� ���� ������ �˷��ִ� �Լ�
int getCurrentAccountCount();