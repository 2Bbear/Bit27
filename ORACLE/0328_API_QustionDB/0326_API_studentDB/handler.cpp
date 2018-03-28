#include"std.h"

int g_memberGender = 0; // 1은 남성 , 2는 여성
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
	//버튼 입력을 받는 event를 처리하기 위한 영역
	switch (LOWORD(wParam))
	{
	//갱신 출력
	/*case IDC_BUTTON1:
	{
		OnPrint(hDlg);
		return 0;
	}*/
	//dig 초기화
	//라디오버튼 답 선택
	case IDC_RADIO3://1번
	{
		g_selectQuestAnswer = 1;
		return 0;
	}
	case IDC_RADIO5://2번
	{
		g_selectQuestAnswer =2;
		return 0;
	}
	case IDC_RADIO4://3번
	{
		g_selectQuestAnswer = 3;
		return 0;
	}
	case IDC_RADIO6://4번
	{
		g_selectQuestAnswer = 4;
		return 0;
	}
	//라디오버튼 남성
	case IDC_RADIO1:
	{
		g_memberGender = 1;
		return 0;
	}
	//라디오버튼 여성
	case IDC_RADIO2:
	{
		
		g_memberGender = 2;
		return 0;
	}
	//DB 접속
	case IDC_BUTTON_CONNECT:
	{
		OnDBConnect(hDlg);
		return 0;
	}
	//DB 접속해제
	case IDC_BUTTON_DISCONNECT:
	{
		OnDBDConnect(hDlg);
		return 0;
	}
	//팀 테이블 생성
	case IDC_BUTTON2 :
	{
		OnCreateTeamTable(hDlg);
		return 0;
	}
	//팀 테이블 삭제
	case IDC_BUTTON3:
	{
		OnDropTeamTable(hDlg);
		return 0;
	}
	//멤버 테이블 생성
	case IDC_BUTTON4:
	{
		OnCreateMemberTable(hDlg);
		return 0;
	}
	//멤버 테이블 삭제
	case IDC_BUTTON5:
	{
		OnDropMemberTable(hDlg);
		return 0;
	}
	//시퀀스 생성
	case IDC_BUTTON6:
	{
		OnCreateSequence(hDlg);
		return 0;
	}
	//시퀀스 삭제
	case IDC_BUTTON7:
	{
		OnDropSequence(hDlg);
		return 0;
	}
	//Team등록 버튼
	case IDC_BUTTON8:
	{
		OnInsertTeam(hDlg);
		return 0; 
	}
	//Member등록 버튼
	case IDC_BUTTON12:
	{
		OnInsertMember(hDlg);
		return 0;
	}

	//Update 버튼
	case IDC_BUTTON10:
	{
		OnUpdateList(hDlg);
		return 0;
	}
	//Select 버튼
	case IDC_BUTTON13:
	{
		OnSelect(hDlg);
		return 0;
	}
	//Delete 버튼
	case IDC_BUTTON11:
	{
		OnDelete(hDlg);
		return 0;
	}
	//문제풀기 시작
	case IDC_BUTTON_STARTQUEST:
	{
		OnStartQuest(hDlg);
		return 0;
	}
	//답전송 버튼
	case IDC_BUTTON_ANSWER:
	{
		OnSendAnswer(hDlg);
		return 0;
	}
	//전체점수보기 버튼
	case IDC_BUTTON16:
	{
		OnAllScorePrint(hDlg);
		return 0;
	}
	// 멤버 문제 검색
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
	//리스트 초기화

	GetProcessList(hDlg);
	return 0;
}

void OnUpdateList(HWND hDlg)
{
	printf("OnUpdateList \n");
	vector<TEAM> teamlist;
	wbdb_GetTeamSelectAll(&teamlist);
	ui_TeamListPrint(&teamlist, (int)teamlist.size());

	printf("팀 리스트 업데이트 완료 \n");

	vector<MEMBER> memberlist;
	wbdb_GetMemberSelectAll(&memberlist);
	ui_MemberListPrint(&memberlist, (int)memberlist.size());

	printf("멤버 리스트 업데이트 완료 \n");
}

void OnSelect(HWND hDlg)
{
	TCHAR select[20];
	ui_GetComboBoxText(hDlg,select);

	//select edit 박스의 아이디 값 추출
	TCHAR id[20];
	ui_GetSelectEditBoxText(hDlg, id);
	//가져온 아이디 값으로 해당 멤버 검색
	vector<MEMBER> memberlist;
	if (_tcscmp(select, TEXT("")) == 0)
	{
		return;
	}
	if (_tcscmp(select,TEXT("MemID"))==0)
	{
		printf("멤버 ID 선택\n");
		wbdb_GetMemberSelectMODE(&memberlist, id,1);
	}
	else if (_tcscmp(select, TEXT("TeamID")) == 0)
	{
		printf("팀 ID 선택\n");
		wbdb_GetMemberSelectMODE(&memberlist, id, 2);
	}
	else if (_tcscmp(select, TEXT("MemName")) == 0)
	{
		printf("멤버이름 선택\n");
		wbdb_GetMemberSelectMODE(&memberlist, id, 3);
	}
	else if (_tcscmp(select, TEXT("MemGender")) == 0)
	{
		printf("멤버성별 선택\n");
		wbdb_GetMemberSelectMODE(&memberlist, id, 4);
	}
	//해당 멤버의 정보 Member list에 출력
	ui_MemberListPrint(&memberlist, (int)memberlist.size());

}

void OnCancel(HWND hDlg)
{
	EndDialog(hDlg, IDCANCEL);
}

void OnDelete(HWND hDlg)
{
	//어떤 콤보박스가 선태되었는지 추출
	TCHAR select[20];
	ui_GetComboBoxText(hDlg, select);

	//select edit 박스의 아이디 값 추출
	TCHAR id[20];
	ui_GetSelectEditBoxText(hDlg, id);

	if (_tcscmp(select, TEXT("")) == 0)
	{
		return;
	}

	if (_tcscmp(select, TEXT("MemID")) == 0)
	{
		printf("멤버 ID 선택\n");
		wbdb_DeleteMemberID(id);
	}
	else if (_tcscmp(select, TEXT("TeamID")) == 0)
	{
		printf("팀 ID 선택\n");
		wbdb_DeleteTeamID(id);
		
	}
	else if (_tcscmp(select, TEXT("MemName")) == 0)
	{
		printf("멤버이름 선택\n");
		
	}
	else if (_tcscmp(select, TEXT("MemGender")) == 0)
	{
		printf("멤버성별 선택\n");
		
	}

}

vector<QUEST> questlist;
void OnStartQuest(HWND hDlg)
{
	questlist.clear();
	printf("문제 풀기 시작 버튼 \n");
	//현재 시험풀고 있는 중인지 확인
	if (true)
	{
		//멤버 아이디 받아오기
		ui_getMemberId(hDlg,&g_currentLoginMember);
		//db에서 문제들 다 받아오기
		if (wbdb_GetQuests(&questlist))
		{
			//문제 출력
			printf("문제출력하기 \n");
			ui_PrintQuest(hDlg,&questlist);
			g_currentQuestIndex++;
		}
	}
}

void OnSendAnswer(HWND hDlg)
{
	printf("답전송 버튼 \n");
	//현재 첫번째 문제를 풀고 있는지?
	if (g_currentQuestIndex>0)
	{
		//examresult에 insert하기
		wbdb_InsertExamResult(questlist[g_currentQuestIndex-1].quest_id, g_currentLoginMember, g_selectQuestAnswer, questlist[g_currentQuestIndex - 1].quest_answer);
		//다음 문제 출력하기
		printf("다음 문제 출력 \n");
		ui_PrintQuest(hDlg, &questlist);
		g_currentQuestIndex++;
		//마지막 문제에 도달할경우
		if ((int)questlist.size()<= g_currentQuestIndex)
		{
			g_currentQuestIndex = 0;
			//commit 쿼리 전송
			wbdb_SendCommit();
			SetDlgItemText(hDlg, IDC_EDIT_QUEST, TEXT("시험문제 푸느라 고생하셨습니다.\n"));
		}
	}

}

void OnAllScorePrint(HWND hDlg)
{
	//우측 아래 리스트 컨트롤 초기화
	ui_InitScoreListView(hDlg, 1);
	vector<MEMBERSCORE> memberScoreList;
	//DB에서 MEMBERSCORE 받기
	if (wbdb_GetAllMemberScore(&memberScoreList)==TRUE)
	{
		//출력
		ui_MemberScoreListPrint(&memberScoreList, (int)memberScoreList.size());
	}
	else
	{
		printf("전체점수 보기 실패 \n");
	}
}

void OnSearchMemberQuests(HWND hDlg)
{
	//우측 아래 리스트 컨트롤 초기화
	ui_InitScoreListView(hDlg, 2);
	//edit에서 검색할 멤버 id 추출하기
	TCHAR targetName[20];
	GetDlgItemText(hDlg, IDC_EDIT44, targetName, sizeof(targetName));

	//DB에서 TESTPAPERlist 값 받아오기
	vector<TESTPAPER> testPaperList;
	if (wbdb_GetTestPaperList(&testPaperList, targetName)==TRUE)
	{
		//출력
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
	//리스트 저장
	//coll_proListSave(&datalist, size);

	//화면에 출력
//	ui_processListPrint(&datalist, size);
}

void OnDBConnect(HWND hdlg)
{

	if (wbdb_DBConnect()==TRUE)
	{
		ui_printTestMemberCountAndAVG(hdlg);
		printf("OnDBConnect 성공\n");
	}
	else
	{
		printf("OnDBConnect 실패\n");
	}
}

void OnDBDConnect(HWND hdlg)
{
	if (wbdb_DBConnect() == TRUE)
	{
		printf("db접속해제 성공\n");
		//MessageBox(NULL, TEXT("db접속해제 성공"), TEXT("알림"), MB_OK);
	}
	else
	{
		printf("db접속해제 실패\n");
		MessageBox(NULL, TEXT("db접속해제 실패"), TEXT("알림"), MB_OK);
	}
}

void OnCreateTeamTable(HWND hdlg)
{
	if (wbdb_CreateTeamTable()==TRUE)
	{
		printf("OnCreateTeamTable 성공\n");
		//MessageBox(NULL, TEXT("성공"), TEXT("알림"), MB_OK);
	}
	else
	{
		printf("OnCreateTeamTable 실패\n");
		//MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);
	}
}

void OnDropTeamTable(HWND hdlg)
{
	if (wbdb_DropTeamTable() == TRUE)
	{
		printf("OnDropTeamTable 성공 \n");
		//MessageBox(NULL, TEXT("성공"), TEXT("알림"), MB_OK);
	}
	else
	{
		printf("OnDropTeamTable 실패 \n");
		//MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);
	}
}

void OnCreateMemberTable(HWND hdlg)
{
	if (wbdb_CreateMemberTable() == TRUE)
	{
		printf("멤버테이블 생성 성공 \n");
		//MessageBox(NULL, TEXT("성공"), TEXT("알림"), MB_OK);
	}
	else
	{
		printf("멤버테이블 생성 실패 \n");
		//MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);
	}
}

void OnDropMemberTable(HWND hdlg)
{
	if (wbdb_DropMemberTable() == TRUE)
	{
		printf("멤버 삭제 성공 \n");
		//MessageBox(NULL, TEXT("성공"), TEXT("알림"), MB_OK);
	}
	else
	{
		printf("멤버 삭제 실패 \n");
		//MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);
	}
}

void OnCreateSequence(HWND hdlg)
{
	if (wbdb_CreateSequence() == TRUE)
	{
		printf("시퀀스 생성 성공 \n");
		//MessageBox(NULL, TEXT("성공"), TEXT("알림"), MB_OK);
	}
	else
	{
		printf("시퀀스 생성 실패 \n");
		//MessageBox(NULL, TEXT("실패"), TEXT("알림"), MB_OK);
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
		printf("팀 삽입 성공\n");
	}
	else
	{
		printf("팀 삽입 실패\n");
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
		printf("멤버 삽입 성공\n");
	}
	else
	{
		printf("멤버 삽입 실패\n");
	}

}
