//wbdb.h

BOOL wbdb_DBConnect();

BOOL wbdb_DBDConnect();

BOOL wbdb_CreateExam(TCHAR *pool_exam, TCHAR *pool_ans1, TCHAR *pool_ans2,
	TCHAR *pool_ans3, TCHAR *pool_ans4, int answer);
BOOL wbdb_GetExamId(int exam_id, int pool_id);
BOOL wbdb_DropTeamTable();
BOOL wbdb_CreateMemberTable();
BOOL wbdb_DropMemberTable();
BOOL wbdb_CreateSequence();
BOOL wbdb_DropSequence();
BOOL wbdb_InsertExampool(TCHAR *pool_exam, TCHAR *pool_ans1, TCHAR *pool_ans2,
	TCHAR *pool_ans3, TCHAR *pool_ans4, int answer);
BOOL wbdb_InsertMember(TCHAR *mem_name, TCHAR *mem_gender, TCHAR *mem_phone, int team_id);

BOOL CommandSql(TCHAR *str);

BOOL wbdb_GetExamPoolCount(int *count);

BOOL wbdb_GetExamPoolIdx(int * exampoolid);

BOOL wbdb_InsertExam(int  idx);
//BOOL wbdb_GetTeamSelectAll(vector<TEAM> *teamlist);
//BOOL wbdb_GetMemberSelectAll(vector<MEMBER> *teamlist);

//BOOL mydb_CreateTable();
//
//BOOL mydb_DeleteTable();
//
//BOOL mydb_InsertData(Student *pData);
//
//BOOL mydb_SelectData();
//
//BOOL mydb_DeleteData();