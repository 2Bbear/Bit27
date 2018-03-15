#include <winsock2.h>//소켓라이브러리
#include <stdio.h>

#define BUFFERSIZE 1024 

// 소켓 함수 오류 출력
void DisplayMessage()
{
	LPVOID pMsg; //
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | // 오류 메시지 저장 메모리를 내부에서 할당하라
		FORMAT_MESSAGE_FROM_SYSTEM, //운영체제로 부터 오류 메시지를 가져온다
		NULL,
		WSAGetLastError(), //오류 코드
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //언어(제어판 설정 언어)
		(LPTSTR)&pMsg, // 오류 메시지 outparam
		0, NULL);

	printf("%s\n", pMsg);// 오류 메시지 출력

	LocalFree(pMsg); // 오류 메시지 저장 메모리 반환 
}

int main(int argc, char* argv[])
{
	int retval;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패!\n");
		return -1;
	}

	// 대기 소켓 생성
	SOCKET listenSock;
	listenSock = socket(
		AF_INET, //주소체계: 프로토콜마다 주소체계 다름, 인터넷 사용, IPv4
		SOCK_STREAM, //프로토콜유형: TCP/IP 기반 사용
		0 //앞 두 인자로 프로토콜 결정이 명확하면 0사용, IPPROTO_TCP, IPPROTO_UDP
	);
	if (listenSock == INVALID_SOCKET)
	{
		DisplayMessage();
		return -1;
	}

	// 대기 소켓의 로컬 주소, 포트 설정
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr)); // 구조체를 사이즈 크기 만큼 전부 0으로 채우기
	serveraddr.sin_family = AF_INET; //주소체계 Ivp4 =AF_INET
	serveraddr.sin_port = htons(40100); //지역포트번호
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); //지역IP 주소 INADDR_ANY= 현재 컴퓨터으 ip주소

	retval = bind(listenSock, (SOCKADDR *)&serveraddr, sizeof(serveraddr)); // 소켓 setting 하는 함수
	if (retval == SOCKET_ERROR)//뭔가 이상한 값이 들어가 있으면
	{
		DisplayMessage();
		return -1;
	}

	// 대기 소켓의 접속 대기 큐 생성 및 클라이언트 접속 대기
	retval = listen(
		listenSock,
		SOMAXCONN //접속대기 큐의 크기
	); // TCP 상태를 LISTENING 변경 // 대기상태로 전환
	if (retval == SOCKET_ERROR) // 링크 못했으면 오류 
	{
		DisplayMessage();
		return -1;
	}

	// 데이터 통신에 사용할 변수========================================
	SOCKET clientSock; //통신용 소켓
	SOCKADDR_IN clientaddr; //상대방 주소의 정보를 담을 구조체
	int addrlen;//상대 주소 길이
	char buf[BUFFERSIZE]; //상대가 보낸 문자를 넣을 배열
	//===================================================================
	while (1) {
		addrlen = sizeof(clientaddr);
		// 접속 대기
		clientSock = accept(
			listenSock,
			(SOCKADDR *)&clientaddr, //클라이언트의 정보 out param
			&addrlen //주소구조체형식의크기, in(크기지정), out(초기화한크기반환) param
		); //통신소켓 생성: 원격 IP, 원격 포트 결정
		if (clientSock == INVALID_SOCKET)
		{
			DisplayMessage();
			continue;
		}
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), //문자열로 IP주소 변환 , 주소정수를 문자열로
			ntohs(clientaddr.sin_port) // 포트번호 네트워크 바이트 정렬을 호스트 바이트 정렬로 변환
		);

		// 클라이언트와 데이터 통신
		while (1) {
			// 데이터 받기
			retval = recv(
				clientSock, //통신소켓핸들
				buf, //받을 애플리케이션 버퍼
				BUFFERSIZE, //수신 버퍼의 최대 크기
				0 //대부분 0 or MSG_PEEK와 MSG_OOB를 사용 가능
			);
			if (retval == SOCKET_ERROR)
			{  //소켓 비정상 종료
				DisplayMessage();
				break;
			}
			else if (retval == 0)
			{  //소켓 정상 종료
				DisplayMessage();
				break;
			}
			else {
				// 받은 데이터 출력
				buf[retval] = '\0';
				printf("[TCP 서버] IP 주소=%s, 포트 번호=%d의 받은 메시지:%s\n",
					inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port),
					buf
				);
			}
		}

		// 통신 소켓 닫기
		closesocket(clientSock);
		printf("\n[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));
	}

	// 대기 소켓 닫기
	closesocket(listenSock);


	WSACleanup();
	return 0;
}
