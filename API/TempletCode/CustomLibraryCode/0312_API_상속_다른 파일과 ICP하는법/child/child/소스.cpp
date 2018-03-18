#include <stdio.h>
#include <windows.h>
// 이 실행파일의 이름을 child.exe 변경하세요..
void main(int argc, char** argv) {
	if (argc != 2) {
		printf("이프로그램은 직접 실행하면 안됩니다. 부모를 실행해 주세요\n");
		return;
	}
	// 부모가 보내준 pipe 핸들을 꺼낸다.
	HANDLE hPipe = (HANDLE)atoi(argv[1]);
	char buf[4096];
	while (1) {
		memset(buf, 0, 4096);
		DWORD len;
		BOOL b = ReadFile(hPipe, buf, 4096, &len, 0);
		if (b == FALSE) break;
		printf("%s\n", buf);
	}
	//CloseHandle(hPipe);
}
