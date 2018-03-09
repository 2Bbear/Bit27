#include"std.h"

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static DATA *pData;
	switch (msg)
	{
	case WM_HSCROLL:
	{
		int n = 0;

		pData->opa_pen = SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_GETPOS, TRUE, (LPARAM)&n);
		return 0;
	}
	case WM_INITDIALOG:
	{
		

		pData = (DATA *)lParam;
		//edit 초기화
		SetDlgItemInt(hDlg,IDC_EDIT1,pData->w_count,0);
		SetDlgItemInt(hDlg, IDC_EDIT2, pData->h_count, 0);
		//슬라이더 바 초기화
		//1>범위 설정 
		SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_SETRANGE, FALSE, MAKELPARAM(1, 5));
		//2>초기값 입력
		SendMessage(GetDlgItem(hDlg, IDC_SLIDER1), TBM_SETPOS, TRUE, pData->opa_pen);

	}	return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			pData->w_count=GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
			pData->h_count= GetDlgItemInt(hDlg, IDC_EDIT2, 0, 0);
			
			EndDialog(hDlg, IDOK);	return 0;
		}

		case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return 0;
		}
		return TRUE;
	}
	return FALSE;
}