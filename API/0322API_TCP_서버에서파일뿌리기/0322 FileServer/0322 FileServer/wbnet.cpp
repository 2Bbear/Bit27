//wbnet.cpp

#include "std.h"
struct FILE_INFO
{
	TCHAR FilePath[250];	// ������ ���� �̸�.
	TCHAR FileName[50];
	int  size;				// ȭ�� ũ��
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

	OnLogMessage(TEXT("Ŭ���̾�Ʈ ���"));
	//----------------------------------------------------------------------
	
	// 4. ���� Client ���� ���� ���޵� ��û�� ����Ѵ�.
	while (1)
	{
		SOCKADDR_IN c_addr;
		int  size = sizeof(c_addr);

		SOCKET c_s = accept(s, (SOCKADDR*)&c_addr, &size);

		OnLogMessage(TEXT("Ŭ���̾�Ʈ ����"));

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

	char buf[4096] = { 0 };//����ü �޴°�
	char buf2[4096] = { 0 };//���� ���� �޴°�
	//int  nRead = 0;
	int  size;

	while (1)
	{
		memset(buf, 0, 4096);
		memset(buf2, 0, 4096);
		//====================================================================
		int nRead = recvn( s, (char*)&size, sizeof(int), 0);  // ����ü ������
		//if (nRead <= 0) break;
		nRead = recvn(s, (char*)buf, size, 0);//����ü - �� �ȿ� ���� ����� ����
												//size�� ����ü ������
		nRead = recvn(s, buf2, ((FILE_INFO*)buf)->size, 0);		// ���� ����
		if (nRead <= 0) break;
		//test �� ���ŵ� ������ ����
		buf2[0] = '1';
		//((FILE_INFO*)buf)->FileName[0] = '2';
		//==================================================================

		OnLogMessage(TEXT("���� ����...."));

		for (int i = 0; i < (int)client_list.size(); ++i)
		{
			if (client_list[i] != s)
			{
				printf(buf2);
			
				send(client_list[i], (char*)&buf, sizeof(int), 0);//����ü ������ ����
				send(client_list[i], buf, sizeof(FILE_INFO), 0);//����ü ����
				send(client_list[i], buf2, ((FILE_INFO*)buf)->size, 0);//�������� ����
				
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
	OnLogMessage(TEXT("Ŭ���̾�Ʈ ����"));

	closesocket(s);
	return 0;
}

