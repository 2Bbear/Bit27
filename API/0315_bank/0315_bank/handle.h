#pragma once
//다이얼로그 초기화 함수
BOOL OnInitDialog(HWND hDlg);

//계좌 생성 윈도우 띄우는 함수
BOOL OnCreateAccountWindow(HWND hDlg, WPARAM wParam, LPARAM lParam);

//계좌 검색 윈도우 띄우는 함수
BOOL OnSearchAccountWindow(HWND hDlg, WPARAM wParam, LPARAM lParam);

//계좌 내역 출력을 처리하는 함수 wParam , lParam 양쪽에 id값이 있으니 골라서 가져 가면 됨 이 값은 TCHAR *임
BOOL OnAccountDetailPrint(HWND hDlg, WPARAM wParam, LPARAM lParam);

//계좌삭제버튼
BOOL OnDeleteAccountButton(HWND hDlg);
//입출금 버튼
BOOL OnBankStatement(HWND hDlg);
//라디오 버튼
	//입력
BOOL OnDeposit();
	//출금
BOOL OnWithdraw();