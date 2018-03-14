#pragma once

//계좌 검색 id값을 받아서 Account 주소 값 리턴
Account * B_FindAccount(TCHAR * _id);

//입금
//void B_Deposit(int _idx,);
//출금

//계좌 생성

//계좌 삭제

//현재 계좌 수

//계좌 내역 생성
void B_CreateAccountDetail(int _accountNum, int _depo,int _withraw,TCHAR * pBalance);

//계좌 내역 검색
