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