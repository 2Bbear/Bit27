#pragma once

//idx로 Account얻기
Account * getAccount(int _idx);
//Account 생성
void createAccount(int _accountNum,TCHAR * _name,int _balance,TCHAR * _id,TCHAR *_password);
//Account 삭제
void deleteAccount(int _idx);
//id값으로 인덱스 값 얻기
int findeIdxAccount(TCHAR * _id);


//AccountDetail생성
void createAccountDetail(int _accountNum, int _deposit,int _withraw);

//해당 계좌 인덱스에서 계좌번호에 맞다면 그 계좌 정보를 반환
AccountDetail matcingAccountDetail(int _accountNum,int _idx);