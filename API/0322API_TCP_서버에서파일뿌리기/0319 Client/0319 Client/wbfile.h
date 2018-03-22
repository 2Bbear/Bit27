//wbfile.h


BOOL wbfile_StartClient(TCHAR* ip, int port);
void wbfile_StopClient();

void wbfile_SendMessage(TCHAR *path, TCHAR *name);

DWORD WINAPI wbfile_foo(void* p);

DWORD WINAPI FileServer(void* p);

int wbfile_recvn(SOCKET s, char *buf, int len, int flags);