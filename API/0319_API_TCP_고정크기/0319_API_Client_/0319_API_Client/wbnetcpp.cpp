#include"std.h"
SOCKET g_socket;




// ����� ���� ������ ���� �Լ�
/*
len �޾ƾ� �� ����Ʈ ũ��

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
	//0�� ��ȯ�ϸ� ���������� �۵��� ���̴�
	return (len - left);
}

DWORD WINAPI foo(void* p)
{
	SOCKET s = (SOCKET)p;

	// �������� ���� data�� �����Ѵ�.
	char buf[1024];
	int nRead;
	while (1)
	{
		memset(buf, 0, 1024);
		nRead = recv( s, buf, 1024, 0);
		//nRead = recvn(s, buf, 1024, 0);
		//ȸ������ �����б�

		//�α��� ���� �б�

		if (nRead <= 0) break;

		OnMessage(buf, nRead);
		printf("%s\n", buf);
	}
	OnLogMessage(TEXT("�������� ������ ���� �����ϴ�.\n"));

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
	// 1. ���ϻ���
	g_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 2. �����ּ� ���� -> client �� ���� ���� 
	//    ���� �ϸ� OS�� ������ ��Ʈ�� ������ �ش�
	//====================================UNICOE ->DBCS

	char _ip[250];
	WideCharToMultiByte(CP_ACP, 0, ip, -1, _ip, 250, NULL, NULL);

	//===========================================
	// 3. ������ ����
	SOCKADDR_IN addr = { 0 };

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(_ip);

	if (connect(g_socket, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		OnLogMessage(TEXT("�������� ����"));
		return FALSE;
	}
	OnLogMessage(TEXT("���� ���� ����"));
	//printf("Connected Server \n");

	// ���ο� �����带 ���� �������� ���� data�� �����Ѵ�
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
	//������ �����̶� ���� ���ֵ� ����� ���� �׳� Ÿ�Ը� �����ָ� �ȴ�
	send(g_socket, (char*)msg, size, 0);
}
