//wbnet.cpp

#include "std.h"

vector<SOCKET> client_list;

void wbnet_StartServer(int port)
{
	HANDLE hThread;
	hThread = CreateThread(0, 0, ServerRun, (LPVOID)port, 0, 0);
	CloseHandle(hThread);
}


DWORD  __stdcall ServerRun(LPVOID value)
{
	int port = (int)value;
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		MessageBox(0,TEXT("Can't Initialize Socket !"), 
										TEXT("에러"), MB_OK);
		return -1;
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
		MessageBox(0, TEXT("Can't bind"),TEXT("에러"), MB_OK);
		return -1;
	}

	// 3. 소켓을 대기 상태로 전환한다.
	if (listen(s, 5) == -1)
	{
		MessageBox(0, TEXT("Can't Listen"), TEXT("에러"), MB_OK);
		return -1;
	}

	OnLogMessage(TEXT("클라이언트를 대기합니다."));
	//----------------------------------------------------------------------
	
	// 4. 이제 Client 에서 부터 전달된 요청을 허용한다.
	while (1)
	{
		SOCKADDR_IN c_addr;
		int  size = sizeof(c_addr);

		SOCKET c_s = accept(s, (SOCKADDR*)&c_addr, &size);

		OnClientLogMessage(1, inet_ntoa(c_addr.sin_addr),
			ntohs(c_addr.sin_port));

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

// 사용자 정의 데이터 수신 함수
int recvn(SOCKET s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0){
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
	int  size;
	while (1)
	{
		memset(buf, 0, 1024);
		//====================================================================
		int nRead = recvn( s, (char*)&size, sizeof(int), 0);
		if (nRead <= 0) break;
		nRead = recvn(s, buf, size, 0);		
		if (nRead <= 0) break;
		//==================================================================

		OnMessage(buf, nRead);
		
		BOOL bCheck = OnMessage(buf,nRead);
		//[Send one]
		if (bCheck)
		{
			send(s,(char*)&size,sizeof(int),0);
			send(s,buf,size,0);
		}
		else
		{
			// 받은 data를 list 에 있는 모든 client에게 보낸다. Send All!!!!!!!!!!!!!!!!!!
			for (int i = 0; i < (int)client_list.size(); ++i)
			{
				//if (client_list[i] != s)
				send(client_list[i], (char*)&size, sizeof(int), 0);
				send(client_list[i], buf, size, 0);
			}
		}

		
	}

	// 접속이 끊어 진 경우 list 에서 제거한다.
	for (int i = 0; i < (int)client_list.size(); ++i)
	{
		if (client_list[i] == s)
		{
			vector<SOCKET>::iterator p = client_list.begin();
			p = p + i;
			client_list.erase(p);
			break;
		}
	}

	SOCKADDR_IN c_addr;
	int length = sizeof(c_addr);
	getpeername(s, (SOCKADDR*)&c_addr, &length);
	OnClientLogMessage(0, inet_ntoa(c_addr.sin_addr),
		ntohs(c_addr.sin_port));

	closesocket(s);
	return 0;
}
