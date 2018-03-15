#include"std.h"
#include<Commctrl.h>
extern HWND mainhwnd;

//���� Control Handle ����
HWND g_hAccountListControl;
HWND g_hAccountDetailListControl;
HWND g_hAccountNameEditControl;
HWND g_hAccountNumEditControl;
HWND g_hAccountBalanceEditControl; 
HWND g_hCurrentAccountCountStaticText;
//=======================================

void ui_initControl(HWND hDlg)
{
	//Control Handle Setting
	g_hAccountListControl = GetDlgItem(hDlg, IDC_LIST1);
	g_hAccountDetailListControl = GetDlgItem(hDlg, IDC_LIST2);
	g_hAccountNameEditControl = GetDlgItem(hDlg, IDC_EDIT2);
	g_hAccountNumEditControl = GetDlgItem(hDlg, IDC_EDIT1);
	g_hAccountBalanceEditControl = GetDlgItem(hDlg, IDC_EDIT3);
	g_hCurrentAccountCountStaticText= GetDlgItem(hDlg, IDC_STATIC_AC_COUNT);
	//List Colum Setting
	initListControlColum();
	//Print AccountCount 
	ui_printCurrentAccountCount(hDlg);

}

void ui_printAllAccount(HWND hDlg, vector<Account>* pAccountList)
{
	//List �ʱ�ȭ
	ListView_DeleteAllItems(g_hAccountListControl);
	//�ϳ��� list ������ ����
	//ListView_DeleteItem(hList,idx)
	//���� ����
	for (int i = 0; i<(int)pAccountList->size(); i++)
	{
		Account info = (*pAccountList)[i];
		//
		//======================================
		AccountListControlPrint(info, i);
		//======================================
	}
}

void ui_printAccountDetailList(TCHAR * _id, vector<AccountDetail> * pAccountDetailList)
{
	//List �ʱ�ȭ
	ListView_DeleteAllItems(g_hAccountDetailListControl);
	//�ϳ��� list ������ ����
	//ListView_DeleteItem(hList,idx)
	//���� ����
	int listlicount = 0;
	
	for (int i = 0; i<(int)pAccountDetailList->size(); i++)
	{
		//accountDetail���� �ϳ��� ��Ҹ� �����ϴ� �κ�
		AccountDetail info = (*pAccountDetailList)[i];
		//������ ��Ұ� _id�� �´��� �˻�
		Account * accinfo = findAccount(-1, info.accountNum);
		//
		//�˻�
		
		if (_tcscmp(accinfo->id, _id)==0)
		{
			//======================================
			AccountDetailListcontrolPrint(info, listlicount);
			//======================================
			listlicount++;
		}
		
	}

}

void ui_printCurrentAccountCount(HWND hDlg)
{
	TCHAR buf[50];
	wsprintf(buf,TEXT("���� ���� �� : %d��"),getCurrentAccountCount());
	SetWindowText(g_hCurrentAccountCountStaticText, buf);
}

void ui_printAccountInfo(int _accountNum, TCHAR * _name, int _balance)
{
	//���¹�ȣ
	TCHAR buf[50];
	wsprintf(buf, TEXT("%d"), _accountNum);
	SetWindowText(g_hAccountNumEditControl, buf);
	//�̸�
	SetWindowText(g_hAccountNameEditControl, _name);

	//�ܾ�
	TCHAR buf2[50];
	wsprintf(buf2, TEXT("%d"), _balance);
	SetWindowText(g_hAccountBalanceEditControl, buf2);
}

void ui_InitAccountInfoEdit(HWND hwnd)
{
	//���� editcontrol
	SetWindowText(g_hAccountNumEditControl, TEXT(""));
	//�̸� editcontrol
	SetWindowText(g_hAccountNameEditControl, TEXT(""));
	//�ܾ� editcontrol
	SetWindowText(g_hAccountBalanceEditControl, TEXT(""));
}

void ui_initAccountDetailListControl(HWND hwnd)
{
	for (int _idx=0;_idx<100;_idx++)
	{
		LVITEM LI;

		LI.mask = LVIF_TEXT;


		//����
		LI.iItem = _idx;// ��

		LI.iSubItem = 0;//��
						//TCHAR buf[50];
						//wsprintf(buf, TEXT("%d"), accDetail.day);
		LI.pszText = TEXT("");		// ù ��° ������
		SendMessage(g_hAccountDetailListControl, LVM_INSERTITEM, 0, (LPARAM)&LI);
		//�ð�
		LI.iSubItem = 1;//��
		LI.pszText = TEXT("");			// ù ��° ������
		SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 1, (LPARAM)&LI);
		//�Աݾ�
		LI.iSubItem = 2;//��
		LI.pszText = TEXT("");			// ù ��° ������
		SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 2, (LPARAM)&LI);
		//��ݾ�
		LI.iSubItem = 3;//��
		LI.pszText = TEXT("");		// ù ��° ������
		SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 3, (LPARAM)&LI);
		//�ܾ�
		LI.iSubItem = 4;//��
		LI.pszText = TEXT("");	// ù ��° ������
		SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 4, (LPARAM)&LI);
	}
}



void initListControlColum()
{
	LVCOLUMN COL;
	// Account ListControl setting
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 75;
	COL.pszText = TEXT("���¹�ȣ");				// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(g_hAccountListControl, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.cx = 50;
	COL.pszText = TEXT("�̸�");			// �� ��° ���
	COL.iSubItem = 1;
	SendMessage(g_hAccountListControl, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.cx = 50;
	COL.pszText = TEXT("�ܾ�");			// 3 ���
	COL.iSubItem = 2;
	SendMessage(g_hAccountListControl, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.cx = 50;
	COL.pszText = TEXT("���̵�");			// 4 ���
	COL.iSubItem = 3;
	SendMessage(g_hAccountListControl, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

	COL.cx = 130;
	COL.pszText = TEXT("�н�����");			// 5 ���
	COL.iSubItem = 4;
	SendMessage(g_hAccountListControl, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);

	//============================================================
	//AccountDetail ListControl Setting
	LVCOLUMN COL2;
	// ����� �߰��Ѵ�.
	COL2.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL2.fmt = LVCFMT_LEFT;
	COL2.cx = 100;
	COL2.pszText = TEXT("����");				// ù ��° ���
	COL2.iSubItem = 0;
	SendMessage(g_hAccountDetailListControl, LVM_INSERTCOLUMN, 0, (LPARAM)&COL2);

	COL2.cx = 120;
	COL2.pszText = TEXT("�ð�");			// �� ��° ���
	COL2.iSubItem = 1;
	SendMessage(g_hAccountDetailListControl, LVM_INSERTCOLUMN, 1, (LPARAM)&COL2);

	COL2.cx = 50;
	COL2.pszText = TEXT("�Աݾ�");			// 3 ���
	COL2.iSubItem = 2;
	SendMessage(g_hAccountDetailListControl, LVM_INSERTCOLUMN, 2, (LPARAM)&COL2);

	COL2.cx = 50;
	COL2.pszText = TEXT("��ݾ�");			// 4 ���
	COL2.iSubItem = 3;
	SendMessage(g_hAccountDetailListControl, LVM_INSERTCOLUMN, 3, (LPARAM)&COL2);

	COL2.cx = 95;
	COL2.pszText = TEXT("�ܾ�");			// 5 ���
	COL2.iSubItem = 4;
	SendMessage(g_hAccountDetailListControl, LVM_INSERTCOLUMN, 4, (LPARAM)&COL2);
}

void AccountListControlPrint(Account acc, int _idx)
{
	LVITEM LI;

	LI.mask = LVIF_TEXT;


	//���¹�ȣ
	LI.iItem = _idx;// ��

	LI.iSubItem = 0;//��
	TCHAR buf[50];
	wsprintf(buf, TEXT("%d"), acc.accountNum);
	LI.pszText = buf;			// ù ��° ������
	SendMessage(g_hAccountListControl, LVM_INSERTITEM, 0, (LPARAM)&LI);
	//�̸�
	LI.iSubItem = 1;//��
	LI.pszText = acc.name;			// ù ��° ������
	SendMessage(g_hAccountListControl, LVM_SETITEM, 1, (LPARAM)&LI);
	//�ܾ�
	LI.iSubItem = 2;//��
	TCHAR buf2[50];
	wsprintf(buf2, TEXT("%d"), acc.balance);
	LI.pszText = buf2;			// ù ��° ������
	SendMessage(g_hAccountListControl, LVM_SETITEM, 2, (LPARAM)&LI);
	//���̵�
	LI.iSubItem = 3;//��
	LI.pszText = acc.id;			// ù ��° ������
	SendMessage(g_hAccountListControl, LVM_SETITEM, 3, (LPARAM)&LI);
	//�н�����
	LI.iSubItem = 4;//��
	LI.pszText = acc.password;			// ù ��° ������
	SendMessage(g_hAccountListControl, LVM_SETITEM, 4, (LPARAM)&LI);
}

void AccountDetailListcontrolPrint(AccountDetail accDetail, int _idx)
{
	LVITEM LI;

	LI.mask = LVIF_TEXT;


	//����
	LI.iItem = _idx;// ��

	LI.iSubItem = 0;//��
					//TCHAR buf[50];
					//wsprintf(buf, TEXT("%d"), accDetail.day);
	LI.pszText = accDetail.day;			// ù ��° ������
	SendMessage(g_hAccountDetailListControl, LVM_INSERTITEM, 0, (LPARAM)&LI);
	//�ð�
	LI.iSubItem = 1;//��
	LI.pszText = accDetail.time;			// ù ��° ������
	SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 1, (LPARAM)&LI);
	//�Աݾ�
	LI.iSubItem = 2;//��
	TCHAR buf[50];
	wsprintf(buf, TEXT("%d"), accDetail.deposit);
	LI.pszText = buf;			// ù ��° ������
	SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 2, (LPARAM)&LI);
	//��ݾ�
	LI.iSubItem = 3;//��
	TCHAR buf2[50];
	wsprintf(buf2, TEXT("%d"), accDetail.withraw);
	LI.pszText = buf2;			// ù ��° ������
	SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 3, (LPARAM)&LI);
	//�ܾ�
	LI.iSubItem = 4;//��
	TCHAR buf3[50];
	wsprintf(buf3, TEXT("%d"), accDetail.balance);
	LI.pszText = buf3;		// ù ��° ������
	SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 4, (LPARAM)&LI);
}

