#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
int main(int argc, char* argv[])
{
	WSADATA wsa;
	//2,2�� ���� �Ű�����
	//MAKEWORD�� �ΰ��� ����  �ϳ��� ��ġ�� ��ũ��

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����!\n");
		return -1;
	}

	printf("������ ���� �ʱ�ȭ ����!\n");
	//=============================================

	//==========================================
	//������� �ʰ� ����
	WSACleanup();

	return 0;
}
