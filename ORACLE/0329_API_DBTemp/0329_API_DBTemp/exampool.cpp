#include"std.h"

static HWND g_hComobo;

void OnInitExamPool(HWND hDlg)
{
	//콤보 박스 초기화
	g_hComobo=GetDlgItem(hDlg, IDC_EXAMPOOL_COMBOBOX1);
	SendMessage(g_hComobo, CB_ADDSTRING, 0, (LPARAM)TEXT("1"));
	SendMessage(g_hComobo, CB_ADDSTRING, 0, (LPARAM)TEXT("2"));
	SendMessage(g_hComobo, CB_ADDSTRING, 0, (LPARAM)TEXT("3"));
	SendMessage(g_hComobo, CB_ADDSTRING, 0, (LPARAM)TEXT("4"));

	SendMessage(g_hComobo, CB_SETCURSEL, 0, 0);

	//전송

}

void OnInsertExamPool(HWND hDlg)
{
	//변수 선언
	TCHAR str1[500];
	TCHAR str2[100];
	TCHAR str3[100];
	TCHAR str4[100];
	TCHAR str5[100];
	int number;
	//Edit에서 각 자료 가져오기
	GetDlgItemText(hDlg, IDC_EXAMPOOL_EDIT1,str1,sizeof(str1)); //문제
	GetDlgItemText(hDlg, IDC_EXAMPOOL_EDIT2, str2, sizeof(str2));//1번
	GetDlgItemText(hDlg, IDC_EXAMPOOL_EDIT3, str3, sizeof(str3));//2번
	GetDlgItemText(hDlg, IDC_EXAMPOOL_EDIT4, str4, sizeof(str4));//3번
	GetDlgItemText(hDlg, IDC_EXAMPOOL_EDIT5, str5, sizeof(str5));//4번
	number = GetDlgItemInt(hDlg, IDC_EXAMPOOL_COMBOBOX1, 0, 0);//진짜답

	//전송 DB 저장 테스트
	if (wbdb_CreateExam(str1, str2, str3, str4, str5, number))
	{
		EndDialog(hDlg, 0);
	}
	else
	{

	}

}
//대화 상자 프로시저
BOOL CALLBACK exampoolDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
		// Dialog가 처음 나타날때 발생. 각 콘트롤을 초기화 한다.
	case WM_INITDIALOG: 
	{
		OnInitExamPool(hDlg);
		return TRUE;
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case IDC_EXAMPOOL_BUTTON1:
		{
			OnInsertExamPool(hDlg);
			return 0;
		}
		case IDOK:
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
	}
	return FALSE; // 메세지 처리를 안한경우..
}

