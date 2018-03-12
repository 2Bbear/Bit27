#pragma once
//Process만드는 첫번째 방법
BOOL OnCreateProcess_1();
//Process만드는 두번째 방법
BOOL OnCreateProcess_2();

//Process 종료 첫번째 방법
/*
@hDlg는 종료시킬 process handle
*/
BOOL OnExitProcess_1(HWND hDlg);

//Process 종료 두번째 방법
/*
@ hDlg는 종료시킬 process handle
@ hwnd는 메세지 박스 출력할 상위 윈도우

*/
BOOL OnExitProcess_2(HANDLE hDlg,HWND hwnd);

//윈도우 핸들로 process ID 얻는 방법
BOOL OnGetProcessIDInWidowHandle(HWND hwnd,LPDWORD lpdwProcessID);

//Process ID로 Window Handle 얻는 방법
/*
이 함수를 사용하면 참조 카운트가 증가합니다.
*/
BOOL OnGetWindowHandleInProcessID(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessID);

//자식 process의 핸들을 복사하는 방법
/*
@ hProcess2 복사한 값이 들어갈 핸들
@ pi  복사할 자식 process의 정보 구조체
@ b 부모가 자식의 제어를 해제 할 것인지 판단하는 함수 TRUE는 해제, FALSE는 해제 안함
*/
BOOL OnCopyChildHandle(HANDLE hProcess2, PROCESS_INFORMATION pi,BOOL b);
