//handler.h
#pragma once;

//���� �ڽ��� ���� �Լ�
void InitCurrentAccount();
void SetCurrentAccountName(TCHAR * _name);
void SetCurrentAccountID(TCHAR * _id);
void SetCurrentAccountPW(TCHAR * _pw);
//
BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

void OnConnect(HWND hDlg);
//ȸ������
void OnAddMember(HWND hDlg);
//�α���
void OnLogin(HWND hDlg);
//�α׾ƿ�
void OnLogOut(HWND hDlg);
//�޼���������?
void OnSendData(HWND hDlg);
//ȸ��Ż��
void OnUnregister(HWND hDlg);

//wbnet->handler
void OnLogMessage(TCHAR *msg);
void OnMessage(char* buf, int nRead);