#pragma once
//Process����� ù��° ���
BOOL OnCreateProcess_1();
//Process����� �ι�° ���
BOOL OnCreateProcess_2();

//Process ���� ù��° ���
/*
@hDlg�� �����ų process handle
*/
BOOL OnExitProcess_1(HWND hDlg);

//Process ���� �ι�° ���
/*
@ hDlg�� �����ų process handle
@ hwnd�� �޼��� �ڽ� ����� ���� ������

*/
BOOL OnExitProcess_2(HANDLE hDlg,HWND hwnd);

//������ �ڵ�� process ID ��� ���
BOOL OnGetProcessIDInWidowHandle(HWND hwnd,LPDWORD lpdwProcessID);

//Process ID�� Window Handle ��� ���
/*
�� �Լ��� ����ϸ� ���� ī��Ʈ�� �����մϴ�.
*/
BOOL OnGetWindowHandleInProcessID(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessID);

//�ڽ� process�� �ڵ��� �����ϴ� ���
/*
@ hProcess2 ������ ���� �� �ڵ�
@ pi  ������ �ڽ� process�� ���� ����ü
@ b �θ� �ڽ��� ��� ���� �� ������ �Ǵ��ϴ� �Լ� TRUE�� ����, FALSE�� ���� ����
*/
BOOL OnCopyChildHandle(HANDLE hProcess2, PROCESS_INFORMATION pi,BOOL b);
