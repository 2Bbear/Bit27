//wbfile.cpp

#include "std.h"

//���� ���� ���� ��������
struct FILE_INFO
{
	TCHAR FilePath[250];	// ������ ���� �̸�.
	TCHAR FileName[50];
	int  size;				// ȭ�� ũ��
};

SOCKET g_filesocket;

BOOL wbfile_StartClient(TCHAR* ip, int port)
{
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		return false;
	}
	//--------------------------------------------
	// 1. ���ϻ���
	g_filesocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

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

	if (connect(g_filesocket, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		return false;
	}
	OnLogMessage(TEXT("���ϼ��� ����..."));

	//CloseHandle(CreateThread(0, 0, wbfile_foo, (void*)g_filesocket, 0, 0));
	//���ο� �����带 ���� �������� ���� data�� �����Ѵ�
	HANDLE hThread = CreateThread(0, 0, wbfile_foo, (void*)g_filesocket, 0, 0);
	OnLogMessage(TEXT("�ٵȰǰ�?"));
	CloseHandle(hThread);
	return true;
}

void wbfile_StopClient()
{
	closesocket(g_filesocket);
	WSACleanup();
}


void wbfile_SendMessage(TCHAR *path, TCHAR *name)
{
	FILE_INFO *info = (FILE_INFO*)malloc(sizeof(FILE_INFO));
	_tcscpy_s(info->FilePath, path);
	_tcscpy_s(info->FileName, name);
	info->size = 0;

	CloseHandle(CreateThread(0, 0, FileServer, (void*)info, 0, 0));
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
		OnLogMessage(TEXT("Can't Open File"));
		closesocket(g_filesocket);
		free(finfo);
		return 0;
	}
	//=========================================================================================================

	//=========================================================================================================
	// ũ�⸦ ���ϰ� ȭ���� ������ �����Ѵ�.
	DWORD size1=0;//���� ������ �����
	DWORD size2 = GetFileSize(hFile, &size1);//���� ������ ��� �Ű��������� ������, ���ϰ����ε� ���´�

	finfo->size = size2;

	int size = sizeof(FILE_INFO);
	send(g_filesocket, (char*)&size, sizeof(int), 0);//����ü�� ������ ����
	send(g_filesocket, (char*)finfo, size, 0);		//����ü ���� ����
	//-------------------------------------------------���� ���� ����
	// ȭ�� ����
	int total = size2; // ������ ��ü ũ��
	int current = 0;   // ������ ũ��
	int nRead = 0;
	char buf[4096] = {0};    // 4k ����.

	//
	while (total > current)//���� ����� ���� ���� ����Ʈ ������ Ŭ��
	{
		DWORD len=0; //�о�� �� ���� �����
		nRead = ReadFile(hFile, buf, 4096, &len, 0);//���� ���� �о�� ����Ʈ ũ��

		if (len <= 0) break;

		int nSend = send(g_filesocket, buf, len, 0);//����
		if (nSend <= 0) break;

		current += nSend;
	}
	if (total != current)   
		OnLogMessage(TEXT("���ۿ���"));
	else
		OnLogMessage(TEXT("���ۿϷ�"));
	//========================================================================
//	closesocket(g_filesocket);
	CloseHandle(hFile);
	free(finfo);

	return 0;
}

// ����� ���� ������ ���� �Լ�
int wbfile_recvn(SOCKET s, char *buf, int len, int flags)
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

DWORD WINAPI wbfile_foo(void* p)
{
	
	// ȭ�� ������ �����Ѵ�.
	FILE_INFO info = {0};
	int size=0;

	recvn(g_filesocket, (char*)&size, sizeof(int), 0);//����ü����� ����
	
	recvn(g_filesocket, (char*)&info, sizeof(FILE_INFO), 0);//���� ����ü�� ����
	OnLogMessage(info.FileName);

	// �ֽ����忡 �˷��ش�. ->�ֽ����尡 UI�� Update �Ѵ�.!
	OnLogMessage(TEXT("���� ���Ž���...."));
	//--------------------------------------------
	TCHAR name[260] = {0};
	_tcscpy_s(name, info.FilePath);
	//_tcscpy_s(name,TEXT("D:\\picture\\ddd.txt"));
	OnLogMessage(name);
	/*HANDLE hFile = CreateFile(name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ| FILE_SHARE_WRITE,
		0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);*/
	
	HANDLE hFile = CreateFile(name, GENERIC_WRITE, FILE_SHARE_READ,
	0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	
	
	int total = info.size;
	int current = 0;
	char buf[4096] = {0};
	while (total > current)
	{

		//�������� ������� ������ buf�� ������
		int nRecv = recvn(g_filesocket, buf, info.size, 0);
		if (nRecv <= 0) break;

		//���� �ۼ�
		DWORD len;
		WriteFile(hFile, buf, nRecv, &len, 0);
		
		current += nRecv;
		OnLogMessage(TEXT("���� ������..."));
		//PostMessage(hwnd, WM_USER + 200, 0, (LPARAM)current);
	}
	if (current != total) 
		OnLogMessage(TEXT("���� ���� Error"));
	else
	{
		OnLogMessage(TEXT("���� ���� Success"));
	}
	
	//closesocket(g_filesocket);
	
	CloseHandle(hFile);
	//WSACleanup();
	OnLogMessage(TEXT("���� �ڵ� ������"));
	return 0;
}
