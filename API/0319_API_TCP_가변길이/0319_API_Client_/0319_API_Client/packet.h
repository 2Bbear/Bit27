#pragma once

#define PACK_ADDMEMBER 1
#define PACK_LOGIN  2
#define PACK_SHORTMESSAGE 3

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

typedef struct taSHORTMESSAGE
{
	int flag;
	TCHAR rest[100];

}SHORTMESSAGE;

//ȸ������
ADDMEMBER  pack_SetAddMember(TCHAR * _name,TCHAR *_id,TCHAR * _password);
//�α���
LOGIN pack_SetLoginData(TCHAR *_id, TCHAR * _password);
//���޼���
SHORTMESSAGE pack_SetShortMessage();