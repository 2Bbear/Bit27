#include"std.h"

vector<SOCKET> client_list;

void wbnet_StartServer(int _port)
{
	HANDLE hThread;
	hThread=CreateThread(0,0,ServerRun,(LPVOID)_port,0,0);
	CloseHandle(hThread);
}
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

	char buf[1024] = { 0 };
	int  nRead = 0;

	while (1)
	{
		memset(buf, 0, 1024);

		int nRead = recv( s, buf, 1024, 0);
		//int nRead = recvn(s, buf, 1024, 0);
		printf("%s\n", buf);//=====================================================
		if (nRead <= 0) break;
		OnMessage(buf, nRead);
		// 받은 data를 list 에 있는 모든 client에게 보낸다.
		for (int i = 0; i < (int)client_list.size(); ++i)
		{
			if (client_list[i] != s)
				send(client_list[i], buf, nRead, 0);
		}
	}

	// 접속이 끊어 진 경우 list 에서 제거한다.
	for (int i = 0; i <(int) client_list.size(); ++i)
	{
		if (client_list[i] == s)
		{
			vector<SOCKET>::iterator p = client_list.begin();
			p = p + i;
			client_list.erase(p);
			break;
		}
	}
	closesocket(s);
	return 0;
}


DWORD __stdcall ServerRun(LPVOID value)
{
	int port = (int)value;
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		MessageBox(0, TEXT("Can't Initialize Socket !\n"),TEXT("에러"),0);
		return 0;
	}
	//--------------------------------------------
	// 1. socket 생성 : TCP : SOCK_STREAM     UDP : SOCK_DGRAM
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 2. 생성된 소켓에 주소를 지정
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;		 // 주소 종류(AF_INET : IP 주소라는 의미)
	addr.sin_port = htons(port); // Port #
	addr.sin_addr.s_addr = htonl(INADDR_ANY);	// 자신의 모든 IP 사용 

	if (bind(s, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		MessageBox(0, TEXT("Can't bind \n"), TEXT("에러"), 0);
		return 0;
	}




	// 3. 소켓을 대기 상태로 전환한다.
	if (listen(s, 5) == -1)
	{
		MessageBox(0, TEXT("Can't Listen\n"), TEXT("에러"), 0);
		return 0;
	}
	OnLogMessage(TEXT("클라이언트를 대기합니다."));//뒤에 개행 붙이면 안됨
	//----------------------------------------------------------------------



	// 4. 이제 Client 에서 부터 전달된 요청을 허용한다.
	while (1)
	{
		SOCKADDR_IN c_addr;
		int  size = sizeof(c_addr);

		SOCKET c_s = accept(s, (SOCKADDR*)&c_addr, &size);

		//printf("클라이언트 가 접속했습니다. IP : %s\n",inet_ntoa(c_addr.sin_addr));
		OnClientLogMessage(1, inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port));
		// linked list 에 socket을 넣는다.
		client_list.push_back(c_s);

		// 새로운 스레드를 생성해서 클라이 언트의 요청을 처리한다.
		HANDLE hThread = CreateThread(0, 0, foo, (void*)c_s, 0, 0);
		CloseHandle(hThread);
	}

	//--------------------------------------------
	closesocket(s); // 소켓 닫기.
	WSACleanup();

	return 0;
}