#include "packet.h"
#include <string.h>
#include <stdlib.h>
void pack_DataSetting(PACKET * pack, char * _buf)
{
	//flag ����
	pack->flag = SEND_DATA;
	//���� ����
	pack->buf = _buf;
	//���ۻ����� �� ����
	//pack->bufsize = strlen(_buf);
	pack->bufsize = (strlen(_buf) < 4 ? 4 : strlen(_buf));
	//pack������ ����
	pack->packsize = pack->bufsize + 4 + 4 + 4;//buf�� flag�� bufsize�� packsize�� 

}
