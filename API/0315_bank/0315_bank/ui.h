#pragma once

//모든 Control을 초기화
void ui_initControl(HWND hDlg);
//모든 계좌를 출력
void ui_printAllAccount(HWND hDlg, vector<Account> * pAccountList);
//해당 계좌의 모든 계좌 내역 출력
void ui_printAccountDetailList(TCHAR * _id, vector<AccountDetail> * pAccountDetailList);
//생성된 계좌 수 출력
void ui_printCurrentAccountCount(HWND hDlg);

//찾은 계좌의 정보를 출력
void ui_printAccountInfo(int _accountNum,TCHAR * _name,int _balance);

//계좌 정보 edit 초기화
void ui_InitAccountInfoEdit(HWND hwnd);

//계좌 내역 list control 초기화
void ui_initAccountDetailListControl(HWND hwnd);

//=======================================================
//List Colum 초기화
void initListControlColum();
//Account ListControl 출력
void AccountListControlPrint(Account acc, int _idx);
//AcountDetail ListControl 출력
void AccountDetailListcontrolPrint(AccountDetail accDetail,int _idx);