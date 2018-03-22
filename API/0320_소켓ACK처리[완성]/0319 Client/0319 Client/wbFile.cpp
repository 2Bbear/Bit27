#include"std.h"

struct FILE_INFO
{
	TCHAR FilePath[250]; // ������ ���� ���
	TCHAR FileName[50];//���� �̸�
	int  size;			// ȭ�� ũ��
};
SOCKET _g_filesocket;

BOOL wbFile_StartClient(TCHAR* ip, int port)
{
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		return false;
	}
	//--------------------------------------------
	// 1. ���ϻ���
	_g_filesocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 2. �����ּ� ���� -> client �� ���� ���� 
	//    ���� �ϸ� OS�� ������ ��Ʈ�� ������ �ش�
	//============== UNICODE -> DBCS ======================
	char _ip[250];
	WideCharToMultiByte(CP_ACP, 0, ip, -1, _ip, 250, NULL, NULL);
	//======================================================
	// 3. ������ ����
	SOCKADDR_IN addr = { 0 };

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(_ip);

	if (connect(_g_filesocket, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		return false;
	}
	OnLogMessage(TEXT("���ϼ��� ����..."));

	//���ο� �����带 ���� �������� ���� data�� �����Ѵ�
	HANDLE hThread = CreateThread(0, 0, wbFile_foo, (void*)_g_filesocket, 0, 0);
	CloseHandle(hThread);
	return true;
}

void wbFile_StopClient()
{
	closesocket(_g_filesocket);
	WSACleanup();
}

void wbFile_SendMessage(TCHAR * _path, TCHAR * _name)
{
	FILE_INFO *info = (FILE_INFO*)malloc(sizeof(FILE_INFO));
	_tcscpy_s(info->FilePath, _path);
	_tcscpy_s(info->FileName, _name);
	info->size = 0;

	CloseHandle(CreateThread(0, 0, FileServer, (void*)&info, 0, 0));
}
// ������ Client���� ������ �����Ѵ�.
DWORD WINAPI FileServer(void* p)
{
	FILE_INFO* finfo = (FILE_INFO*)p;


	// ������ ����Open //file share read �����б� ��� = ������ ���� �� ���� �ְ� ��, ���� ���� �ʰڴٴ� �ǹ�
	HANDLE hFile = CreateFile(finfo->FilePath, GENERIC_READ, FILE_SHARE_READ,
		0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	//�������� Ŀ�� �������� �˻�
	if (hFile == INVALID_HANDLE_VALUE)
	{
		OnLogMessage(TEXT("Cand't Open File"));
		closesocket(_g_filesocket);
		free(finfo);//�̻�
		return 0;
	}
	//=========================================================================================================
	// ũ�⸦ ���ϰ� ȭ���� ������ �����Ѵ�.
	DWORD size1;//���� ������ �����
	DWORD size2 = GetFileSize(hFile, &size1);//���� ������ ��� �Ű��������� ������, ���ϰ����ε� ���´�

	finfo->size = size2;
	int size = sizeof(FILE_INFO);
	send(_g_filesocket,(char *)&size,sizeof(int),0);

	send(_g_filesocket, (char*)&finfo, size, 0); //����
	//-------------------------------------------------
	// ȭ�� ����
	int total = size2; // ������ ��ü ũ��
	int current = 0;   // ������ ũ��
	int nRead = 0;
	char buf[4096];    // 4k ����.

					   //
	while (total > current)//���� ����� ���� ���� ����Ʈ ������ Ŭ��
	{
		DWORD len; //�о�� �� ���� �����
		nRead = ReadFile(hFile, buf, 4096, &len, 0);//���� ���� �о�� ����Ʈ ũ��

		if (len <= 0) break;

		int nSend = send(_g_filesocket, buf, len, 0);//����
		if (nSend <= 0) break;

		current += nSend;
	}
	if (total != current)	OnLogMessage(TEXT("���ۿ���"));
	else					OnLogMessage(TEXT("���ۿϷ�"));

	//closesocket(_g_filesocket);
	CloseHandle(hFile);
	free(finfo);
	return 0;
}



// ����� ���� ������ ���� �Լ�
int wbFile_recvn(SOCKET s, char *buf, int len, int flags)
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

DWORD WINAPI wbFile_foo(void* p)
{// ȭ�� ������ �����Ѵ�.
	FILE_INFO info;
	int size;
	recvn(_g_filesocket, (char*)&size, sizeof(int), 0);
	recvn(_g_filesocket, (char*)&info, sizeof(FILE_INFO), 0);

	// �ֽ����忡 �˷��ش�. ->�ֽ����尡 UI�� Update �Ѵ�.!
	OnLogMessage(TEXT("���� ���Ž���..."));
	//--------------------------------------------
	TCHAR name[260];
	_tcscpy_s(name, info.FileName);   //�����̸� ����

	HANDLE hFile = CreateFile(name, GENERIC_WRITE, FILE_SHARE_READ,
		0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	int total = info.size;
	int current = 0;
	char buf[4096];
	while (total > current)
	{
		int nRecv = recv(_g_filesocket, buf, 4096, 0);
		if (nRecv <= 0) break;

		DWORD len;
		WriteFile(hFile, buf, nRecv, &len, 0);

		current += nRecv;
		OnLogMessage(TEXT("���� ������..."));
	}
	if (current != total)
		OnLogMessage(TEXT("Error"));
	else
		OnLogMessage(TEXT("���� ���� Success"));
	//	closesocket(s);
	CloseHandle(hFile);
	//	WSACleanup();
	return 0;
}

int wbFile(SOCKET s, char * buf, int len, int flags)
{
	return 0;
}

