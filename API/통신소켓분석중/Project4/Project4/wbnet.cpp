#include"std.h"


#define PORT	9000

vector<SOCKET> client_list;

//��� �޼��� ó�� �Լ�
BOOL OnMessage(char * _buf,int size)
{
	//flag�� �о����
	int *p = (int*)_buf;
	//�޼��� �м�
	if (*p==1)
	{
		printf("1 ��Ŷ ���� Ȯ�� \n");
	}
	if (*p == 2)
	{
		printf("2 ��Ŷ ���� Ȯ�� \n");
	}
	if (*p == 3)
	{
		printf("3 ��Ŷ ���� Ȯ�� \n");
	}
	return FALSE;
}

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

//���ź�
DWORD WINAPI foo(void* p)
{
	SOCKET s = (SOCKET)p;

	char buf[1024] = { 0 };
	int  nRead = 0;

	while (1)
	{
		memset(buf, 0, 1024);

		//		int nRead = recv( s, buf, 1024, 0);
		int nRead = recvn(s, buf, 1024, 0);
		printf("%s\n", buf);
		if (nRead <= 0) break;

		OnMessage(buf,nRead);


		// ���� data�� list �� �ִ� ��� client���� ������.
		for (int i = 0; i < client_list.size(); ++i)
		{
			//if (client_list[i] != s)
				send(client_list[i], buf, nRead, 0);
		}
	}

	// ������ ���� �� ��� list ���� �����Ѵ�.
	for (int i = 0; i < client_list.size(); ++i)
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
//���ۺ�
void ServerRun()
{
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		printf("Can't Initialize Socket !\n");
		return;
	}
	//--------------------------------------------
	// 1. socket ���� : TCP : SOCK_STREAM     UDP : SOCK_DGRAM
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 2. ������ ���Ͽ� �ּҸ� ����
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;		 // �ּ� ����(AF_INET : IP �ּҶ�� �ǹ�)
	addr.sin_port = htons(PORT); // Port #
	addr.sin_addr.s_addr = htonl(INADDR_ANY);	// �ڽ��� ��� IP ��� 

	if (bind(s, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		printf("Can't bind \n"); return;
	}




	// 3. ������ ��� ���·� ��ȯ�Ѵ�.
	if (listen(s, 5) == -1)
	{
		printf("Can't Listen\n"); return;
	}
	printf("Ŭ���̾�Ʈ�� ����մϴ�. \n");
	//----------------------------------------------------------------------



	// 4. ���� Client ���� ���� ���޵� ��û�� ����Ѵ�.
	while (1)
	{
		SOCKADDR_IN c_addr;
		int  size = sizeof(c_addr);

		SOCKET c_s = accept(s, (SOCKADDR*)&c_addr, &size);

		printf("Ŭ���̾�Ʈ �� �����߽��ϴ�. IP : %s\n",
			inet_ntoa(c_addr.sin_addr));

		// linked list �� socket�� �ִ´�.
		client_list.push_back(c_s);

		// ���ο� �����带 �����ؼ� Ŭ���� ��Ʈ�� ��û�� ó���Ѵ�.
		HANDLE hThread = CreateThread(0, 0, foo, (void*)c_s, 0, 0);
		CloseHandle(hThread);
	}
	printf("���� ����");
	//--------------------------------------------
	closesocket(s); // ���� �ݱ�.
	WSACleanup();
}


void main()
{
	ServerRun();
}









