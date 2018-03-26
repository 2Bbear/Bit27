#include "packet.h"
#include <string.h>
#include <stdlib.h>
void pack_DataSetting(PACKET * pack, char * _buf)
{
	//flag 설정
	pack->flag = SEND_DATA;
	//버퍼 복사
	strcpy_s(pack->buf, sizeof(pack->buf), _buf);

	//사이즈 값 설정
	pack->bufsize = sizeof(_buf) ;//buf값 flag값 size값
	//pack사이즈 설정
	pack->packsize = sizeof(_buf) + 4 + 4+4;//buf값 flag값 size값



}
