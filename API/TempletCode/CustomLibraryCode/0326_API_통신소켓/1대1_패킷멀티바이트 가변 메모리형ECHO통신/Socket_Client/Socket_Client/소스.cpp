/*
���ǻ���
1. ������ �޴� ������� paket���� �����ؼ� size�� �ȹٷ� ������
 - ���� ����� �� ������ ��� ���ʿ��� �޴°ų� ������ ���� �ȵȴ�.



*/
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>	
#include <winsock2.h>	
#pragma comment(lib, "ws2_32.lib")
using namespace std;

#include "packet.h"


// ����� ���� ������ ���� �Լ�
int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}

DWORD WINAPI foo(void* p)
{
	SOCKET s = (SOCKET)p;

	// �������� ���� data�� �����Ѵ�.
	char buf[PACK_MAXSIZE];
	int nRead;
	while (1)
	{
		memset(buf, 0, PACK_MAXSIZE);
		//		nRead = recv( s, buf, 1024, 0);
		nRead = recvn(s, buf, PACK_MAXSIZE, 0);

		if (nRead <= 0) break;
		printf("%s\n", buf);
	}
	printf("�������� ������ ���� �����ϴ�.\n");
	closesocket(s);
	return 0;
}
void main()
{
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		printf("Can't Initialize Socket !\n");
		return;
	}
	//--------------------------------------------
	// 1. ���ϻ���
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	// 2. �����ּ� ���� -> client �� ���� ���� 
	//    ���� �ϸ� OS�� ������ ��Ʈ�� ������ �ش�

	// 3. ������ ����
	SOCKADDR_IN addr = { 0 };

	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	addr.sin_addr.s_addr = inet_addr("192.168.0.33");

	if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		printf("Can't Connect Server\n");
		return;
	}
	printf("Connected Server \n");

	// ���ο� �����带 ���� �������� ���� data�� �����Ѵ�
	HANDLE hThread = CreateThread(0, 0, foo, (void*)s, 0, 0);
	CloseHandle(hThread);

	//-----------------------------------------------

	
	int check = 0;

	// ������� �Է��� ������ �����Ѵ�.
	while (1)
	{
		
		//��Ŷ �ʱ�ȭ ����
		PACKET data = { 0 };
	
		//����ڷ� ���� �Է¹ޱ�
		char str[244];
		memset(str,0,sizeof(str));
		gets_s(str);
		
		if (check==0)
		{
			//�����Ҵ�
			data.buf = (char*)malloc(strlen(str));
			check++;
		}
		else
		{
			data.buf = (char*)realloc(data.buf, strlen(str));
		}
	
		
		//�Է¹��� ���� ��Ű¡
		pack_DataSetting(&data, str);
	
		//int datasize = data.packsize;
		int datta = strlen(data.buf);
	
		send(s, (char*)&datta, sizeof(int), 0);
		send(s, data.buf,strlen(data.buf),0);
		
		// ������ �����Ѵ�
		//send(s, (char*)&datasize, sizeof(int), 0);	//����ü ������ ����
		//send(s, (char*)&data, data.packsize, 0);	//����ü ����
		printf("����\n");

		
	}
	closesocket(s);
	



	//--------------------------------------------
	WSACleanup();
}

/*
�����Ҵ��ؼ� ������ �ȵǳ�.


*/












