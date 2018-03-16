#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
int main(int argc, char* argv[])
{
	WSADATA wsa;
	//2,2는 버전 매개변수
	//MAKEWORD는 두개의 값을  하나로 뭉치는 매크로

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패!\n");
		return -1;
	}

	printf("윈도우 소켓 초기화 성공!\n");
	//=============================================

	//==========================================
	//사용하지 않게 해제
	WSACleanup();

	return 0;
}
