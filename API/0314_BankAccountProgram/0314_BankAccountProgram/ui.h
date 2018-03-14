#pragma once

//계좌생성윈도우 출력하는 함수
void ui_PopUpCreateAccountWindow(HWND hDlg);

//계좌검색윈도우 출력하는 함수
void ui_PopUpSerchAccountWindow(HWND hDlg);

//입력받은 매개변수의 핸들을 찾는 함수
void ui_GetHandle(HWND hDlg);

//ListControl의 colum을 추가하는 함수
void ui_SetListViewColumnHeader(HWND hDlg);

//Account list전체 출력하는 함수
void ui_processListPrint(vector<Account>* datalist, int size);
//Account list 한 단을 출력하는 함수
void ListPrint(Account acc, int _idx);
//==============================================================================
//AccountDetail list 한단을 출력하는 함수
void AccountDetailListPrint(AccountDetail accDetail,int _idx);
//AccountDetail list 전체를 출력하는 함수
void ui_processAccountDetailListPrint(vector<AccountDetail> * datalist,int size);
//==============================================================================

//오른쪽 컨트롤들에 데이터들 추가하는 함수
void setEditControls( int _accountNum, TCHAR * _name, TCHAR * _balance);

//입금하는 함수