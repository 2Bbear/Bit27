//wbnet.cpp

#include "std.h"
struct FILE_INFO
{
	TCHAR FilePath[250];	// 전송할 파일 이름.
	TCHAR FileName[50];
	int  size;				// 화일 크기
};


vector<SOCKET> client_list;
HANDLE hThread;
void wbnet_StartServer(int port)
{

	hThread = CreateThread(0, 0, ServerRun, (LPVOID)port, 0, 0);
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

	OnLogMessage(TEXT("클라이언트 대기"));
	//----------------------------------------------------------------------
	
	// 4. 이제 Client 에서 부터 전달된 요청을 허용한다.
	while (1)
	{
		SOCKADDR_IN c_addr;
		int  size = sizeof(c_addr);

		SOCKET c_s = accept(s, (SOCKADDR*)&c_addr, &size);

		OnLogMessage(TEXT("클라이언트 접속"));

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

	char buf[4096] = { 0 };//구조체 받는곳
	char buf2[4096] = { 0 };//실제 파일 받는곳
	//int  nRead = 0;
	int  size;

	while (1)
	{
		memset(buf, 0, 4096);
		memset(buf2, 0, 4096);
		//====================================================================
		int nRead = recvn( s, (char*)&size, sizeof(int), 0);  // 구조체 사이즈
		//if (nRead <= 0) break;
		nRead = recvn(s, (char*)buf, size, 0);//구조체 - 이 안에 파일 사이즈가 있음
												//size는 구조체 사이즈
		nRead = recvn(s, buf2, ((FILE_INFO*)buf)->size, 0);		// 실제 파일
		if (nRead <= 0) break;
		//test 용 수신된 데이터 변경
		buf2[0] = '1';
		//((FILE_INFO*)buf)->FileName[0] = '2';
		//==================================================================

		OnLogMessage(TEXT("파일 수신...."));

		for (int i = 0; i < (int)client_list.size(); ++i)
		{
			if (client_list[i] != s)
			{
				printf(buf2);
			
				send(client_list[i], (char*)&buf, sizeof(int), 0);//구조체 사이즈 전송
				send(client_list[i], buf, sizeof(FILE_INFO), 0);//구조체 전송
				send(client_list[i], buf2, ((FILE_INFO*)buf)->size, 0);//실제파일 전송
				
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
	OnLogMessage(TEXT("클라이언트 종료"));

	closesocket(s);
	return 0;
}

