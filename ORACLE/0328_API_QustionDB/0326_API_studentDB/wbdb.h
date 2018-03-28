#pragma once


BOOL wbdb_DBConnect();
BOOL wbdb_DBDConnect();

BOOL wbdb_CreateTeamTable();
BOOL wbdb_DropTeamTable();

BOOL wbdb_CreateMemberTable();
BOOL wbdb_DropMemberTable();

BOOL wbdb_CreateSequence();
BOOL wbdb_DropSequence();

//
BOOL wbdb_InsertTeam(int _team_id , TCHAR * _team_name);
BOOL wbdb_InsertMember(int member_id, TCHAR * member_name, TCHAR * member_gender, TCHAR * member_phone, int team_id);
BOOL wbdb_InsertExamResult(int quest_id, int mem_id,int selectNum,int quest_answer);

BOOL wbdb_GetTeamSelectAll(vector<TEAM>*teamlist);
BOOL wbdb_GetMemberSelectAll(vector<MEMBER>*memberlist);
BOOL wbdb_GetTestPaperList(vector<TESTPAPER>*testPaperList,TCHAR * target_id);

//
BOOL CommandSql(TCHAR *str);
//
BOOL wbdb_DeleteMemberID(TCHAR * memId);
BOOL wbdb_DeleteTeamID(TCHAR * memId);

//1 MemID 2 TeamID 3 MemName 4 MemGender
BOOL wbdb_GetMemberSelectMODE(vector<MEMBER>* memberlist,TCHAR * clue, int _mode);

//
BOOL wbdb_GetQuests(vector<QUEST>*questlist);

//
BOOL wbdb_SendCommit();

BOOL wbdb_GetAllMemberScore(vector<MEMBERSCORE>* memscorelist);

BOOL wbdb_GetTestMemberCountAndAVG(int * count, double * avg);

void ui_InitTeamListView(HWND hDlg);
//BOOL mydb_CreateTable();
//
//BOOL mydb_DeleteTable();
//
////BOOL mydb_InsertData(Student *pData);
//
//BOOL mydb_SelectData();
//
//BOOL mydb_DeleteData();