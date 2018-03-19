
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>	
#include <winsock2.h>	
#pragma comment(lib, "ws2_32.lib")


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
//recv만 함
DWORD WINAPI foo(void* p)
{
	SOCKET s = (SOCKET)p;

	// 서버에서 오는 data를 수신한다.
	char buf[1024];
	int nRead;
	while (1)
	{
		memset(buf, 0, 1024);
		//		nRead = recv( s, buf, 1024, 0);
		nRead = recvn(s, buf, 1024, 0);

		if (nRead <= 0) break;
		printf("%s\n", buf);
	}
	printf("서버와의 접속이 끊어 졌습니다.\n");
	closesocket(s);
	return 0;
}

//send만 함
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
	// 사용자의 입력을 서버에 전달한다.
	char name[256] = "[자신이름] :JJH";
	char data[256] = { 0 };
	char buf[1024] = { 0 };
	/*
	send 스레드
	receive 스레드
	*/
	while (1)
	{
		memset(buf, 0, 1024);
		memset(data, 0, 256);
		gets_s(data,strlen(data));
		strcpy(buf, name);
		strcat(buf, data);

		// 서버에 전송한다
		send(s, buf, strlen(buf) + 1, 0);	//[홍길동]HI~
	}

	closesocket(s);




	//--------------------------------------------
	WSACleanup();
}














