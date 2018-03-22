//wbnet.h

void wbnet_StartServer(int port);

DWORD  __stdcall ServerRun(LPVOID port);

DWORD WINAPI foo(void* p);

int recvn(SOCKET s, char *buf, int len, int flags);