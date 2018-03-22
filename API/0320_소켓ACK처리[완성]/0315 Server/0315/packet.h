//packet.h
// C -> S
#define PACK_ADDMEMBER  	1
#define PACK_LOGIN			2
#define PACK_SHORTMESSAGE	3
#define PACK_LOGOUT			4
#define PACK_MINMEMBER		5

// S -> C
#define ACK_ADDMEMBER_S		11
#define ACK_ADDMEMBER_F		12
#define ACK_LOGIN_S			13
#define ACK_LOGIN_F			14
#define ACK_SHORTMESSAGE	15
#define ACK_LOGOUT			16
#define ACK_MINMEMBER		17

typedef struct tagADDMEMBER
{
	int  flag;
	TCHAR name[20];
	TCHAR id[20];
	TCHAR pw[20];
}ADDMEMBER;

typedef struct tagLOGIN
{
	int  flag;
	TCHAR id[20];
	TCHAR pw[20];
}LOGIN;

typedef struct tagSHORTMESSAGE
{
	int  flag;
	TCHAR msg[100];
}SHORTMESSAGE;



//가입(플래그(4), 이름(20), 아이디(20), 패스워드(20))
//로그인(플래그(4)아이디(20), 패스워드(20), 빈공간(20)
//숏매시지(플래그(4)60)

