#include "packet.h"
#include <string.h>
#include <stdlib.h>
void pack_DataSetting(PACKET * pack, char * _buf)
{
	//flag ����
	pack->flag = SEND_DATA;
	//���� ����
	strcpy_s(pack->buf, sizeof(pack->buf), _buf);

	//������ �� ����
	pack->bufsize = sizeof(_buf) ;//buf�� flag�� size��
	//pack������ ����
	pack->packsize = sizeof(_buf) + 4 + 4+4;//buf�� flag�� size��



}
