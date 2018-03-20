#include"std.h"
//Dlg handle


BOOL CALLBACK ModalProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	

	switch (msg)
	{
		//초기화 event
	case WM_INITDIALOG:
	{
		
		return TRUE;
	}
	//메세지 받는 event를 처리하기 위한 영역
	case WM_COMMAND:
	{
		//버튼 입력을 받는 event를 처리하기 위한 영역
		switch (LOWORD(wParam))
		{
			//사각형 버튼
		case IDC_BUTTON_MODAL_RECT:
		{
			printf("사각형 버튼 \n");
			RECTPRINT data;
			data.flag = 1;
			data.x = GetDlgItemInt(hDlg, IDC_EDIT_MODAL_X, 0, 0);
			data.y= GetDlgItemInt(hDlg, IDC_EDIT_MODAL_Y, 0, 0);
			data.width= GetDlgItemInt(hDlg, IDC_EDIT_MODAL_SIZE, 0, 0);

			wbnet_SendMessage((TCHAR*)&data, sizeof(data));
			return 0;
		}
		//타원 버튼
		case IDC_BUTTON_MODAL_ELLIP:
		{
			printf("타원 버튼 \n");
			ELLIPSEPRINT data;
			data.flag = 2;
			data.x = GetDlgItemInt(hDlg, IDC_EDIT_MODAL_X, 0, 0);
			data.y = GetDlgItemInt(hDlg, IDC_EDIT_MODAL_Y, 0, 0);
			data.width = GetDlgItemInt(hDlg, IDC_EDIT_MODAL_SIZE, 0, 0);

			wbnet_SendMessage((TCHAR*)&data, sizeof(data));
			return 0;
		}
		//문자열 버튼
		case IDC_BUTTON_MODAL_STRING:
		{
			printf("문자열 버튼 \n");
			STRINGEPRINT data;
			data.flag = 3;
			data.x = GetDlgItemInt(hDlg, IDC_EDIT_MODAL_X, 0, 0);
			data.y = GetDlgItemInt(hDlg, IDC_EDIT_MODAL_Y, 0, 0);
			
			TCHAR buff[20];
			GetDlgItemText(hDlg, IDC_EDIT_MODAL_STRING, buff, 20);
			_tcscpy(data.str, buff);
			wbnet_SendMessage((TCHAR*)&data, sizeof(data));
			return 0;
		}
		case IDCANCEL:
		{
			//_temp->color = tt;

			EndDialog(hDlg, IDCANCEL);	return 0;
		}
		case IDOK:
		{
			printf("모달 오케이\n");
			EndDialog(hDlg, IDOK);	return 0;
		}

		}
		return TRUE;
	}

	}
	return FALSE;
}


UINT SWSS_CreateWindow(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	UINT	ret = DialogBoxParam(GetModuleHandle(0),// instance
		MAKEINTRESOURCE(IDD_DIALOG2),	// 다이얼로그 선택 
		0,			// 부모 윈도우
		ModalProc,
		lParam);			// Proc..

	return ret;
}
