#include <stdio.h>
#include <windows.h>
void main() {
	HANDLE hRead, hWrite;
	CreatePipe(&hRead, &hWrite, 0, 4096);
	// �б� ���� �ڵ��� ��� �����ϰ� �Ѵ�.
	SetHandleInformation(hRead, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
	TCHAR cmd[256];
	wsprintf(cmd, TEXT("child.exe %d"), hRead); // ����� �������� ���
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
		printf("������ �޼����� �Է��ϼ��� >> ");
		gets_s(buf);
		DWORD len;
		WriteFile(hWrite, buf, strlen(buf) + 1, &len, 0);
	}
}
