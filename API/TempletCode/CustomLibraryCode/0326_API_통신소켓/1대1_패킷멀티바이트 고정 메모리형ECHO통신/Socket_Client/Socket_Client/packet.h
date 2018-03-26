#pragma once
#define PACK_MAXSIZE 4096

//
#define SEND_DATA 1

#define REPLY_DATA_S 100;
#define REPLY_DATA_F 101;

//

typedef struct tagPACKET
{
	int flag;
	char buf[1024];
	int bufsize;
	int packsize;
}PACKET;

void pack_DataSetting(PACKET * pack, char * _buf);