#pragma once
typedef struct tagTEAM
{
	int tema_id;
	TCHAR team_name[20];

}TEAM;

typedef struct tagMEMBER
{
	int member_id;
	TCHAR member_name[20];
	TCHAR member_gender[10];
	TCHAR member_phone[20];
	int tema_id;
	TCHAR member_regiday[20];
	TCHAR team_name[20];

}MEMBER;

typedef struct tagQUEST
{
	int quest_id;
	TCHAR quest_str[500];
	TCHAR quest_answer1[100];
	TCHAR quest_answer2[100];
	TCHAR quest_answer3[100];
	TCHAR quest_answer4[100];
	int quest_answer;

}QUEST;

typedef struct tagMEMBERSCORE
{
	int mem_id;
	TCHAR mem_name[20];
	int mem_scoreResult;

}MEMBERSCORE;

typedef struct tagTESTPAPER
{
	int exam_id;
	int answer;
	int mem_selectnum;
	int result;
}TESTPAPER;