/*
주의사항
1. 보내고 받는 사이즈는 paket으로 지정해서 size로 똑바로 보내자
 - 서로 사이즈가 안 맞으면 어느 한쪽에서 받는거나 보내는 것이 안된다.



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


// 사용자 정의 데이터 수신 함수
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

	// 서버에서 오는 data를 수신한다.
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
	printf("서버와의 접속이 끊어 졌습니다.\n");
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
	// 1. 소켓생성
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	// 2. 소켓주소 지정 -> client 는 생략 가능 
	//    생략 하면 OS가 임의의 포트를 지정해 준다

	// 3. 서버에 접속
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

	// 새로운 스레드를 만들어서 서버에서 오는 data를 수신한다
	HANDLE hThread = CreateThread(0, 0, foo, (void*)s, 0, 0);
	CloseHandle(hThread);

	//-----------------------------------------------

	
	int check = 0;

	// 사용자의 입력을 서버에 전달한다.
	while (1)
	{
		
		//패킷 초기화 선언
		PACKET data = { 0 };
	
		//사용자로 부터 입력받기
		char str[244];
		memset(str,0,sizeof(str));
		gets_s(str);
		
		if (check==0)
		{
			//동적할당
			data.buf = (char*)malloc(strlen(str));
			check++;
		}
		else
		{
			data.buf = (char*)realloc(data.buf, strlen(str));
		}
	
		
		//입력받은 값을 패키징
		pack_DataSetting(&data, str);
	
		//int datasize = data.packsize;
		int datta = strlen(data.buf);
	
		send(s, (char*)&datta, sizeof(int), 0);
		send(s, data.buf,strlen(data.buf),0);
		
		// 서버에 전송한다
		//send(s, (char*)&datasize, sizeof(int), 0);	//구조체 사이즈 전송
		//send(s, (char*)&data, data.packsize, 0);	//구조체 전송
		printf("보냄\n");

		
	}
	closesocket(s);
	



	//--------------------------------------------
	WSACleanup();
}

/*
동적할당해서 전달이 안되네.


*/












