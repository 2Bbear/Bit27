#pragma once
//wbnet.h
// 사용자 정의 데이터 수신 함수
int recvn(SOCKET s, char *buf, int len, int flags);
BOOL OnMessage(char * _buf, int size);
DWORD WINAPI foo(void* p);
void ServerRun();