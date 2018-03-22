//wbfile.cpp

#include "std.h"

//파일 전송 관련 프로토콜
struct FILE_INFO
{
	TCHAR FilePath[250];	// 전송할 파일 이름.
	TCHAR FileName[50];
	int  size;				// 화일 크기
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
	// 1. 소켓생성
	g_filesocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

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

	if (connect(g_filesocket, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		return false;
	}
	OnLogMessage(TEXT("파일서버 연결..."));

	//CloseHandle(CreateThread(0, 0, wbfile_foo, (void*)g_filesocket, 0, 0));
	//새로운 스레드를 만들어서 서버에서 오는 data를 수신한다
	HANDLE hThread = CreateThread(0, 0, wbfile_foo, (void*)g_filesocket, 0, 0);
	OnLogMessage(TEXT("다된건가?"));
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
		OnLogMessage(TEXT("Can't Open File"));
		closesocket(g_filesocket);
		free(finfo);
		return 0;
	}
	//=========================================================================================================

	//=========================================================================================================
	// 크기를 구하고 화일의 정보를 전송한다.
	DWORD size1=0;//파일 사이즈 저장용
	DWORD size2 = GetFileSize(hFile, &size1);//파일 사이즈 얻기 매개변수에도 들어오고, 리턴값으로도 들어온다

	finfo->size = size2;

	int size = sizeof(FILE_INFO);
	send(g_filesocket, (char*)&size, sizeof(int), 0);//구조체의 사이즈 전송
	send(g_filesocket, (char*)finfo, size, 0);		//구조체 정보 전송
	//-------------------------------------------------실제 파일 전송
	// 화일 전송
	int total = size2; // 전송할 전체 크기
	int current = 0;   // 전송한 크기
	int nRead = 0;
	char buf[4096] = {0};    // 4k 버퍼.

	//
	while (total > current)//보낼 사이즈가 현재 보낸 바이트 수보다 클때
	{
		DWORD len=0; //읽어온 값 길이 저장용
		nRead = ReadFile(hFile, buf, 4096, &len, 0);//리턴 값이 읽어온 바이트 크기

		if (len <= 0) break;

		int nSend = send(g_filesocket, buf, len, 0);//전송
		if (nSend <= 0) break;

		current += nSend;
	}
	if (total != current)   
		OnLogMessage(TEXT("전송에러"));
	else
		OnLogMessage(TEXT("전송완료"));
	//========================================================================
//	closesocket(g_filesocket);
	CloseHandle(hFile);
	free(finfo);

	return 0;
}

// 사용자 정의 데이터 수신 함수
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
	
	// 화일 정보를 수신한다.
	FILE_INFO info = {0};
	int size=0;

	recvn(g_filesocket, (char*)&size, sizeof(int), 0);//구조체사이즈를 받음
	
	recvn(g_filesocket, (char*)&info, sizeof(FILE_INFO), 0);//실제 구조체를 받음
	OnLogMessage(info.FileName);

	// 주스레드에 알려준다. ->주스레드가 UI를 Update 한다.!
	OnLogMessage(TEXT("파일 수신시작...."));
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

		//서버에서 날라오는 파일을 buf에 저장함
		int nRecv = recvn(g_filesocket, buf, info.size, 0);
		if (nRecv <= 0) break;

		//파일 작성
		DWORD len;
		WriteFile(hFile, buf, nRecv, &len, 0);
		
		current += nRecv;
		OnLogMessage(TEXT("파일 수신중..."));
		//PostMessage(hwnd, WM_USER + 200, 0, (LPARAM)current);
	}
	if (current != total) 
		OnLogMessage(TEXT("파일 수신 Error"));
	else
	{
		OnLogMessage(TEXT("파일 수신 Success"));
	}
	
	//closesocket(g_filesocket);
	
	CloseHandle(hFile);
	//WSACleanup();
	OnLogMessage(TEXT("파일 핸들 터졌어"));
	return 0;
}
