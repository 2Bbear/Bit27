#pragma once
//wbnet.h
// ����� ���� ������ ���� �Լ�
int recvn(SOCKET s, char *buf, int len, int flags);
BOOL OnMessage(char * _buf, int size);
DWORD WINAPI foo(void* p);
void ServerRun();