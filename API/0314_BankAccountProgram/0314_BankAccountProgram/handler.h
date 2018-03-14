#pragma once
//다이얼로그를 초기화하는 이벤트
BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);

//Command 이벤트를 처리하는 핸들러
BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

//오른쪽 리스트 출력하는 이벤트
BOOL OnRightListControlPrint(HWND hDlg, WPARAM wParam, LPARAM lParam);

