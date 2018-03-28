#include"std.h"

int g_memberGender = 0; // 1�� ���� , 2�� ����
int g_selectQuestAnswer = 0;
int g_currentQuestIndex = 0;
int g_currentLoginMember;
BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	
	ui_InitTeamListView(hDlg);
	ui_InitMemberListView(hDlg);
	ui_InitComboBox(hDlg);
	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//��ư �Է��� �޴� event�� ó���ϱ� ���� ����
	switch (LOWORD(wParam))
	{
	//���� ���
	/*case IDC_BUTTON1:
	{
		OnPrint(hDlg);
		return 0;
	}*/
	//dig �ʱ�ȭ
	//������ư �� ����
	case IDC_RADIO3://1��
	{
		g_selectQuestAnswer = 1;
		return 0;
	}
	case IDC_RADIO5://2��
	{
		g_selectQuestAnswer =2;
		return 0;
	}
	case IDC_RADIO4://3��
	{
		g_selectQuestAnswer = 3;
		return 0;
	}
	case IDC_RADIO6://4��
	{
		g_selectQuestAnswer = 4;
		return 0;
	}
	//������ư ����
	case IDC_RADIO1:
	{
		g_memberGender = 1;
		return 0;
	}
	//������ư ����
	case IDC_RADIO2:
	{
		
		g_memberGender = 2;
		return 0;
	}
	//DB ����
	case IDC_BUTTON_CONNECT:
	{
		OnDBConnect(hDlg);
		return 0;
	}
	//DB ��������
	case IDC_BUTTON_DISCONNECT:
	{
		OnDBDConnect(hDlg);
		return 0;
	}
	//�� ���̺� ����
	case IDC_BUTTON2 :
	{
		OnCreateTeamTable(hDlg);
		return 0;
	}
	//�� ���̺� ����
	case IDC_BUTTON3:
	{
		OnDropTeamTable(hDlg);
		return 0;
	}
	//��� ���̺� ����
	case IDC_BUTTON4:
	{
		OnCreateMemberTable(hDlg);
		return 0;
	}
	//��� ���̺� ����
	case IDC_BUTTON5:
	{
		OnDropMemberTable(hDlg);
		return 0;
	}
	//������ ����
	case IDC_BUTTON6:
	{
		OnCreateSequence(hDlg);
		return 0;
	}
	//������ ����
	case IDC_BUTTON7:
	{
		OnDropSequence(hDlg);
		return 0;
	}
	//Team��� ��ư
	case IDC_BUTTON8:
	{
		OnInsertTeam(hDlg);
		return 0; 
	}
	//Member��� ��ư
	case IDC_BUTTON12:
	{
		OnInsertMember(hDlg);
		return 0;
	}

	//Update ��ư
	case IDC_BUTTON10:
	{
		OnUpdateList(hDlg);
		return 0;
	}
	//Select ��ư
	case IDC_BUTTON13:
	{
		OnSelect(hDlg);
		return 0;
	}
	//Delete ��ư
	case IDC_BUTTON11:
	{
		OnDelete(hDlg);
		return 0;
	}
	//����Ǯ�� ����
	case IDC_BUTTON_STARTQUEST:
	{
		OnStartQuest(hDlg);
		return 0;
	}
	//������ ��ư
	case IDC_BUTTON_ANSWER:
	{
		OnSendAnswer(hDlg);
		return 0;
	}
	//��ü�������� ��ư
	case IDC_BUTTON16:
	{
		OnAllScorePrint(hDlg);
		return 0;
	}
	// ��� ���� �˻�
	case IDC_BUTTON17:
	{
		OnSearchMemberQuests(hDlg);
		return 0;
	}
	case IDCANCEL:
	{
		OnCancel(hDlg);
		return 0;
	}

	}
	return TRUE;
}

BOOL OnPrint(HWND hDlg)
{
	//����Ʈ �ʱ�ȭ

	GetProcessList(hDlg);
	return 0;
}

void OnUpdateList(HWND hDlg)
{
	printf("OnUpdateList \n");
	vector<TEAM> teamlist;
	wbdb_GetTeamSelectAll(&teamlist);
	ui_TeamListPrint(&teamlist, (int)teamlist.size());

	printf("�� ����Ʈ ������Ʈ �Ϸ� \n");

	vector<MEMBER> memberlist;
	wbdb_GetMemberSelectAll(&memberlist);
	ui_MemberListPrint(&memberlist, (int)memberlist.size());

	printf("��� ����Ʈ ������Ʈ �Ϸ� \n");
}

void OnSelect(HWND hDlg)
{
	TCHAR select[20];
	ui_GetComboBoxText(hDlg,select);

	//select edit �ڽ��� ���̵� �� ����
	TCHAR id[20];
	ui_GetSelectEditBoxText(hDlg, id);
	//������ ���̵� ������ �ش� ��� �˻�
	vector<MEMBER> memberlist;
	if (_tcscmp(select, TEXT("")) == 0)
	{
		return;
	}
	if (_tcscmp(select,TEXT("MemID"))==0)
	{
		printf("��� ID ����\n");
		wbdb_GetMemberSelectMODE(&memberlist, id,1);
	}
	else if (_tcscmp(select, TEXT("TeamID")) == 0)
	{
		printf("�� ID ����\n");
		wbdb_GetMemberSelectMODE(&memberlist, id, 2);
	}
	else if (_tcscmp(select, TEXT("MemName")) == 0)
	{
		printf("����̸� ����\n");
		wbdb_GetMemberSelectMODE(&memberlist, id, 3);
	}
	else if (_tcscmp(select, TEXT("MemGender")) == 0)
	{
		printf("������� ����\n");
		wbdb_GetMemberSelectMODE(&memberlist, id, 4);
	}
	//�ش� ����� ���� Member list�� ���
	ui_MemberListPrint(&memberlist, (int)memberlist.size());

}

void OnCancel(HWND hDlg)
{
	EndDialog(hDlg, IDCANCEL);
}

void OnDelete(HWND hDlg)
{
	//� �޺��ڽ��� ���µǾ����� ����
	TCHAR select[20];
	ui_GetComboBoxText(hDlg, select);

	//select edit �ڽ��� ���̵� �� ����
	TCHAR id[20];
	ui_GetSelectEditBoxText(hDlg, id);

	if (_tcscmp(select, TEXT("")) == 0)
	{
		return;
	}

	if (_tcscmp(select, TEXT("MemID")) == 0)
	{
		printf("��� ID ����\n");
		wbdb_DeleteMemberID(id);
	}
	else if (_tcscmp(select, TEXT("TeamID")) == 0)
	{
		printf("�� ID ����\n");
		wbdb_DeleteTeamID(id);
		
	}
	else if (_tcscmp(select, TEXT("MemName")) == 0)
	{
		printf("����̸� ����\n");
		
	}
	else if (_tcscmp(select, TEXT("MemGender")) == 0)
	{
		printf("������� ����\n");
		
	}

}

vector<QUEST> questlist;
void OnStartQuest(HWND hDlg)
{
	questlist.clear();
	printf("���� Ǯ�� ���� ��ư \n");
	//���� ����Ǯ�� �ִ� ������ Ȯ��
	if (true)
	{
		//��� ���̵� �޾ƿ���
		ui_getMemberId(hDlg,&g_currentLoginMember);
		//db���� ������ �� �޾ƿ���
		if (wbdb_GetQuests(&questlist))
		{
			//���� ���
			printf("��������ϱ� \n");
			ui_PrintQuest(hDlg,&questlist);
			g_currentQuestIndex++;
		}
	}
}

void OnSendAnswer(HWND hDlg)
{
	printf("������ ��ư \n");
	//���� ù��° ������ Ǯ�� �ִ���?
	if (g_currentQuestIndex>0)
	{
		//examresult�� insert�ϱ�
		wbdb_InsertExamResult(questlist[g_currentQuestIndex-1].quest_id, g_currentLoginMember, g_selectQuestAnswer, questlist[g_currentQuestIndex - 1].quest_answer);
		//���� ���� ����ϱ�
		printf("���� ���� ��� \n");
		ui_PrintQuest(hDlg, &questlist);
		g_currentQuestIndex++;
		//������ ������ �����Ұ��
		if ((int)questlist.size()<= g_currentQuestIndex)
		{
			g_currentQuestIndex = 0;
			//commit ���� ����
			wbdb_SendCommit();
			SetDlgItemText(hDlg, IDC_EDIT_QUEST, TEXT("���蹮�� Ǫ���� ����ϼ̽��ϴ�.\n"));
		}
	}

}

void OnAllScorePrint(HWND hDlg)
{
	//���� �Ʒ� ����Ʈ ��Ʈ�� �ʱ�ȭ
	ui_InitScoreListView(hDlg, 1);
	vector<MEMBERSCORE> memberScoreList;
	//DB���� MEMBERSCORE �ޱ�
	if (wbdb_GetAllMemberScore(&memberScoreList)==TRUE)
	{
		//���
		ui_MemberScoreListPrint(&memberScoreList, (int)memberScoreList.size());
	}
	else
	{
		printf("��ü���� ���� ���� \n");
	}
}

void OnSearchMemberQuests(HWND hDlg)
{
	//���� �Ʒ� ����Ʈ ��Ʈ�� �ʱ�ȭ
	ui_InitScoreListView(hDlg, 2);
	//edit���� �˻��� ��� id �����ϱ�
	TCHAR targetName[20];
	GetDlgItemText(hDlg, IDC_EDIT44, targetName, sizeof(targetName));

	//DB���� TESTPAPERlist �� �޾ƿ���
	vector<TESTPAPER> testPaperList;
	if (wbdb_GetTestPaperList(&testPaperList, targetName)==TRUE)
	{
		//���
		ui_MemberQuestListPrint(&testPaperList, (int)testPaperList.size());
	}
	else
	{

	}
}


void GetProcessList(HWND hDlg)
{
	
//	vector<PROINFO> datalist;
	//int size;
//	pro_getProcessList(&datalist, &size);
	//����Ʈ ����
	//coll_proListSave(&datalist, size);

	//ȭ�鿡 ���
//	ui_processListPrint(&datalist, size);
}

void OnDBConnect(HWND hdlg)
{

	if (wbdb_DBConnect()==TRUE)
	{
		ui_printTestMemberCountAndAVG(hdlg);
		printf("OnDBConnect ����\n");
	}
	else
	{
		printf("OnDBConnect ����\n");
	}
}

void OnDBDConnect(HWND hdlg)
{
	if (wbdb_DBConnect() == TRUE)
	{
		printf("db�������� ����\n");
		//MessageBox(NULL, TEXT("db�������� ����"), TEXT("�˸�"), MB_OK);
	}
	else
	{
		printf("db�������� ����\n");
		MessageBox(NULL, TEXT("db�������� ����"), TEXT("�˸�"), MB_OK);
	}
}

void OnCreateTeamTable(HWND hdlg)
{
	if (wbdb_CreateTeamTable()==TRUE)
	{
		printf("OnCreateTeamTable ����\n");
		//MessageBox(NULL, TEXT("����"), TEXT("�˸�"), MB_OK);
	}
	else
	{
		printf("OnCreateTeamTable ����\n");
		//MessageBox(NULL, TEXT("����"), TEXT("�˸�"), MB_OK);
	}
}

void OnDropTeamTable(HWND hdlg)
{
	if (wbdb_DropTeamTable() == TRUE)
	{
		printf("OnDropTeamTable ���� \n");
		//MessageBox(NULL, TEXT("����"), TEXT("�˸�"), MB_OK);
	}
	else
	{
		printf("OnDropTeamTable ���� \n");
		//MessageBox(NULL, TEXT("����"), TEXT("�˸�"), MB_OK);
	}
}

void OnCreateMemberTable(HWND hdlg)
{
	if (wbdb_CreateMemberTable() == TRUE)
	{
		printf("������̺� ���� ���� \n");
		//MessageBox(NULL, TEXT("����"), TEXT("�˸�"), MB_OK);
	}
	else
	{
		printf("������̺� ���� ���� \n");
		//MessageBox(NULL, TEXT("����"), TEXT("�˸�"), MB_OK);
	}
}

void OnDropMemberTable(HWND hdlg)
{
	if (wbdb_DropMemberTable() == TRUE)
	{
		printf("��� ���� ���� \n");
		//MessageBox(NULL, TEXT("����"), TEXT("�˸�"), MB_OK);
	}
	else
	{
		printf("��� ���� ���� \n");
		//MessageBox(NULL, TEXT("����"), TEXT("�˸�"), MB_OK);
	}
}

void OnCreateSequence(HWND hdlg)
{
	if (wbdb_CreateSequence() == TRUE)
	{
		printf("������ ���� ���� \n");
		//MessageBox(NULL, TEXT("����"), TEXT("�˸�"), MB_OK);
	}
	else
	{
		printf("������ ���� ���� \n");
		//MessageBox(NULL, TEXT("����"), TEXT("�˸�"), MB_OK);
	}
}

void OnDropSequence(HWND hdlg)
{
}

void OnInsertTeam(HWND hdlg)
{
	int team_id;
	TCHAR team_name[20];

	ui_GetTeamCreateInfo(hdlg,&team_id,team_name);

	if (wbdb_InsertTeam(team_id, team_name) == TRUE)
	{
		vector<TEAM> teamlist;
		wbdb_GetTeamSelectAll(&teamlist);
		
	
		ui_TeamListPrint(&teamlist, (int)teamlist.size());
		printf("�� ���� ����\n");
	}
	else
	{
		printf("�� ���� ����\n");
	}
}

void OnInsertMember(HWND hDlg)
{
	int member_id;
	TCHAR member_name[20];
	TCHAR member_gender[10];
	TCHAR member_phone[20];
	int tema_id;

	ui_GetMemberCreateInfo(hDlg,&member_id, member_name, member_gender, member_phone, &tema_id);

	if (wbdb_InsertMember(member_id, member_name, member_gender, member_phone, tema_id)==TRUE)
	{
		vector<MEMBER> memberlist;
		wbdb_GetMemberSelectAll(&memberlist);

		ui_MemberListPrint(&memberlist, (int)memberlist.size());
		printf("��� ���� ����\n");
	}
	else
	{
		printf("��� ���� ����\n");
	}

}
