
//[ TCP Client ]
#include <winsock2.h>	
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
#define BUFSIZE 512

// 소켓 함수 오류 출력 후 종료
void err_quit(char *msg);
// 소켓 함수 오류 출력
void err_display(char *msg);

// 사용자 정의 데이터 수신 함수
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

int main(int argc, char* argv[])
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); //주소 체계 , 프로토콜 유형 , 프로토콜 마지막 인자로 IPPROTO_UDP = 결국 어떠한 프로토콜을 쓸것인지 결정
	//
	if (sock == INVALID_SOCKET) // 소켓 생성에 실패했다면
		err_quit("socket()"); //이 함수 자체가 에러가 있다면 강제적으로 프로그램을 종료 시킴

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);//9000
	serveraddr.sin_addr.s_addr = inet_addr("192.168.0.33");
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// 데이터 통신에 사용할 변수
	char buf[BUFSIZE + 1];
	int len;

	// 서버와 데이터 통신
	while (1) {
		// 데이터 입력
		ZeroMemory(buf, sizeof(buf));
		printf("\n[보낼 데이터] ");
		if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;

		// '\n' 문자 제거
		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		// 데이터 보내기
		retval = send(sock, buf, strlen(buf), 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}
		printf("[TCP 클라이언트] %d바이트를 보냈습니다.\n", retval);

		// 데이터 받기
		//recvn(sock, buf, retval, 0);
		retval = recv(sock, buf, retval, 0);
		if (retval == SOCKET_ERROR) {
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		// 받은 데이터 출력
		buf[retval] = '\0';
		printf("[TCP 클라이언트] %d바이트를 받았습니다.\n", retval);
		printf("[받은 데이터] %s\n", buf);
	}

	// closesocket()
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}

// 소켓 함수 오류 출력 후 종료
//api에서 이 코드를 쓰고 싶다면 wsaGet;astError를 getlasterror로 바꿔주면 쓸수 있다.
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(//포맥된 형식으로 문자열을 저장하는 함수
		FORMAT_MESSAGE_ALLOCATE_BUFFER | //동적으로 메모리를 할당해달라는 것, 왜냐면 받는 변수가 pointer여서 , 뭐 안쓰면 그냥 문자열을 저장시킴 , 한마디로 내부적으로 동적메모리를 잡아서 주소값을 반환하는 것.
		//사실 에러 코드 값마다 생성되어지는 문자열을 다를 수 있으므로 동적으로 받는 것이 좀더 의미 있는 코드다
		FORMAT_MESSAGE_FROM_SYSTEM,//시스템에 정의 되어 있는 메세지를 가져와라 라는 메크로
		NULL, WSAGetLastError(), // 전역함수 하나에 소켓 함수의 에러 또 결과 값들을 저장하는 함수가 있다. 즉 뭔가를 만들면 또는 어디선가 문제가 생기면 자동으로 가장 마지막 값을 저장한다, 그냥 getLast error를 치면 window api의 에러를 반환한다
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);//에러코드의 문자열을 lpMsgBuf에 저장함
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCWSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);// 내부적으로 동적 할당을 해제하는 함수
	exit(-1);//자신의 메인 프로그램 종료 함수
}



// 소켓 함수 오류 출력
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}
/*
netstat -a -n 명령 실행 : TCP/IP 네트워크 연결상태 정보 표시 기본 제공됨
-a : 모든 연결정보와 포트변호 표시
-n : IP 주소와 포트번호를 숫자로 표시
1) 서버실행
상태 확인 : 9000  포트번호 상태가 (LISTENING연결대기중)
2) 클라이언트 실행
상태 확인 : 총 3개 ESTABLISHED(연결됨)
=> 서버측에서 만든 소켓은 모두 같은 포트 번호를 사용한다.
3) 글자를 입력하지 않은 상태에서 Enter키를 누르면
클라이언트는 종료한다.
상태확인 : TIME_WAIT 상태인 포트(1502)가 존재한다.
4) 약 5분 후 다시 상태 확인
TIME_OUT 상태인 포트는 사라지고
처음과 동일한 결과를 보게 된다.
5) 클라이언트를 다시 실행하여 데이터를 몇개 보낸 후
Ctrl+C를 눌러 강제 종료 해보자.
상태확인  : 최초 대기 서버 소켓만 존재한다.
*/