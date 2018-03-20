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
										TEXT("����"), MB_OK);
		return -1;
	}
	//--------------------------------------------
	// 1. socket ���� : TCP : SOCK_STREAM     UDP : SOCK_DGRAM
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 2. ������ ���Ͽ� �ּҸ� ����
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;		 // �ּ� ����(AF_INET : IP �ּҶ�� �ǹ�)
	addr.sin_port = htons(port); // Port #
	addr.sin_addr.s_addr = htonl(INADDR_ANY);	// �ڽ��� ��� IP ��� 

	if (bind(s, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		MessageBox(0, TEXT("Can't bind"),TEXT("����"), MB_OK);
		return -1;
	}

	// 3. ������ ��� ���·� ��ȯ�Ѵ�.
	if (listen(s, 5) == -1)
	{
		MessageBox(0, TEXT("Can't Listen"), TEXT("����"), MB_OK);
		return -1;
	}

	OnLogMessage(TEXT("Ŭ���̾�Ʈ�� ����մϴ�."));
	//----------------------------------------------------------------------
	
	// 4. ���� Client ���� ���� ���޵� ��û�� ����Ѵ�.
	while (1)
	{
		SOCKADDR_IN c_addr;
		int  size = sizeof(c_addr);

		SOCKET c_s = accept(s, (SOCKADDR*)&c_addr, &size);

		OnClientLogMessage(1, inet_ntoa(c_addr.sin_addr),
			ntohs(c_addr.sin_port));

		// linked list �� socket�� �ִ´�.
		client_list.push_back(c_s);

		// ���ο� �����带 �����ؼ� Ŭ���� ��Ʈ�� ��û�� ó���Ѵ�.
		HANDLE hThread = CreateThread(0, 0, foo, (void*)c_s, 0, 0);
		CloseHandle(hThread);
	}

	//--------------------------------------------
	closesocket(s); // ���� �ݱ�.
	WSACleanup();
	return 0;
}

// ����� ���� ������ ���� �Լ�
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
			// ���� data�� list �� �ִ� ��� client���� ������. Send All!!!!!!!!!!!!!!!!!!
			for (int i = 0; i < (int)client_list.size(); ++i)
			{
				//if (client_list[i] != s)
				send(client_list[i], (char*)&size, sizeof(int), 0);
				send(client_list[i], buf, size, 0);
			}
		}

		
	}

	// ������ ���� �� ��� list ���� �����Ѵ�.
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
