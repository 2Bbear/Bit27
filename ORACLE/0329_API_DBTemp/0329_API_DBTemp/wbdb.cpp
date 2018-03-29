//mydb.cpp
#include "std.h"
#include<sql.h>
#include<sqlext.h>
#define DBNAME	TEXT("test2")
#define ID		TEXT("ccm")
#define PW		TEXT("ccm")

SQLHSTMT hStmt;
SQLHENV hEnv;
SQLHDBC hDbc;

BOOL wbdb_DBConnect()
{

	// 연결 설정을 위한 변수들
	SQLRETURN Ret;

	// 1, 환경 핸들을 할당하고 버전 속성을 설정한다.(p1741)
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
		return false;
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
		return false;

	// 2. 연결 핸들을 할당하고 연결한다.
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
		return false;
	// 오라클 서버에 연결하기
	Ret = SQLConnect(hDbc, (SQLTCHAR *)DBNAME, SQL_NTS, (SQLTCHAR *)ID, SQL_NTS, (SQLTCHAR *)PW, SQL_NTS);

	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
		return false;

	// 명령 핸들을 할당한다.
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS)
		return false;

	return true;
}

BOOL wbdb_DBDConnect()
{
	// 뒷정리
	if (hStmt) SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (hDbc) SQLDisconnect(hDbc);
	if (hDbc) SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (hEnv) SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	
	return TRUE;
}

BOOL wbdb_CreateExam(TCHAR *pool_exam, TCHAR *pool_ans1, TCHAR *pool_ans2,
	TCHAR *pool_ans3, TCHAR *pool_ans4, int answer)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("insert into exampool values(EXAMPOOL_ID_SEQ.nextval,\
					    '%s', '%s', '%s', '%s', '%s', %d);")
						, pool_exam, pool_ans1, pool_ans2, pool_ans3, pool_ans4, answer);

	if (CommandSql(str) == TRUE)
	{	
		/*int expool_id;
		SQLINTEGER lexpool_id;

		SQLBindCol(hStmt, 1, SQL_C_ULONG, &expool_id, 0, &lexpool_id);

		TCHAR sql[256];
		wsprintf(sql, TEXT("select exampool_id from exampool where question = '%s'"), pool_exam);

		if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
		{
			return FALSE;
		}*/

	

		return CommandSql(TEXT("commit"));
	}
	return FALSE;
}

BOOL wbdb_GetExamId(int exam_id, int pool_id)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("insert into exam values(EXAM_ID_SEQ.nextval, %d);"), pool_id);

	if (CommandSql(str) == TRUE)
	{
		int ex_id;
		SQLINTEGER lex_id;

		SQLBindCol(hStmt, 1, SQL_C_ULONG, &ex_id, 0, &lex_id);

		TCHAR sql[256];
		wsprintf(sql, TEXT("select exam_id from exampool where question = '%s'"), exam_id);

		if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
		{
			return FALSE;
		}

		ex_id = exam_id;

		return CommandSql(TEXT("commit"));
	}
	return FALSE;
}

BOOL wbdb_DropTeamTable()
{
	TCHAR str[1024] = TEXT("drop table team;");

	return CommandSql(str);
}

BOOL wbdb_CreateMemberTable()
{
	TCHAR str[2048] = TEXT("CREATE TABLE member(\
	mem_ID   	NUMBER, \
	mem_NAME  	VARCHAR2(20 BYTE) NOT NULL, \
	mem_gen		VARCHAR2(20 BYTE) check(mem_gen in('남성', '여성')), \
	mem_phone 	VARCHAR2(20 BYTE), \
	mem_GID     NUMBER NOT NULL, \
	mem_date	date, \
	constraint member_pk PRIMARY Key(mem_id), \
	CONSTRAINT MEMBER_FK FOREIGN KEY(mem_GID) REFERENCES team(groupID));");

	return CommandSql(str);
}

BOOL wbdb_DropMemberTable()
{
	TCHAR str[1024] = TEXT("drop table member;");

	return CommandSql(str);
}

BOOL wbdb_CreateSequence()
{
	TCHAR str[1024] = TEXT("create sequence mem_ID_seq increment by 1 start with 1000;");

	return CommandSql(str);
}

BOOL wbdb_DropSequence()
{
	TCHAR str[1024] = TEXT("drop sequence mem_ID_seq;");

	return CommandSql(str);
}

BOOL wbdb_InsertExampool(TCHAR *pool_exam, TCHAR *pool_ans1, TCHAR *pool_ans2, 
	TCHAR *pool_ans3, TCHAR *pool_ans4, int answer)
{
	TCHAR str[1024];
//	wsprintf(str, TEXT("insert into Team values(%d, '%s');"), team_id, team_name);

	if (CommandSql(str) == TRUE)
		return CommandSql(TEXT("commit"));
	return FALSE;
}

BOOL wbdb_InsertMember(TCHAR *mem_name, TCHAR *mem_gender, TCHAR *mem_phone, int team_id)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("insert into member values(mem_ID_seq.nextval, '%s', '%s', '%s', %d, sysdate);"),
		mem_name, mem_gender, mem_phone, team_id);

	if (CommandSql(str) == TRUE)
		return CommandSql(TEXT("commit"));
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

BOOL wbdb_GetExamPoolCount(int * count)
{
	//저장 변수
	int temp_count;

	SQLINTEGER lcount;

	//바인딩
	SQLBindCol(hStmt, 1, SQL_C_ULONG, &temp_count, 0, &lcount);

	//쿼리문
	TCHAR sql[256] = TEXT("select count(*) from exampool;");
	//에러 검출
	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE;
	}

	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
		*count = temp_count;
	}

	return TRUE;
}

BOOL wbdb_GetExamPoolIdx(int * exampoolid)
{
	//저장 변수
	int temp_id;

	SQLINTEGER lid;

	//바인딩
	SQLBindCol(hStmt, 1, SQL_C_ULONG, &temp_id, 0, &lid);

	//쿼리 던지기
	TCHAR sql[256] = TEXT("select e.exampool_id\
		FROM exampool e; ");

	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
	{
		return FALSE; 
	}
	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
	{
		exampoolid[i] = temp_id;
	}

	return TRUE;
}

BOOL wbdb_InsertExam(int idx)
{
	TCHAR str[1024];
	wsprintf(str, TEXT("INSERT into exam values(exam_id_seq.nextval,%d);"), idx);

	if (CommandSql(str) == TRUE)
		return CommandSql(TEXT("commit"));
	return FALSE;
}

//BOOL wbdb_GetSelectAll(vector<EXAMPOOL> *exampool)
//{
//	int team_id;
//	SQLCHAR name[256];
//	SQLINTEGER lteam_id, lname;
//
//	SQLBindCol(hStmt, 1, SQL_C_ULONG, &team_id, 0, &lteam_id);	
//	SQLBindCol(hStmt, 2, SQL_C_CHAR, name, sizeof(name), &lname);
//
//	TCHAR sql[256] = TEXT("select * from team");
//	
//	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
//	{
//		return FALSE; 
//	}
//
//	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
//	{
//		TEAM data;
//		data.team_id = team_id;
//		MultiByteToWideChar(CP_ACP, 0, (char*)name, -1, data.team_name, sizeof(data.team_name));
//
//		teamlist->push_back(data);
//	}
//}

//BOOL wbdb_GetMemberSelectAll(vector<MEMBER> *memlist)
//{
//	int mem_id;
//	SQLCHAR name[20], gender[20], phone[20], date[20]/*, team_name[20]*/;
//	int team_id;
//	SQLINTEGER lmem_id, lname, lgen, lphone, lteam_id, ldate/*, lteam_name*/;
//
//	SQLBindCol(hStmt, 1, SQL_C_ULONG, &mem_id, 0, &lmem_id);
//	SQLBindCol(hStmt, 2, SQL_C_CHAR, name, sizeof(name), &lname);
//	SQLBindCol(hStmt, 3, SQL_C_CHAR, gender, sizeof(gender), &lgen);
//	SQLBindCol(hStmt, 4, SQL_C_CHAR, phone, sizeof(phone), &lphone);
//	SQLBindCol(hStmt, 5, SQL_C_ULONG, &team_id, 0, &lteam_id);
//	SQLBindCol(hStmt, 6, SQL_C_CHAR, date, sizeof(date), &ldate);
////	SQLBindCol(hStmt, 7, SQL_C_CHAR, team_name, sizeof(team_name), &lteam_name);
//
//	TCHAR sql[256] = TEXT("select * from member");
//
//	if (SQLExecDirect(hStmt, (SQLTCHAR*)sql, SQL_NTS) != SQL_SUCCESS)
//	{
//		return FALSE;
//	}
//
//	for (int i = 0; SQLFetch(hStmt) != SQL_NO_DATA; i++)
//	{
//		MEMBER data;
//		data.mem_id = mem_id;
//		MultiByteToWideChar(CP_ACP, 0, (char*)name, -1, data.mem_name, sizeof(data.mem_name));
//		MultiByteToWideChar(CP_ACP, 0, (char*)gender, -1, data.mem_gender, sizeof(data.mem_gender));
//		MultiByteToWideChar(CP_ACP, 0, (char*)phone, -1, data.mem_phone, sizeof(data.mem_phone));
//		data.team_id = team_id;
//		MultiByteToWideChar(CP_ACP, 0, (char*)date, -1, data.in_date, sizeof(data.in_date));
////		MultiByteToWideChar(CP_ACP, 0, (char*)team_name, -1, data.team_name, sizeof(data.team_name));
//
//		memlist->push_back(data);
//	}
//}

//BOOL mydb_CreateTable()
//{
//	char str[1024] = "create table sb(name varchar2(30byte) not null, snum number(10,0) not null, phone varchar2(20byte), email varchar2(40byte));";
//	if (SQLExecDirect(hStmt, (SQLCHAR *)str, SQL_NTS) != SQL_SUCCESS)
//	{
//		return FALSE;
//	}
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
//BOOL mydb_InsertData(Student *pData)
//{
//	char sql[256];
//	wsprintf(sql, "insert into sb(name,snum,phone,email) values( '%s', '%d', '%s' ,'%s')"
//		, pData->sName.c_str(), pData->sNum, pData->sPhone.c_str(), pData->email.c_str());
//	if (SQLExecDirect(hStmt, (SQLCHAR *)sql, SQL_NTS) != SQL_SUCCESS)
//	{
//		return FALSE;
//	}
//	else
//	{
//		return TRUE;
//	}
//}
//
//
//BOOL mydb_SelectData()
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