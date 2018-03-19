//wbnet.cpp

#include "std.h"

vector<SOCKET> client_list;

void wbnet_StartServer(int port)
{
	
	HANDLE hThread;
	hThread = CreateThread(0, 0, ServerRun, (LPVOID)port, 0, 0);
	CloseHandle(hThread); // ???????
}


DWORD  __stdcall ServerRun(LPVOID value)
{
	int port = (int)value;
	WSADATA wsadata;
	//DLL �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		printf("Can't Initialize Socket !");
		//MessageBox(0, TEXT("Can't Initialize Socket !"),TEXT("����"), MB_OK);
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
		printf("Can't bind");
		//MessageBox(0, TEXT("Can't bind"), TEXT("����"), MB_OK);
		return -1;
	}

	// 3. ������ ��� ���·� ��ȯ�Ѵ�.
	if (listen(s, 5) == -1)
	{
		printf("Can't Listen");
		//MessageBox(0, TEXT("Can't Listen"), TEXT("����"), MB_OK);
		return -1;
	}
	printf("Ŭ���̾�Ʈ�� ����մϴ�.");
	OnLogMessage(TEXT("Ŭ���̾�Ʈ�� ����մϴ�."));
	//----------------------------------------------------------------------

	// 4. ���� Client ���� ���� ���޵� ��û�� ����Ѵ�.
	while (1)
	{
		SOCKADDR_IN c_addr;
		int  size = sizeof(c_addr);

		SOCKET c_s = accept(s, (SOCKADDR*)&c_addr, &size);

		OnClientLogMessage(1, inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port));

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
	//�� ����Ʈ�� �о� ���� �ش� ���� �������� ���� �˻��� ����,�о� ���� ����Ʈ ���� ������ ��
	int received;
	//���� ���۸� �ּҰ����� ����
	char *ptr = buf;
	//�� �о�� ����, ���� ������ ���̷� ������
	int left = len;

	while (left > 0)
	{
		//���Ͽ��� data �о����, �о���� ����Ʈ ���� received�� ���� 
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0) // ���̻� �о� �� ���� ���� ���
			break;
		left -= received;//�о���� ũ�⸦ �� �о�;� �� ���̿��� ��
		ptr += received;//���� �����͵��� ���� ���� �ּҸ� ������
	}

	return (len - left); //�� ���� - �о�� �� ���� ���� 0 �� ���°� ���� �� ���� ���� ���� ������ ����
}


DWORD WINAPI foo(void* p)
{
	SOCKET s = (SOCKET)p;

	char buf[1024] = { 0 };
	int  nRead = 0;
	
	while (1)
	{
		
		memset(buf, 0, 1024);

		//int nRead = recv( s, buf, 1024, 0);
		int nRead = recvn(s, buf, sizeof(RECTPRINT), 0);
		if (nRead <= 0) break; // 0�̳� -1 ���̶�� ������ ������ �ش� ������ �ı� �ؾ���

							   //�ƴ϶�� �����۵�
		//============================================================= ���� �۾� ��
		OnMessage(buf, nRead);
		// ���� data�� list �� �ִ� ��� client���� ������.
		for (int i = 0; i < (int)client_list.size(); ++i)
		{
			
			if (client_list[i] == s)
			{
				send(client_list[i], buf, nRead, 0); printf("������");
			}
			
		}
		//=============================================================
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
