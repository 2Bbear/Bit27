#include"std.h"

//mydb.cpp

#define DBNAME TEXT("test2")//odbc �� �ִ� ������ ���ƾ� ��
#define ID	   TEXT("ccm")
#define PW		TEXT("ccm")

SQLHSTMT hStmt;
SQLHENV hEnv;
SQLHDBC hDbc;

BOOL wbdb_DBConnect()
{

	// ���� ������ ���� ������
	SQLRETURN Ret;

	// 1, ȯ�� �ڵ��� �Ҵ��ϰ� ���� �Ӽ��� �����Ѵ�.(p1741)
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
		return false;
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
		return false;

	// 2. ���� �ڵ��� �Ҵ��ϰ� �����Ѵ�.
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
		return false;
	// ����Ŭ ������ �����ϱ�
	Ret = SQLConnect(hDbc, (SQLTCHAR *)DBNAME, SQL_NTS, (SQLTCHAR *)ID, SQL_NTS, (SQLTCHAR *)PW, SQL_NTS);

	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
		return false;

	// ��� �ڵ��� �Ҵ��Ѵ�.
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS)
		return false;

	return true;
}
BOOL wbdb_DBDConnect()
{
	// ������
	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return TRUE;
}
BOOL wbdb_CreateTeamTable()
{
	TCHAR str[1024] = TEXT("CREATE TABLE Team\
		(GroupId number,\
		GroupName varchar2(20),\
		CONSTRAINT Group_id_pk primary key(GroupId));");

	return CommandSql(str);
}

BOOL wbdb_DropTeamTable()
{
	TCHAR str[1024] = TEXT("DROP TABLE Team;");

	return CommandSql(str);
}

BOOL wbdb_CreateMemberTable()
{
	TCHAR str[1024] = TEXT("CREATE TABLE member(mem_ID   	 NUMBER,\
		mem_NAME  	VARCHAR2(20 BYTE) NOT NULL,\
		mem_gen		VARCHAR2(20 BYTE) check(mem_gen in('����', '����')),\
		mem_phone 	 VARCHAR2(20 BYTE),\
		mem_GID          NUMBER NOT NULL,\
		mem_date	date,\
		CONSTRAINT member_PK PRIMARY KEY(mem_ID)); ");
	TCHAR str2[1024] = TEXT("ALTER TABLE member\
		ADD CONSTRAINT member_FK FOREIGN KEY(mem_ID)\
		REFERENCES member(mem_ID);");
	
	CommandSql(str);

	return CommandSql(str2);
}

BOOL wbdb_DropMemberTable()
{
	TCHAR str[1024] = TEXT("DROP TABLE member;");

	return CommandSql(str);
}

BOOL wbdb_CreateSequence()
{
	TCHAR str[1024] = TEXT("create sequence mem_ID_seq\
		increment by 1\
		start with 1000;");

	return CommandSql(str);
}

BOOL wbdb_DropSequence()
{
	return 0;
}

BOOL wbdb_DeleteMemberID(TCHAR * memId)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("delete member where mem_ID=%s;"), memId);

	return CommandSql(str);
}
BOOL wbdb_DeleteTeamID(TCHAR * memId)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("delete team where groupid=%s;"), memId);
	return CommandSql(str);
}
BOOL wbdb_InsertTeam(int _team_id, TCHAR * _team_name)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("insert into Team values(%d , '%s')"), _team_id, _team_name);
	if (CommandSql(str)==TRUE)
	{
		return CommandSql(TEXT("commit;"));
	}
	return FALSE;
}

BOOL wbdb_InsertMember(int member_id, TCHAR * member_name, TCHAR * member_gender, TCHAR * member_phone , int team_id)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("insert into Member values( mem_ID_seq.nextval,'%s','%s','%s',%d, sysdate );"), member_name, member_gender, member_phone, team_id);
	if (CommandSql(str) == TRUE)
	{
		return CommandSql(TEXT("commit;"));
	}
	else
	{
		printf("insert member false \n");
	}
	return FALSE;
}

BOOL wbdb_InsertExamResult(int quest_id, int mem_id, int selectNum, int quest_answer)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("insert into EXAMRESULT\
		values(EXAMRESULT_ID_SEQ.nextval,%d, %d, %d, %d); "), quest_id, mem_id, selectNum, quest_answer== selectNum?10:0);
	if (CommandSql(str) == TRUE)
	{
		return CommandSql(TEXT("commit;"));
	}
	else
	{
		printf("insert ExamResult false \n");
	}
	return FALSE;
}

BOOL CommandSql(TCHAR *str)
{
	if (SQLExecDirect(hStmt, (SQLTCHAR *)str, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}
	return TRUE;
}
BOOL wbdb_GetMemberSelectMODE(vector<MEMBER>* memberlist, TCHAR * clue,int _mode)
{
	int member_id;
	SQLTCHAR name[20];
	SQLTCHAR gender[10];
	SQLTCHAR phone[20];
	int team_id;
	SQLTCHAR day[20];
	SQLTCHAR team_name[20];

	SQLINTEGER  lmember_id, lname, lgender, lphone, lteam_id, lday, lteam_name;


	SQLBindCol(hStmt, 1, SQL_C_ULONG, &member_id, 0, &lmember_id); //��� ���̵�
	SQLBindCol(hStmt, 2, SQL_C_CHAR, name, sizeof(name), &lname);//�̸�
	SQLBindCol(hStmt, 3, SQL_C_CHAR, gender, sizeof(gender), &lgender);//����
	SQLBindCol(hStmt, 4, SQL_C_CHAR, phone, sizeof(phone), &lphone);//��ȭ��ȣ
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &team_id, 0, &lteam_id);//�����̵�
	SQLBindCol(hStmt, 6, SQL_C_CHAR, day, sizeof(day), &lday);//��ϳ�¥
	SQLBindCol(hStmt, 7, SQL_C_CHAR, team_name, sizeof(team_name), &lteam_name);//����

	TCHAR sql[1024];
	if (_mode==1)//MemID
	{
		wsprintf(sql, TEXT("SELECT m.* , t.groupname\
		FROM member m NATURAL join team t\
		where m.mem_gid = t.groupid AND m.mem_id=%s;"), clue);
	}
	else if (_mode==2)//TeamID
	{
		wsprintf(sql, TEXT("SELECT m.* , t.groupname\
		FROM member m NATURAL join team t\
		where m.mem_gid = t.groupid AND m.mem_gid='%s';"), clue);
	}
	else if (_mode==3)//MemName
	{
		wsprintf(sql, TEXT("SELECT m.* , t.groupname\
		FROM member m NATURAL join team t\
		where m.mem_gid = t.groupid AND m.mem_name='%s';"), clue);
	}
	else if (_mode==4)//MemGender
	{
		wsprintf(sql, TEXT("SELECT m.* , t.groupname\
		FROM member m NATURAL join team t\
		where m.mem_gid = t.groupid AND m.mem_gen='%s';"), clue);
	}
	


	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
	{
		printf("db���� �о���� ����\n");
		return FALSE;
	}


	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{

		MEMBER data;
		//��� ���̵�
		data.member_id = member_id;
		//�̸�
		MultiByteToWideChar(CP_ACP, 0, (char*)name, -1, data.member_name, sizeof(data.member_name));
		//����
		MultiByteToWideChar(CP_ACP, 0, (char*)gender, -1, data.member_gender, sizeof(data.member_gender));
		//��ȭ��ȣ
		MultiByteToWideChar(CP_ACP, 0, (char*)phone, -1, data.member_phone, sizeof(data.member_phone));
		//�� ���̵�
		data.tema_id = team_id;
		//��ϳ���
		MultiByteToWideChar(CP_ACP, 0, (char*)day, -1, data.member_regiday, sizeof(data.member_regiday));
		//����
		MultiByteToWideChar(CP_ACP, 0, (char*)team_name, -1, data.team_name, sizeof(data.team_name));

		memberlist->push_back(data);
	}
	return TRUE;
}
BOOL wbdb_GetQuests(vector<QUEST>* questlist)
{
	printf("DB ���� ������ �޾ƿ��� \n");
	//������ ����
	int temp_id;
	TCHAR temp_str[500];
	TCHAR temp_answer1[100];
	TCHAR temp_answer2[100];
	TCHAR temp_answer3[100];
	TCHAR temp_answer4[100];
	int temp_answer;

	SQLINTEGER lid, lstr, lanswer1, lanswer2, lanswer3, lanswer4, lanswer;
	//���ε�
	SQLBindCol(hStmt, 1, SQL_C_ULONG, &temp_id, 0, &lid); //���� ���̵�
	SQLBindCol(hStmt, 2, SQL_C_CHAR, temp_str, sizeof(temp_str), &lstr);//���� ����
	SQLBindCol(hStmt, 3, SQL_C_CHAR, temp_answer1, sizeof(temp_answer1), &lanswer1);//��1
	SQLBindCol(hStmt, 4, SQL_C_CHAR, temp_answer2, sizeof(temp_answer2), &lanswer2);//��2
	SQLBindCol(hStmt, 5, SQL_C_CHAR, temp_answer3, sizeof(temp_answer3), &lanswer3);//��3
	SQLBindCol(hStmt, 6, SQL_C_CHAR, temp_answer4, sizeof(temp_answer4), &lanswer4);//��4
	SQLBindCol(hStmt, 7, SQL_C_ULONG, &temp_answer, 0, &lanswer);//��¥��

	//���� ����
	TCHAR sql2[2048] = { TEXT("SELECT ep.*\
		FROM exam ex, exampool ep\
		WHERE ex.exampool_id = ep.exampool_id;") };


	//���� ���� �� ��������
	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql2, SQL_NTS) != SQL_SUCCESS)
	{
		printf("db���� �о���� ����\n");
		return FALSE;
	}
	//�� �޾ƿ���
	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
		printf("DB���� �޾ƿ�\n");
		QUEST data;
		//���� ���̵�
		data.quest_id = temp_id;
		//���� ����
		MultiByteToWideChar(CP_ACP, 0, (char*)temp_str, -1, data.quest_str, sizeof(data.quest_str));
		//��1
		MultiByteToWideChar(CP_ACP, 0, (char*)temp_answer1, -1, data.quest_answer1, sizeof(data.quest_answer1));
		//��2
		MultiByteToWideChar(CP_ACP, 0, (char*)temp_answer2, -1, data.quest_answer2, sizeof(data.quest_answer2));
		//��3
		MultiByteToWideChar(CP_ACP, 0, (char*)temp_answer3, -1, data.quest_answer3, sizeof(data.quest_answer3));
		//��4
		MultiByteToWideChar(CP_ACP, 0, (char*)temp_answer4, -1, data.quest_answer4, sizeof(data.quest_answer4));
		//��¥��
		data.quest_answer = temp_answer;
		
		questlist->push_back(data);
		
	}

	printf("wbdb_GetQuests ����\n");
	return TRUE;
}
BOOL wbdb_SendCommit()
{
	TCHAR str[1024];
	wsprintf(str, TEXT("Commit;"));

	return CommandSql(str);
}
BOOL wbdb_GetAllMemberScore(vector<MEMBERSCORE>* memscorelist)
{
	printf("DB ���� ��� ��� ���� �޾ƿ��� \n");
	//������ ����
	int temp_id;
	TCHAR temp_name[20];
	int temp_score;

	SQLINTEGER lid, lname, lscore;

	//���ε�
	SQLBindCol(hStmt, 1, SQL_C_ULONG, &temp_id, 0, &lid); //��� ���̵�
	SQLBindCol(hStmt, 2, SQL_C_CHAR, temp_name, sizeof(temp_name), &lname);//��� �̸�
	SQLBindCol(hStmt, 3, SQL_C_ULONG, &temp_score, 0, &lscore); //socre

	//���� ����
	TCHAR sql2[2048] = { TEXT("SELECT e.mem_id, m.mem_name , SUM(result) sresult\
		FROM member m , examresult e\
		WHERE m.mem_id = e.mem_id\
		GROUP BY m.mem_name, e.mem_id; ") };

	//���� ���� �� ��������
	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql2, SQL_NTS) != SQL_SUCCESS)
	{
		printf("db���� �о���� ����\n");
		return FALSE;
	}
	//�� �޾ƿ���
	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
		printf("DB���� �޾ƿ�\n");
		MEMBERSCORE data;
		//��� ���̵�
		data.mem_id = temp_id;
		//��� �̸�
		MultiByteToWideChar(CP_ACP, 0, (char*)temp_name, -1, data.mem_name, sizeof(data.mem_name));
		//��� ����
		data.mem_scoreResult = temp_score;
		memscorelist->push_back(data);

	}

	printf("wbdb_GetAllMemberScore ����\n");

	return TRUE;
}
BOOL wbdb_GetMemberSelectAll(vector<MEMBER>*memberlist)
{
	int member_id;
	SQLTCHAR name[20];
	SQLTCHAR gender[10];
	SQLTCHAR phone[20];
	int team_id;
	SQLTCHAR day[20];
	SQLTCHAR team_name[20];

	SQLINTEGER  lmember_id, lname, lgender, lphone, lteam_id, lday, lteam_name;


	SQLBindCol(hStmt, 1, SQL_C_ULONG, &member_id, 0, &lmember_id); //��� ���̵�
	SQLBindCol(hStmt, 2, SQL_C_CHAR, name, sizeof(name), &lname);//�̸�
	SQLBindCol(hStmt, 3, SQL_C_CHAR, gender, sizeof(gender), &lgender);//����
	SQLBindCol(hStmt, 4, SQL_C_CHAR, phone, sizeof(phone), &lphone);//��ȭ��ȣ
	SQLBindCol(hStmt, 5, SQL_C_ULONG, &team_id, 0, &lteam_id);//�����̵�
	SQLBindCol(hStmt, 6, SQL_C_CHAR, day, sizeof(day), &lday);//��ϳ�¥
	SQLBindCol(hStmt, 7, SQL_C_CHAR, team_name, sizeof(team_name), &lteam_name);//����

	TCHAR sql[1024] = TEXT("SELECT m.* , t.groupname\
		FROM member m NATURAL join team t\
	where m.mem_gid = t.groupid; ");


	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
	{
		printf("db���� �о���� ����\n");
		return FALSE;
	}


	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{

		MEMBER data;
		//��� ���̵�
		data.member_id = member_id;
		//�̸�
		MultiByteToWideChar(CP_ACP, 0, (char*)name, -1, data.member_name, sizeof(data.member_name));
		//����
		MultiByteToWideChar(CP_ACP, 0, (char*)gender, -1, data.member_gender, sizeof(data.member_gender));
		//��ȭ��ȣ
		MultiByteToWideChar(CP_ACP, 0, (char*)phone, -1, data.member_phone, sizeof(data.member_phone));
		//�� ���̵�
		data.tema_id = team_id;
		//��ϳ���
		MultiByteToWideChar(CP_ACP, 0, (char*)day, -1, data.member_regiday, sizeof(data.member_regiday));
		//����
		MultiByteToWideChar(CP_ACP, 0, (char*)team_name, -1, data.team_name, sizeof(data.team_name));

		memberlist->push_back(data);
	}
	return TRUE;
}
BOOL wbdb_GetTestPaperList(vector<TESTPAPER>* testPaperList, TCHAR * target_id)
{
	printf("DB ���� �ش� ����� ������ �޾ƿ��� \n");
	//������ ����
	int temp_examid;
	int temp_answer;
	int temp_memselectnum;
	int temp_result;

	SQLINTEGER lexamid, lanswer, lmemselectnum, lresult;

	//���ε�
	SQLBindCol(hStmt, 1, SQL_C_ULONG, &temp_examid, 0, &lexamid); //���� ���̵�
	SQLBindCol(hStmt, 2, SQL_C_ULONG, &temp_answer, 0, &lanswer); //����
	SQLBindCol(hStmt, 3, SQL_C_ULONG, &temp_memselectnum, 0, &lmemselectnum); //�ش� ����� ������ ��
	SQLBindCol(hStmt, 4, SQL_C_ULONG, &temp_result, 0, &lresult); //���� ���

	//���� ����
	TCHAR sql2[2048];
	wsprintf(sql2, TEXT("SELECT er.exam_id, ep.answer, er.member_selectnum, er.result\
		FROM Examresult er NATURAL join exampool ep\
		WHERE er.exam_id = ep.exampool_id AND er.mem_id = %s; "), target_id);

	//���� ���� �� ��������
	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql2, SQL_NTS) != SQL_SUCCESS)
	{
		printf("db���� �о���� ����\n");
		return FALSE;
	}
	//�� �޾ƿ���
	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
		printf("DB���� �޾ƿ�\n");
		TESTPAPER data;
		//���� ���̵�
		data.exam_id = temp_examid;
		printf("%d \n", temp_examid);
		//����
		data.answer = temp_answer;
		//�ش� ����� ������ ����
		data.mem_selectnum = temp_memselectnum;
		//���� ���
		data.result = temp_result;

		testPaperList->push_back(data);

	}

	printf("wbdb_GetTestPaperList ����\n");
	return TRUE;
}
BOOL wbdb_GetTeamSelectAll(vector<TEAM>* teamlist)
{
	int team_id;
	SQLTCHAR name[20];
	SQLINTEGER lteam_id,lname;


	SQLBindCol(hStmt, 1, SQL_C_ULONG, &team_id, 0, &lteam_id);
	SQLBindCol(hStmt, 2, SQL_C_CHAR, name, sizeof(name), &lname);

	


	TCHAR sql[256] = TEXT("select * from team");


	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
	{
		printf("db���� �о���� ����\n");
		return FALSE;
	}


	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
	
		TEAM data;
		data.tema_id = team_id;
		
		MultiByteToWideChar(CP_ACP, 0, (char*)name, -1, data.team_name, sizeof(data.team_name));

		teamlist->push_back(data);
	}
	return TRUE;
}

BOOL wbdb_GetTestMemberCountAndAVG(int * count, double * avg)
{
	printf("DB ���� �����ο�, ��� ���� ���ϱ� \n");
	//������ ����
	int temp_count;
	double temp_avg;

	SQLINTEGER lcount, lavg;

	//���ε�
	SQLBindCol(hStmt, 1, SQL_C_ULONG, &temp_count, 0, &lcount); //�����ο�
	SQLBindCol(hStmt, 2, SQL_C_ULONG, &temp_avg, 0, &lavg); //��� ����

	//���� ����
	TCHAR sql2[2048] = { TEXT("SELECT COUNT(mem_name),AVG(sresult)\
		FROM(SELECT e.mem_id, m.mem_name , SUM(result) sresult\
			FROM member m , examresult e\
			WHERE m.mem_id = e.mem_id\
			GROUP BY m.mem_name, e.mem_id) ptr; ") };

	//���� ���� �� ��������
	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql2, SQL_NTS) != SQL_SUCCESS)
	{
		printf("db���� �о���� ����\n");
		return FALSE;
	}

	//�� �޾ƿ���
	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
		printf("DB���� �޾ƿ�\n");
		
		//�� ���� �ο�
		*count = temp_count;
		//��� ����
		*avg = temp_avg;

	}

	printf("wbdb_GetAllMemberScore ����\n");

	return TRUE;


}


//
// BOOL mydb_SelectData()
//{
//	SQLCHAR Name[256];
//
//	SQLINTEGER lName, lSnum, lPhone, lEmail;
//	int ssnum;
//
//	SQLCHAR Phone[256];
//	SQLCHAR Email[256];
//
//	SQLBindCol(hStmt, 1, SQL_C_CHAR, Name, sizeof(Name), &lName);
//	SQLBindCol(hStmt, 2, SQL_C_ULONG, &ssnum, 0, &lSnum);
//	SQLBindCol(hStmt, 3, SQL_C_CHAR, Phone, sizeof(Phone), &lPhone);
//	SQLBindCol(hStmt, 4, SQL_C_CHAR, Email, sizeof(Email), &lEmail);
//
//	char sql[256] = "select * from sb";
//
//	if (SQLExecDirect(hStmt, (SQLCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
//	{
//		return FALSE;
//	}
//
//	char name[21], num[21], phoneNumber[21], email[41];
//	int count = 0;
//	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
//	{
//		wsprintf(name, "%s", Name);
//		wsprintf(num, "%d", ssnum);
//		wsprintf(phoneNumber, "%s", Phone);
//		wsprintf(email, "%s", Email);
//
//		control_GetData(count++, name, num, phoneNumber, email);
//
//	}
//	return TRUE;
//}

//
//
//BOOL mydb_CreateTable()
//{
//	char str[1024] = "create table sb(name varchar2(30byte) not null, snum number(10,0) not null, phone varchar2(20byte), email varchar2(40byte));";
//	
//	return TRUE;
//}
//
//
//BOOL mydb_DeleteTable()
//{
//	char str[256] = "drop table sb";
//	if (SQLExecDirect(hStmt, (SQLCHAR *)str, SQL_NTS) != SQL_SUCCESS)
//	{
//		return FALSE;
//	}
//	return TRUE;
//}
//
//
////BOOL mydb_InsertData(Student *pData)
////{
////	char sql[256];
////	wsprintf(sql, "insert into sb(name,snum,phone,email) values( '%s', '%d', '%s' ,'%s')"
////		, pData->sName.c_str(), pData->sNum, pData->sPhone.c_str(), pData->email.c_str());
////	if (SQLExecDirect(hStmt, (SQLCHAR *)sql, SQL_NTS) != SQL_SUCCESS)
////	{
////		return FALSE;
////	}
////	else
////	{
////		return TRUE;
////	}
////}
//
//

//
//BOOL mydb_DeleteData()
//{
//	char sql[256];
//
//	wsprintf(sql, "delete sb");
//	if (SQLExecDirect(hStmt, (SQLCHAR *)sql, SQL_NTS) != SQL_SUCCESS)
//	{
//		return FALSE;
//	}
//	return TRUE;
//}