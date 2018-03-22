#pragma once
//wbnet.h

BOOL wbFile_StartClient(TCHAR* ip, int port);
void wbFile_StopClient();

void wbFile_SendMessage(TCHAR * _path,TCHAR * _name);

DWORD WINAPI wbFile_foo(void* p);

DWORD WINAPI FileServer(void* p);
int wbFile(SOCKET s, char *buf, int len, int flags);