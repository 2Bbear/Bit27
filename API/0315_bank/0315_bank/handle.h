#pragma once
//���̾�α� �ʱ�ȭ �Լ�
BOOL OnInitDialog(HWND hDlg);

//���� ���� ������ ���� �Լ�
BOOL OnCreateAccountWindow(HWND hDlg, WPARAM wParam, LPARAM lParam);

//���� �˻� ������ ���� �Լ�
BOOL OnSearchAccountWindow(HWND hDlg, WPARAM wParam, LPARAM lParam);

//���� ���� ����� ó���ϴ� �Լ� wParam , lParam ���ʿ� id���� ������ ��� ���� ���� �� �� ���� TCHAR *��
BOOL OnAccountDetailPrint(HWND hDlg, WPARAM wParam, LPARAM lParam);

//���»�����ư
BOOL OnDeleteAccountButton(HWND hDlg);
//����� ��ư
BOOL OnBankStatement(HWND hDlg);
//���� ��ư
	//�Է�
BOOL OnDeposit();
	//���
BOOL OnWithdraw();