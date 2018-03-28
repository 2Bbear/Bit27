//mydb.cpp

#include "std.h"

#define DBNAME "test"
#define ID	   "ccm"
#define PW		"ccm"

SQLHSTMT hStmt;
SQLHENV hEnv;
SQLHDBC hDbc;

BOOL mydb_DBConnect()
{

	// 연결 설정을 위한 변수들
	SQLRETURN Ret;

	// 1, 환경 핸들을 할당하고 버전 속성을 설정한다.(p1741)
	if (SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hEnv) != SQL_SUCCESS) 
		return false;
	if (SQLSetEnvAttr(hEnv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER) != SQL_SUCCESS) 
		return false;

	// 2. 연결 핸들을 할당하고 연결한다.
	if (SQLAllocHandle(SQL_HANDLE_DBC,hEnv,&hDbc) != SQL_SUCCESS) 
		return false;
	// 오라클 서버에 연결하기
	Ret=SQLConnect(hDbc,(SQLCHAR *)DBNAME,SQL_NTS,(SQLCHAR *)ID,SQL_NTS,(SQLCHAR *)PW,SQL_NTS);

	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
		return false;

	// 명령 핸들을 할당한다.
	if (SQLAllocHandle(SQL_HANDLE_STMT,hDbc,&hStmt) != SQL_SUCCESS)
		return false;

	return true;
}


BOOL mydb_CreateTable()
{
	char str[1024] ="create table sb(name varchar2(30byte) not null, snum number(10,0) not null, phone varchar2(20byte), email varchar2(40byte));" ;
	if (SQLExecDirect(hStmt,(SQLCHAR *)str,SQL_NTS) != SQL_SUCCESS) 
	{
		return FALSE;
	}
	return TRUE;
}


BOOL mydb_DeleteTable()
{
	char str[256] = "drop table sb";
	if (SQLExecDirect(hStmt,(SQLCHAR *)str,SQL_NTS) != SQL_SUCCESS) 
	{
		return FALSE;
	}
	return TRUE;
}


BOOL mydb_InsertData(Student *pData)
{
	char sql[256];
	wsprintf(sql,"insert into sb(name,snum,phone,email) values( '%s', '%d', '%s' ,'%s')"
			,pData->sName.c_str(),pData->sNum,pData->sPhone.c_str(),pData->email.c_str());
	if (SQLExecDirect(hStmt,(SQLCHAR *)sql,SQL_NTS) != SQL_SUCCESS) 
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


BOOL mydb_SelectData()
{
	SQLCHAR Name[256];

	SQLINTEGER lName,lSnum,lPhone,lEmail;
	int ssnum;

	SQLCHAR Phone[256];
	SQLCHAR Email[256];

	SQLBindCol(hStmt,1,SQL_C_CHAR,Name,sizeof(Name),&lName);
	SQLBindCol(hStmt,2,SQL_C_ULONG,&ssnum,0,&lSnum);
	SQLBindCol(hStmt,3,SQL_C_CHAR,Phone,sizeof(Phone),&lPhone);
	SQLBindCol(hStmt,4,SQL_C_CHAR,Email,sizeof(Email),&lEmail);

	char sql[256]= "select * from sb";

	if(SQLExecDirect(hStmt,(SQLCHAR*)sql,SQL_NTS )!=SQL_SUCCESS)
	{
		return FALSE;
	}	

	char name[21], num[21], phoneNumber[21], email[41];
	int count = 0;
	for(int i=0;SQLFetch(hStmt)!=SQL_NO_DATA;i++)
	{	
		wsprintf(name,"%s",Name);
		wsprintf(num,"%d",ssnum);
		wsprintf(phoneNumber,"%s",Phone);
		wsprintf(email,"%s",Email);

		control_GetData(count++, name, num, phoneNumber, email );
		
	}
	return TRUE;
}

BOOL mydb_DeleteData()
{
	char sql[256];

	wsprintf(sql,"delete sb");
	if (SQLExecDirect(hStmt,(SQLCHAR *)sql,SQL_NTS) != SQL_SUCCESS) 
	{
		return FALSE;
	}
	return TRUE;
}