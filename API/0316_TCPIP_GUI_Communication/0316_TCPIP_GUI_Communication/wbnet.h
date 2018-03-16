#pragma once
void wbnet_StartServer(int _port);

DWORD __stdcall ServerRun(LPVOID port);

DWORD WINAPI foo(void* p);
int recvn(SOCKET s, char *buf, int len, int flags);