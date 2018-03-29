#include"std.h"

BOOL OnInitDialog(HWND hDlg)
{
	//db접속
	if (wbdb_DBConnect()==FALSE)
	{
		MessageBox(0, TEXT("접속실패"), TEXT(""), 0);
	}
	else
	{
		MessageBox(0, TEXT("접속성공"), TEXT(""), 0);
	}

	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//버튼 입력을 받는 event를 처리하기 위한 영역
	switch (LOWORD(wParam))
	{
	//버튼
		//문제출력버튼
	case IDC_MAIN_EXAMPOOL:
	{
		UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
			MAKEINTRESOURCE(IDD_EXAMPOOLDLG),
			hDlg,		// 부모
			exampoolDlgProc, // 메세지 함수.
			0); // WM_INITDIALOG의 lParam로 전달된다.
		if (ret == IDOK) {

		}
		return 0;
	}
	//문제 선택버튼
	case IDC_MAIN_EXAM:
	{
		UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
			MAKEINTRESOURCE(IDD_EXMADLG),
			hDlg,		// 부모
			examDlgProc, // 메세지 함수.
			0); // WM_INITDIALOG의 lParam로 전달된다.
		if (ret == IDOK) {

		}
		return 0;
	}
	//전송버튼
	case IDC_MAIN_SENDQUEST:
	{
		return 0;
	}
	case IDCANCEL:
	{
		EndDialog(hDlg, IDCANCEL);	return 0;
	}

	}
	return TRUE;
}
