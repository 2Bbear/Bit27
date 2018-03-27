#include"std.h"
extern int g_memberGender; // 1�� ���� , 2�� ����

//HWND g_hListView;
//
//void ui_GetHandle(HWND hDlg)
//{
//	g_hListView = GetDlgItem(hDlg, IDC_LIST1);
//}
//
//void ui_SetListViewColumnHeader(HWND hDlg)
//{
//	LVCOLUMN COL;
//	// ����� �߰��Ѵ�.
//	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
//	COL.fmt = LVCFMT_LEFT;
//	COL.cx = 150;
//	COL.pszText = TEXT("�̸�");				// ù ��° ���
//	COL.iSubItem = 0;
//	SendMessage(g_hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);
//
//	COL.pszText = TEXT("PID");			// �� ��° ���
//	COL.iSubItem = 1;
//	SendMessage(g_hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);
//
//}
//
//
//
//
HWND ListTeamView;
HWND ListMemberView;
HWND hComBox;
void ListTeamPrint(TEAM _info, int _idx)
{
	LVITEM LI;

	LI.mask = LVIF_TEXT;


	LI.iItem = _idx;// ��

	LI.iSubItem = 0;//��

	TCHAR buf[20];
	wsprintf(buf, TEXT("%d"), _info.tema_id);

	LI.pszText = buf;			// ù ��° ������
	SendMessage(ListTeamView, LVM_INSERTITEM, 0, (LPARAM)&LI);

	LI.iSubItem = 1;
	LI.pszText = _info.team_name;
	SendMessage(ListTeamView, LVM_SETITEM, 0, (LPARAM)&LI);

	//===========================================================
	
}
void ui_TeamListPrint(vector<TEAM>* datalist, int size)
{
	printf("ui listcontrol�� ���\n");
	//List �ʱ�ȭ
	ListView_DeleteAllItems(ListTeamView);
	//�ϳ��� list ������ ����
	//ListView_DeleteItem(hList,idx)
	//���� ����
	for (int i =0;i<size;i++)
	{
		TEAM info = (*datalist)[i];
		//
		//======================================
		ListTeamPrint(info, i);
		//======================================
	}
}

void ListMemberPrint(MEMBER _info, int _idx)
{
	LVITEM LI;

	LI.mask = LVIF_TEXT;


	LI.iItem = _idx;// ��

	LI.iSubItem = 0;//��

	TCHAR buf[20];
	wsprintf(buf, TEXT("%d"), _info.member_id);
	

	LI.pszText = buf;				// ù ��° ������ ������̵�
	SendMessage(ListMemberView, LVM_INSERTITEM, 0, (LPARAM)&LI);

	LI.iSubItem = 1;
	LI.pszText = _info.member_name;				//�ι�° ������ �̸�
	SendMessage(ListMemberView, LVM_SETITEM, 0, (LPARAM)&LI);

	LI.iSubItem = 2;
	LI.pszText = _info.member_gender;			//����° ������ ����
	SendMessage(ListMemberView, LVM_SETITEM, 0, (LPARAM)&LI);

	LI.iSubItem = 3;
	LI.pszText = _info.member_phone;			//�׹�° ������ ��ȭ��ȣ
	SendMessage(ListMemberView, LVM_SETITEM, 0, (LPARAM)&LI);

	TCHAR buf2[20];
	wsprintf(buf2, TEXT("%d"), _info.tema_id);

	LI.iSubItem = 4;
	LI.pszText = buf2;					//�ټ���° ������ �� ���̵�
	SendMessage(ListMemberView, LVM_SETITEM, 0, (LPARAM)&LI);

	LI.iSubItem = 5;
	LI.pszText = _info.member_regiday;			//������° ������ ��ϳ�¥
	SendMessage(ListMemberView, LVM_SETITEM, 0, (LPARAM)&LI);

	LI.iSubItem = 6;
	LI.pszText = _info.team_name;			//�ϰ� ��° ������ ���̸�
	SendMessage(ListMemberView, LVM_SETITEM, 0, (LPARAM)&LI);

	//===========================================================
}
void ui_MemberListPrint(vector<MEMBER>* datalist,int size)
{
	printf("ui_MemberListPrint�� ���\n");
	ListView_DeleteAllItems(ListMemberView);
	//�ϳ��� list ������ ����
	//ListView_DeleteItem(hList,idx)
	//���� ����
	for (int i = 0; i<size; i++)
	{
		MEMBER info = (*datalist)[i];
		//
		//======================================
		ListMemberPrint(info, i);
		//======================================
	}
}

void ui_InitComboBox(HWND hDlg)
{
	hComBox = GetDlgItem(hDlg, IDC_COMBO1);

	TCHAR *item[] = { TEXT("MemID"),TEXT("TeamID"),TEXT("MemName"),TEXT("MemGender") };

	for (int i=0;i<4;i++)
	{
		SendMessage(hComBox, CB_ADDSTRING, 0, (LPARAM)item[i]);
	}
	
}

void ui_GetComboBoxText(HWND hDlg,TCHAR * _target)
{
	TCHAR temp[20];
	GetDlgItemText(hDlg, IDC_COMBO1, temp, sizeof(temp));
	_tcscpy(_target, temp);
}

void ui_GetSelectEditBoxText(HWND hDlg, TCHAR * _id)
{
	TCHAR temp[20];
	GetDlgItemText(hDlg, IDC_EDIT9, temp, sizeof(temp));
	_tcscpy(_id, temp);
}

void ui_GetTeamCreateInfo(HWND hDlg,int * team_id, TCHAR * team_name)
{
	*team_id=GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
	GetDlgItemText(hDlg, IDC_EDIT2, team_name, _tcsclen(team_name));

}

void ui_GetMemberCreateInfo(HWND hDlg, int * member_id, TCHAR * member_name, TCHAR * member_gender, TCHAR * member_phone,int * team_id)
{
	
	//��� �̸�
	GetDlgItemText(hDlg, IDC_EDIT5, member_name, _tcsclen(member_name));
	//��� ����
	if (g_memberGender==1)
	{
		_tcscpy(member_gender,TEXT("����"));
	}
	else if (g_memberGender==2)
	{
		_tcscpy(member_gender, TEXT("����"));
	}
	//��� ��ȭ��ȣ
	GetDlgItemText(hDlg, IDC_EDIT6, member_phone, _tcsclen(member_phone));
	//�� id
	*team_id=GetDlgItemInt(hDlg, IDC_EDIT7,0,0);
}

void ui_InitMemberListView(HWND hDlg)
{
	ListMemberView = GetDlgItem(hDlg, IDC_LIST2);
	
	LVCOLUMN COL;
	//����� �߰��Ѵ�.
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 70;
	COL.pszText = TEXT("��� ID");				// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(ListMemberView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = TEXT("�̸�");			// �� ��° ���
	COL.iSubItem = 1;
	SendMessage(ListMemberView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.pszText = TEXT("����");			// �� ��° ���
	COL.iSubItem = 2;
	SendMessage(ListMemberView, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.pszText = TEXT("��ȭ��ȣ");			// �� ��° ���
	COL.iSubItem = 3;
	SendMessage(ListMemberView, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

	COL.pszText = TEXT("�� ID");			// �ټ� ��° ���
	COL.iSubItem = 4;
	SendMessage(ListMemberView, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);

	COL.pszText = TEXT("��ϳ�¥");			// ���� ��° ���
	COL.iSubItem = 5;
	SendMessage(ListMemberView, LVM_INSERTCOLUMN, 5, (LPARAM)&COL);

	COL.pszText = TEXT("�� ��");			// �ϰ� ��° ���
	COL.iSubItem = 6;
	SendMessage(ListMemberView, LVM_INSERTCOLUMN, 6, (LPARAM)&COL);
}

void ui_InitTeamListView(HWND hDlg)
{
	ListTeamView = GetDlgItem(hDlg, IDC_LIST1);

	LVCOLUMN COL;

	//����� �߰��Ѵ�.
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 150;
	COL.pszText = TEXT("�� ID");				// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(ListTeamView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = TEXT("�� �̸�");			// �� ��° ���
	COL.iSubItem = 1;
	SendMessage(ListTeamView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);
}
