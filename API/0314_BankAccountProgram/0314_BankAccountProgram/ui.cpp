#include"std.h"

extern vector<Account> g_AccountList;
extern vector<AccountDetail> g_AccountDetailList;

//���� ����Ʈ��Ʈ�� �ڵ�
HWND g_hListView;
//������ ����Ʈ��Ʈ�� �ڵ�
HWND g_hListView2;
//������ ���¹�ȣedit �ڵ�
HWND g_hEditAccountNum;
//������ �̸� edit �ڵ�
HWND g_hEditName;
//������ �ܾ� edit �ڵ�
HWND g_hEditBalance;

void ui_PopUpCreateAccountWindow(HWND hDlg)
{
	//��� ������ ����
	CAWH_CreateDialogWindow(&g_AccountList,hDlg);
	
	//���� ���� ����
	B_CreateAccountDetail(g_AccountList[g_AccountList.size() - 1].accountNum, 0, 0,TEXT("0��"));
	//����Ʈ�� ����ϱ�
	ui_processListPrint(&g_AccountList, g_AccountList.size());
}

void ui_PopUpSerchAccountWindow(HWND hDlg)
{
	TCHAR tempID[50];
	//��� ���� ������ ����
	SAWH_CreateDialogWindow(tempID,hDlg);
}

void ListPrint(Account acc,int _idx)
{
	LVITEM LI;

	LI.mask = LVIF_TEXT;


	//���¹�ȣ
	LI.iItem = _idx;// ��

	LI.iSubItem = 0;//��
	TCHAR buf[50];
	wsprintf(buf,TEXT("%d"),acc.accountNum);
	LI.pszText = buf;			// ù ��° ������
	SendMessage(g_hListView, LVM_INSERTITEM, 0, (LPARAM)&LI);
	//�̸�
	LI.iSubItem = 1;//��
	LI.pszText = acc.name;			// ù ��° ������
	SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);
	//�ܾ�
	LI.iSubItem = 2;//��
	LI.pszText = TEXT("0��");			// ù ��° ������
	SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);
	//���̵�
	LI.iSubItem = 3;//��
	LI.pszText = acc.id;			// ù ��° ������
	SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);
	//�н�����
	LI.iSubItem = 4;//��
	LI.pszText = acc.password;			// ù ��° ������
	SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);



	//LI.iItem = _idx;// ��

	//LI.iSubItem = 0;//��
	//LI.pszText = acc.name;			// ù ��° ������
	//SendMessage(g_hListView, LVM_INSERTITEM, 0, (LPARAM)&LI);

	//TCHAR buf[50];
	//wsprintf(buf, TEXT("%d"), acc.accountNum);

	//LI.iSubItem = 1;
	//LI.pszText = buf;
	//SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

	//===========================================================
}

void AccountDetailListPrint(AccountDetail accDetail, int _idx)
{
	LVITEM LI;

	LI.mask = LVIF_TEXT;


	//����
	LI.iItem = _idx;// ��

	LI.iSubItem = 0;//��
	//TCHAR buf[50];
	//wsprintf(buf, TEXT("%d"), accDetail.day);
	LI.pszText = accDetail.day;			// ù ��° ������
	SendMessage(g_hListView2, LVM_INSERTITEM, 0, (LPARAM)&LI);
	//�ð�
	LI.iSubItem = 1;//��
	LI.pszText = accDetail.time;			// ù ��° ������
	SendMessage(g_hListView2, LVM_SETITEM, 1, (LPARAM)&LI);
	//�Աݾ�
	LI.iSubItem = 2;//��
	TCHAR buf[50];
	wsprintf(buf, TEXT("%d"), accDetail.deposit);
	LI.pszText = buf;			// ù ��° ������
	SendMessage(g_hListView2, LVM_SETITEM, 2, (LPARAM)&LI);
	//��ݾ�
	LI.iSubItem = 3;//��
	TCHAR buf2[50];
	wsprintf(buf2, TEXT("%d"), accDetail.withdraw);
	LI.pszText = buf2;			// ù ��° ������
	SendMessage(g_hListView2, LVM_SETITEM, 3, (LPARAM)&LI);
	//�ܾ�
	LI.iSubItem = 4;//��
	LI.pszText = accDetail.balance;			// ù ��° ������
	SendMessage(g_hListView2, LVM_SETITEM, 4, (LPARAM)&LI);
}

void ui_processAccountDetailListPrint(vector<AccountDetail>* datalist, int size)
{
	//List �ʱ�ȭ
	ListView_DeleteAllItems(g_hListView2);
	//�ϳ��� list ������ ����
	//ListView_DeleteItem(hList,idx)
	//���� ����
	for (int i = 0; i<size; i++)
	{
		AccountDetail info = (*datalist)[i];
		//
		//======================================
		AccountDetailListPrint(info, i);
		//======================================
	}
}



void ui_GetHandle(HWND hDlg)
{
	g_hListView = GetDlgItem(hDlg, IDC_LIST1);
	g_hListView2 = GetDlgItem(hDlg, IDC_LIST2);

	g_hEditAccountNum=GetDlgItem(hDlg, IDC_EDIT1);

	g_hEditName = GetDlgItem(hDlg, IDC_EDIT2);
	
	g_hEditBalance = GetDlgItem(hDlg, IDC_EDIT3);
}

void ui_SetListViewColumnHeader(HWND hDlg)
{
	
	LVCOLUMN COL;
	// ����� �߰��Ѵ�.
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 75;
	COL.pszText = TEXT("���¹�ȣ");				// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.cx = 50;
	COL.pszText = TEXT("�̸�");			// �� ��° ���
	COL.iSubItem = 1;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.cx = 50;
	COL.pszText = TEXT("�ܾ�");			// 3 ���
	COL.iSubItem = 2;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.cx = 50;
	COL.pszText = TEXT("���̵�");			// 4 ���
	COL.iSubItem = 3;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

	COL.cx = 75;
	COL.pszText = TEXT("�н�����");			// 5 ���
	COL.iSubItem = 4;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);

	//============================================================
	//������ list control
	LVCOLUMN COL2;
	// ����� �߰��Ѵ�.
	COL2.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL2.fmt = LVCFMT_LEFT;
	COL2.cx = 100;
	COL2.pszText = TEXT("����");				// ù ��° ���
	COL2.iSubItem = 0;
	SendMessage(g_hListView2, LVM_INSERTCOLUMN, 0, (LPARAM)&COL2);

	COL2.cx = 120;
	COL2.pszText = TEXT("�ð�");			// �� ��° ���
	COL2.iSubItem = 1;
	SendMessage(g_hListView2, LVM_INSERTCOLUMN, 1, (LPARAM)&COL2);

	COL2.cx = 50;
	COL2.pszText = TEXT("�Աݾ�");			// 3 ���
	COL2.iSubItem = 2;
	SendMessage(g_hListView2, LVM_INSERTCOLUMN, 2, (LPARAM)&COL2);

	COL2.cx = 50;
	COL2.pszText = TEXT("��ݾ�");			// 4 ���
	COL2.iSubItem = 3;
	SendMessage(g_hListView2, LVM_INSERTCOLUMN, 3, (LPARAM)&COL2);

	COL2.cx = 75;
	COL2.pszText = TEXT("�ܾ�");			// 5 ���
	COL2.iSubItem = 4;
	SendMessage(g_hListView2, LVM_INSERTCOLUMN, 4, (LPARAM)&COL2);
}

void ui_processListPrint(vector<Account>* datalist, int size)
{
	//List �ʱ�ȭ
	ListView_DeleteAllItems(g_hListView);
	//�ϳ��� list ������ ����
	//ListView_DeleteItem(hList,idx)
	//���� ����
	for (int i = 0; i<size; i++)
	{
		Account info = (*datalist)[i];
		//
		//======================================
		ListPrint(info, i);
		//======================================
	}
}

void setEditControls(int _accountNum,TCHAR * _name,TCHAR * _balance)
{
	TCHAR buf[50];
	wsprintf(buf, TEXT("%d"), _accountNum);
	SetWindowText(g_hEditAccountNum, buf);

	SetWindowText(g_hEditName, _name);

	SetWindowText(g_hEditBalance, _balance);
}
