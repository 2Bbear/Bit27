#pragma once

//���»��������� ����ϴ� �Լ�
void ui_PopUpCreateAccountWindow(HWND hDlg);

//���°˻������� ����ϴ� �Լ�
void ui_PopUpSerchAccountWindow(HWND hDlg);

//�Է¹��� �Ű������� �ڵ��� ã�� �Լ�
void ui_GetHandle(HWND hDlg);

//ListControl�� colum�� �߰��ϴ� �Լ�
void ui_SetListViewColumnHeader(HWND hDlg);

//Account list��ü ����ϴ� �Լ�
void ui_processListPrint(vector<Account>* datalist, int size);
//Account list �� ���� ����ϴ� �Լ�
void ListPrint(Account acc, int _idx);
//==============================================================================
//AccountDetail list �Ѵ��� ����ϴ� �Լ�
void AccountDetailListPrint(AccountDetail accDetail,int _idx);
//AccountDetail list ��ü�� ����ϴ� �Լ�
void ui_processAccountDetailListPrint(vector<AccountDetail> * datalist,int size);
//==============================================================================

//������ ��Ʈ�ѵ鿡 �����͵� �߰��ϴ� �Լ�
void setEditControls( int _accountNum, TCHAR * _name, TCHAR * _balance);

//�Ա��ϴ� �Լ�