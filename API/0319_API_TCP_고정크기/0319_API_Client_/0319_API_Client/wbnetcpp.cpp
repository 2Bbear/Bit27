#include"std.h"
SOCKET g_socket;




// 사용자 정의 데이터 수신 함수
/*
len 받아야 할 바이트 크기

*/
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
	//0을 반환하면 정상적으로 작동한 것이다
	return (len - left);
}

DWORD WINAPI foo(void* p)
{
	SOCKET s = (SOCKET)p;

	// 서버에서 오는 data를 수신한다.
	char buf[1024];
	int nRead;
	while (1)
	{
		memset(buf, 0, 1024);
		nRead = recv( s, buf, 1024, 0);
		//nRead = recvn(s, buf, 1024, 0);
		//회원가입 정보분기

		//로그인 정보 분기

		if (nRead <= 0) break;

		OnMessage(buf, nRead);
		printf("%s\n", buf);
	}
	OnLogMessage(TEXT("서버와의 접속이 끊어 졌습니다.\n"));

	closesocket(s);
	return 0;
}




BOOL wbnet_StartClient(TCHAR *ip, int port)
{
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		return FALSE;
	
	}
	//--------------------------------------------
	// 1. 소켓생성
	g_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 2. 소켓주소 지정 -> client 는 생략 가능 
	//    생략 하면 OS가 임의의 포트를 지정해 준다
	//====================================UNICOE ->DBCS

	char _ip[250];
	WideCharToMultiByte(CP_ACP, 0, ip, -1, _ip, 250, NULL, NULL);

	//===========================================
	// 3. 서버에 접속
	SOCKADDR_IN addr = { 0 };

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(_ip);

	if (connect(g_socket, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		OnLogMessage(TEXT("서버연결 실패"));
		return FALSE;
	}
	OnLogMessage(TEXT("서버 연결 성공"));
	//printf("Connected Server \n");

	// 새로운 스레드를 만들어서 서버에서 오는 data를 수신한다
	HANDLE hThread = CreateThread(0, 0, foo, (void*)g_socket, 0, 0);
	CloseHandle(hThread);
	return TRUE;

}

void wbnet_StopClient()
{
	closesocket(g_socket);
	//--------------------------------------------
	WSACleanup();

}

void wbnet_SendMessage(TCHAR * msg, int size)
{
	//보내는 목적이라서 뭐가 들어가있든 상관이 없고 그냥 타입만 맞춰주면 된다
	send(g_socket, (char*)msg, size, 0);
}
