#include <stdio.h>
#include <windows.h>
void main() {
	HANDLE hRead, hWrite;
	CreatePipe(&hRead, &hWrite, 0, 4096);
	// 읽기 위한 핸들을 상속 가능하게 한다.
	SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	TCHAR cmd[256];
	wsprintf(cmd, TEXT("child.exe %d"), hRead); // 명령형 전달인자 사용
	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof(si) };

	BOOL b = CreateProcess(0, cmd, 0, 0, TRUE, CREATE_NEW_CONSOLE,0, 0, &si, &pi);
	if (b) {
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		CloseHandle(hRead);
	}
	//--------------------------------------------
	char buf[4096];
	while (1) {
		printf("전달할 메세지를 입력하세요 >> ");
		gets_s(buf);
		DWORD len;
		WriteFile(hWrite, buf, strlen(buf) + 1, &len, 0);
	}
}
