//packet.h

// C->S
#define PACK_LOGOUT        1
#define PACK_MINMEMBER     2
#define PACK_ADDMEMBER     3
#define PACK_LOGIN         4
#define PACK_ADDACCOUNT    5
#define PACK_DELACCOUNT    6
#define PACK_ADDMONEY      7
#define PACK_SUBMONEY      8
#define PACK_SHORTMESSAGE  9

//#define PACK_MYACCOUNT      7

// S->C
#define ACK_LOGOUT       10
#define ACK_MINMEMBER     11
#define ACK_ADDMEMBER_S   12
#define ACK_ADDMEMBER_F   13
#define ACK_LOGIN_S      14
#define ACK_LOGIN_F      15
#define ACK_ADDACCOUNT_S      16
#define ACK_ADDACCOUNT_F      17
#define ACK_DELACCOUNT_S      18
#define ACK_DELACCOUNT_F      19
#define ACK_ADDMONEY      20
#define ACK_SUBMONEY_S      21
#define ACK_SUBMONEY_F      22
#define ACK_SHORTMESSAGE  23
//#define ACK_MYACCOUNT_S      22
//#define ACK_MYACCOUNT_F      23

//구조체
typedef struct tagADDMEMBER
{
	int flag;
	TCHAR name[20];
	TCHAR id[20];
	TCHAR pw[20];
}ADDMEMBER;

typedef struct tagLOGIN
{
	int flag;
	TCHAR id[20];
	TCHAR pw[20];
}LOGIN;
typedef struct tagSHORTMESSAGE
{
	int flag;
	TCHAR msg[50];

}SHORTMESSAGE;

typedef struct tagADDACCOUNT
{
	int flag;
	TCHAR id[20];
	int accnum;
	int balance;
	TCHAR date[50];
}ADDACCOUNT;

typedef struct tagDELACCOUNT
{
	int flag;
	TCHAR id[20];
	int accnum;
}DELACCOUNT;

typedef struct tagADDMONEY
{
	int flag;
	int accnum;
	int balance;
	int money;
}ADDMONEY;

typedef struct tagSUBMONEY
{
	int flag;
	int accnum;
	int balance;
	int money;
}SUBMONEY;

//typedef struct tagMYACCOUNT
//{
//   int flag;
//   TCHAR id[20];
//}MYACCOUNT;




//가입(플래그(4), 이름(20), 아이디(20), 패스워드(20))
//로그인(플래그(4)아이디(20), 패스워드(20), 빈공간(20)
//숏매시지(플래그(4)60)
ADDMEMBER pack_SetAddMember(TCHAR*name, TCHAR*id, TCHAR*pw);

ADDMEMBER pack_SetMinMember(TCHAR*name, TCHAR*id, TCHAR*pw);

LOGIN pack_SetLogiin(TCHAR *id, TCHAR *pw);

LOGIN pack_SetLogout(TCHAR *id, TCHAR *);

SHORTMESSAGE pack_SetShortMessage(TCHAR *msg);

ADDACCOUNT pack_SetAddAccount(TCHAR* id, int accnum, int balance, TCHAR* date);

ADDACCOUNT pack_SetDelAccount(TCHAR* id, int accnum, int balance, TCHAR* date);

ADDMONEY pack_SetAddMoney(int accnum, int money);

SUBMONEY pack_SetSubMoney(int accnum, int money);


