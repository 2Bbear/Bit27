#pragma once


//ui �ʱ�ȭ �ϴ� �Լ�
void ui_InitControl(HWND hDlg);

//���Ӱ��� �����ϴ� �Լ�
void ui_SetCurrentConnectCountStatic(int n);

//port ��ȣ dlg���� �о���� �Լ�
int ui_getPort(HWND hDlg);

//�޼��� â�� �޼����� ����ϴ� �Լ�
void ui_LogMessage(TCHAR * _msg);