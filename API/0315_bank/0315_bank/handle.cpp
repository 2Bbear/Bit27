#include"std.h"
//��������
extern vector<Account> g_AccountList;
extern vector<AccountDetail> g_AccountDetailList;
HWND mainhwnd;

int bankStatement;//1�̸� ���, 2�� �Ա�
BOOL OnInitDialog(HWND hDlg)
{
	//ui �ʱ�ȭ
	ui_initControl(hDlg);
	//�� ���� �ڵ� ����
	mainhwnd = hDlg;
	return 0;
}

BOOL OnCreateAccountWindow(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//���� �������� �������� �ۼ��� ������ ������ ����ü
	Account temp;
	
	//��� ����
	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_DIALOG2),
		hDlg,		// �θ�
		SW_CreateAccountProc, // �޼��� �Լ�.
		(LPARAM)&temp); // WM_INITDIALOG�� lParam�� ���޵ȴ�. //�� �Լ��� ���� ������ ���� ������� �ƹ��͵� ���Ѵ�

	if (ret==IDOK)
	{
		//��������
		createAccount(temp);
		//���³��� ����
		createAccountDetail(temp.accountNum, 0, 0,0);
		//�� ���� ���
		ui_printAllAccount(hDlg, &g_AccountList);
		//�������� �� ���
		ui_printCurrentAccountCount(hDlg);
	}
	else if (ret == IDCANCEL)
	{

	}
	else
	{
		MessageBox(hDlg, TEXT("�������"), TEXT(""), MB_OK);
	}
	return 0;
}

BOOL OnSearchAccountWindow(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//�� �ڵ� ��ü�� ���ο� â�� ���� ��
	UINT ret = DialogBox(GetModuleHandle(0),// instance 
		MAKEINTRESOURCE(IDD_DIALOG3), // ���̾�α� ���� 
		0,   // �θ� ������ 
		SW_SearchAccountProc);   // Proc..
	return 0;
}

BOOL OnAccountDetailPrint(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//���� ���� ����Ʈ ���
	ui_printAccountDetailList((TCHAR * )wParam, &g_AccountDetailList);
	//���� ���� ���
	Account temp = g_AccountList[findeIdxAccount((TCHAR *)wParam)];

	ui_printAccountInfo(temp.accountNum,temp.name,temp.balance);
	return 0;
}

BOOL OnDeleteAccountButton(HWND hDlg)
{

	//edit���� ���� ��ȣ �о� ����
	TCHAR buf[50];
	GetDlgItemText(hDlg, IDC_EDIT1, buf, _tcslen(buf));
	//���� ��ȣ�� �ش� ���� �ε��� ã��
	
	int tempAccountNum= _wtoi(buf);
	Account * temp = findAccount(-1, tempAccountNum);
	//�ش� ���� ����
	deleteAccount(findeIdxAccount(temp->id));
	//���� ����Ʈ �� ���
	ui_printAllAccount(hDlg, &g_AccountList);
	//���� ���� edit �ʱ�ȭ
	ui_InitAccountInfoEdit(hDlg);
	//���� ���� ����Ʈ �ʱ�ȭ
	ui_initAccountDetailListControl(hDlg);
	return 0;
}

BOOL OnBankStatement(HWND hDlg)
{
	//���¹�ȣ �о����
	//���� ��ȣ edit���� ���� ��ȣ �о� ����
	TCHAR buf[50];
	GetDlgItemText(hDlg, IDC_EDIT1, buf, _tcslen(buf));
	int tempAccountNum = _wtoi(buf);
	//�Աݾ� edit���� �ݾ� ��������
	TCHAR buf2[50];
	GetDlgItemText(hDlg, IDC_EDIT4, buf2, _tcslen(buf2));
	int userMoney = _wtoi(buf2);

	//���
	if (bankStatement == 1)
	{
		//����ϱ�
		withdrawAccount(userMoney, tempAccountNum);
	}
	//�Ա�
	else if (bankStatement == 2)
	{
		depositAccount(userMoney, tempAccountNum);
	}
	//�׿�. �̻��� ���� �������� ��
	else
	{

	}

	//���� list control �ʱ�ȭ
	ui_printAllAccount(hDlg, &g_AccountList);
	//���� ����, ���� ���� ����Ʈ �ʱ�ȭ
	OnAccountDetailPrint(hDlg,(WPARAM)(findAccount(-1, tempAccountNum)->id),0);
	return 0;
}

BOOL OnDeposit()
{
	bankStatement = 2;
	return 0;
}

BOOL OnWithdraw()
{
	bankStatement = 1;
	return 0;
}
