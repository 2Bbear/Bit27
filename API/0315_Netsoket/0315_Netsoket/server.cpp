#include <winsock2.h>//���϶��̺귯��
#include <stdio.h>

#define BUFFERSIZE 1024 

// ���� �Լ� ���� ���
void DisplayMessage()
{
	LPVOID pMsg; //
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | // ���� �޽��� ���� �޸𸮸� ���ο��� �Ҵ��϶�
		FORMAT_MESSAGE_FROM_SYSTEM, //�ü���� ���� ���� �޽����� �����´�
		NULL,
		WSAGetLastError(), //���� �ڵ�
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //���(������ ���� ���)
		(LPTSTR)&pMsg, // ���� �޽��� outparam
		0, NULL);

	printf("%s\n", pMsg);// ���� �޽��� ���

	LocalFree(pMsg); // ���� �޽��� ���� �޸� ��ȯ 
}

int main(int argc, char* argv[])
{
	int retval;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����!\n");
		return -1;
	}

	// ��� ���� ����
	SOCKET listenSock;
	listenSock = socket(
		AF_INET, //�ּ�ü��: �������ݸ��� �ּ�ü�� �ٸ�, ���ͳ� ���, IPv4
		SOCK_STREAM, //������������: TCP/IP ��� ���
		0 //�� �� ���ڷ� �������� ������ ��Ȯ�ϸ� 0���, IPPROTO_TCP, IPPROTO_UDP
	);
	if (listenSock == INVALID_SOCKET)
	{
		DisplayMessage();
		return -1;
	}

	// ��� ������ ���� �ּ�, ��Ʈ ����
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr)); // ����ü�� ������ ũ�� ��ŭ ���� 0���� ä���
	serveraddr.sin_family = AF_INET; //�ּ�ü�� Ivp4 =AF_INET
	serveraddr.sin_port = htons(40100); //������Ʈ��ȣ
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); //����IP �ּ� INADDR_ANY= ���� ��ǻ���� ip�ּ�

	retval = bind(listenSock, (SOCKADDR *)&serveraddr, sizeof(serveraddr)); // ���� setting �ϴ� �Լ�
	if (retval == SOCKET_ERROR)//���� �̻��� ���� �� ������
	{
		DisplayMessage();
		return -1;
	}

	// ��� ������ ���� ��� ť ���� �� Ŭ���̾�Ʈ ���� ���
	retval = listen(
		listenSock,
		SOMAXCONN //���Ӵ�� ť�� ũ�� ��� ��ٷ� �޶��� �ǹ�
	); // TCP ���¸� LISTENING ���� // �����·� ��ȯ
	if (retval == SOCKET_ERROR) // ��ũ �������� ���� 
	{
		DisplayMessage();
		return -1;
	}

	// ������ ��ſ� ����� ����========================================
	SOCKET clientSock; //��ſ� ����
	SOCKADDR_IN clientaddr; //���� �ּ��� ������ ���� ����ü
	int addrlen;//��� �ּ� ����
	char buf[BUFFERSIZE]; //��밡 ���� ���ڸ� ���� �迭
	//===================================================================
	while (1) {
		addrlen = sizeof(clientaddr);//�ϴ��� �ʱ�ȭ ���� ������ accpet�� ���������� ����ȴ�
		// ���� ���
		clientSock = accept(
			listenSock,
			(SOCKADDR *)&clientaddr, //Ŭ���̾�Ʈ�� ���� out param
			&addrlen //�ּұ���ü������ũ��, in(ũ������), out(�ʱ�ȭ��ũ���ȯ) param //���� ������ ������ �ƴ϶� ���� �� ȿ�������� �޸𸮸� ����ϱ� ���ؼ�
		); //��ż��� ����: ���� IP, ���� ��Ʈ ����
		if (clientSock == INVALID_SOCKET)
		{
			DisplayMessage();
			continue;
		}
		/*
		clientaddr�� accept�� ���� ��Ʈ��ũ���� �޾ƿ� �������̱⶧���� sin_addr�� �̿��ؼ� host bt order�� ���� ���ְ�,
		inet_ntoa�� �̿��ؼ� ȣ��Ʈ �����͸� ���ڿ��� �ٲ۴�.
		*/
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), //���ڿ��� IP�ּ� ��ȯ , �ּ������� ���ڿ��� /<=> intet_addr(��Ʈ)->���ڷ�
			ntohs(clientaddr.sin_port) // ��Ʈ��ȣ ��Ʈ��ũ ����Ʈ ������ ȣ��Ʈ ����Ʈ ���ķ� ��ȯ 
		);

		// Ŭ���̾�Ʈ�� ������ ���
		while (1) {
			// ������ �ޱ�
			/*
			�Լ��� ����Ǹ鼭 ������ �����
			recv �� �ι���° ������ buf�� 3��° ������ ���� ũ�� ��ŭ ���Ź��� ���� �����Ѵ�,
			��ȯ ������ ���� ������ ��� ���� ���� ���� size�� ��ȯ�Ѵ�.
			*/
			retval = recv(
				clientSock, //��ż����ڵ�
				buf, //���� ���ø����̼� ����
				BUFFERSIZE, //���� ������ �ִ� ũ��
				0 //��κ� 0 or MSG_PEEK�� MSG_OOB�� ��� ����
			);
			if (retval == SOCKET_ERROR)//���� �ڵ� ���� ������ ���
			{  //���� ������ ����
				DisplayMessage();
				break;
			}
			else if (retval == 0)//������ ������ closesocket ���� ��� 0�� server�� �����ϴµ� �� ���̴�.
			{  //���� ���� ����
				DisplayMessage();
				break;
			}
			else {//�������� �����Ͱ� ���ŵ� ���
				// ���� ������ ���
				buf[retval] = '\0';//client ������ �ι��ڸ� ���� ������ ������ ������ ���� �ι��ڸ� �־��ش�.
				printf("[TCP ����] IP �ּ�=%s, ��Ʈ ��ȣ=%d�� ���� �޽���:%s\n",
					inet_ntoa(clientaddr.sin_addr),
					ntohs(clientaddr.sin_port),
					buf);
				/*������ ������
				retval = send(client_sock, buf, retval, 0);
				if (retval==SOCKET_ERROR)
				{
					err_display("send()");
					break;
				}*/
			}
		}

		// ��� ���� �ݱ�
		closesocket(clientSock);//���� ���� ���� �ݱ�
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port));
	}

	// ��� ���� �ݱ�
	closesocket(listenSock);


	WSACleanup();
	return 0;
}
