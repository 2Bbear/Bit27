//handler.h
#pragma once;

//현재 자신의 상태 함수
void InitCurrentAccount();
void SetCurrentAccountName(TCHAR * _name);
void SetCurrentAccountID(TCHAR * _id);
void SetCurrentAccountPW(TCHAR * _pw);
//
BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

void OnConnect(HWND hDlg);
//회원가입
void OnAddMember(HWND hDlg);
//로그인
void OnLogin(HWND hDlg);
//로그아웃
void OnLogOut(HWND hDlg);
//메세지보내기?
void OnSendData(HWND hDlg);
//회원탈퇴
void OnUnregister(HWND hDlg);

//wbnet->handler
void OnLogMessage(TCHAR *msg);
void OnMessage(char* buf, int nRead);