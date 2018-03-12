#include <windows.h>
#include<stdio.h>
void main() {
	HANDLE hFile = CreateFile(TEXT("a.txt"), GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		0, // 보안							
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		printf("생성된 화일 핸들(Table Index) : %x\n", hFile);
	HWND hwnd = FindWindow(0, TEXT("B"));
	// hwnd을 만든 프로세스의 ID를 구한다.
	DWORD pid;
	DWORD tid = GetWindowThreadProcessId(hwnd, &pid);

	// 프로세스 ID를 가지고 PROCESS 핸들을 얻는다.
	HANDLE h;
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

	// A의 Table의 내용을 B의 Table 에 복사 해준다.
	DuplicateHandle(GetCurrentProcess(), hFile, // source
		hProcess, &h,    // target
		0, 0, DUPLICATE_SAME_ACCESS);
	printf("B에 복사한 핸들(Table index) : %x\n", h);
	SendMessage(hwnd, WM_USER + 100, 0, (LPARAM)h);
	CloseHandle(hFile);
}
