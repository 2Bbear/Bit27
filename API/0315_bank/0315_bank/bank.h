#pragma once

//입금
void depositAccount(int money,int _accountNum);
//출금
void withdrawAccount(int money, int _accountNum);

//idx로 Account얻기 - 1일 경우 해당 매개변수는 안쓰고 찾음
Account * findAccount(int _idx,int _accountNum);


//Account 생성
void createAccount(int _accountNum, TCHAR * _name, int _balance, TCHAR * _id, TCHAR *_password);
void createAccount(Account temp);
//Account 삭제
void deleteAccount(int _idx);
//id값으로 인덱스 값 얻기
int findeIdxAccount(TCHAR * _id);


//AccountDetail생성
void createAccountDetail(int _accountNum, int _deposit, int _withraw,int _balance);

//해당 계좌 인덱스에서 계좌번호에 맞다면 그 계좌 정보를 반환
AccountDetail matcingAccountDetail(int _accountNum, int _idx);

//Getter Setter========================================================
//AccountList 포인터를 주는 함수
vector<Account> * getAccountList();
//현재 계좌 갯수를 알려주는 함수
int getCurrentAccountCount();