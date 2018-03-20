#pragma once
BOOL wbnet_StartClient(TCHAR *ip, int port);

void wbnet_StopClient();

void wbnet_SendMessage(TCHAR * msg,int size);

DWORD WINAPI foo(void* p);
int recvn(SOCKET s, char *buf, int len, int flags);