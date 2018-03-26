#include "packet.h"
#include <string.h>
#include <stdlib.h>
void pack_DataSetting(PACKET * pack, char * _buf)
{
	//flag 설정
	pack->flag = SEND_DATA;
	//버퍼 복사
	pack->buf = _buf;
	//버퍼사이즈 값 설정
	//pack->bufsize = strlen(_buf);
	pack->bufsize = (strlen(_buf) < 4 ? 4 : strlen(_buf));
	//pack사이즈 설정
	pack->packsize = pack->bufsize + 4 + 4 + 4;//buf값 flag값 bufsize값 packsize값 

}
