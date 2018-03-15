#pragma once

//��� Control�� �ʱ�ȭ
void ui_initControl(HWND hDlg);
//��� ���¸� ���
void ui_printAllAccount(HWND hDlg, vector<Account> * pAccountList);
//�ش� ������ ��� ���� ���� ���
void ui_printAccountDetailList(TCHAR * _id, vector<AccountDetail> * pAccountDetailList);
//������ ���� �� ���
void ui_printCurrentAccountCount(HWND hDlg);

//ã�� ������ ������ ���
void ui_printAccountInfo(int _accountNum,TCHAR * _name,int _balance);

//���� ���� edit �ʱ�ȭ
void ui_InitAccountInfoEdit(HWND hwnd);

//���� ���� list control �ʱ�ȭ
void ui_initAccountDetailListControl(HWND hwnd);

//=======================================================
//List Colum �ʱ�ȭ
void initListControlColum();
//Account ListControl ���
void AccountListControlPrint(Account acc, int _idx);
//AcountDetail ListControl ���
void AccountDetailListcontrolPrint(AccountDetail accDetail,int _idx);