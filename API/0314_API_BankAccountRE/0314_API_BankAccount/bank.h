#pragma once

//idx�� Account���
Account * getAccount(int _idx);
//Account ����
void createAccount(int _accountNum,TCHAR * _name,TCHAR * _balance,TCHAR * _id,TCHAR *_password);
//Account ����
void deleteAccount(int _idx);
//id������ �ε��� �� ���
int findeIdxAccount(TCHAR * _id);


//AccountDetail����
void createAccountDetail(int _accountNum, TCHAR * _deposit,TCHAR * _withraw);

//�ش� ���� �ε������� ���¹�ȣ�� �´ٸ� �� ���� ������ ��ȯ
AccountDetail matcingAccountDetail()