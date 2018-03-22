#include"std.h"

struct FILE_INFO
{
	TCHAR FilePath[250]; // 전송할 파일 경로
	TCHAR FileName[50];//파일 이름
	int  size;			// 화일 크기
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
	// 1. 소켓생성
	_g_filesocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 2. 소켓주소 지정 -> client 는 생략 가능 
	//    생략 하면 OS가 임의의 포트를 지정해 준다
	//============== UNICODE -> DBCS ======================
	char _ip[250];
	WideCharToMultiByte(CP_ACP, 0, ip, -1, _ip, 250, NULL, NULL);
	//======================================================
	// 3. 서버에 접속
	SOCKADDR_IN addr = { 0 };

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(_ip);

	if (connect(_g_filesocket, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		return false;
	}
	OnLogMessage(TEXT("파일서버 연결..."));

	//새로운 스레드를 만들어서 서버에서 오는 data를 수신한다
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
// 접속한 Client에게 파일을 전송한다.
DWORD WINAPI FileServer(void* p)
{
	FILE_INFO* finfo = (FILE_INFO*)p;


	// 전송할 파일Open //file share read 공유읽기 모드 = 파일을 열고 또 열수 있게 함, 락을 걸지 않겠다는 의미
	HANDLE hFile = CreateFile(finfo->FilePath, GENERIC_READ, FILE_SHARE_READ,
		0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	//정상적인 커널 상태인지 검사
	if (hFile == INVALID_HANDLE_VALUE)
	{
		OnLogMessage(TEXT("Cand't Open File"));
		closesocket(_g_filesocket);
		free(finfo);//이상
		return 0;
	}
	//=========================================================================================================
	// 크기를 구하고 화일의 정보를 전송한다.
	DWORD size1;//파일 사이즈 저장용
	DWORD size2 = GetFileSize(hFile, &size1);//파일 사이즈 얻기 매개변수에도 들어오고, 리턴값으로도 들어온다

	finfo->size = size2;
	int size = sizeof(FILE_INFO);
	send(_g_filesocket,(char *)&size,sizeof(int),0);

	send(_g_filesocket, (char*)&finfo, size, 0); //전송
	//-------------------------------------------------
	// 화일 전송
	int total = size2; // 전송할 전체 크기
	int current = 0;   // 전송한 크기
	int nRead = 0;
	char buf[4096];    // 4k 버퍼.

					   //
	while (total > current)//보낼 사이즈가 현재 보낸 바이트 수보다 클때
	{
		DWORD len; //읽어온 값 길이 저장용
		nRead = ReadFile(hFile, buf, 4096, &len, 0);//리턴 값이 읽어온 바이트 크기

		if (len <= 0) break;

		int nSend = send(_g_filesocket, buf, len, 0);//전송
		if (nSend <= 0) break;

		current += nSend;
	}
	if (total != current)	OnLogMessage(TEXT("전송에러"));
	else					OnLogMessage(TEXT("전송완료"));

	//closesocket(_g_filesocket);
	CloseHandle(hFile);
	free(finfo);
	return 0;
}



// 사용자 정의 데이터 수신 함수
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
{// 화일 정보를 수신한다.
	FILE_INFO info;
	int size;
	recvn(_g_filesocket, (char*)&size, sizeof(int), 0);
	recvn(_g_filesocket, (char*)&info, sizeof(FILE_INFO), 0);

	// 주스레드에 알려준다. ->주스레드가 UI를 Update 한다.!
	OnLogMessage(TEXT("파일 수신시작..."));
	//--------------------------------------------
	TCHAR name[260];
	_tcscpy_s(name, info.FileName);   //파일이름 저장

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
		OnLogMessage(TEXT("파일 수신중..."));
	}
	if (current != total)
		OnLogMessage(TEXT("Error"));
	else
		OnLogMessage(TEXT("파일 수신 Success"));
	//	closesocket(s);
	CloseHandle(hFile);
	//	WSACleanup();
	return 0;
}

int wbFile(SOCKET s, char * buf, int len, int flags)
{
	return 0;
}

