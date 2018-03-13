#include <Windows.h>
#include<tchar.h>
//You must have make Resource-Dialog 
#include"resource.h"
HWND hwnd;
void OnConnect(HWND hDlg)
{

	TCHAR str[20];
	GetDlgItemText(hDlg, IDC_EDIT3, str, sizeof(str));
	hwnd = FindWindow(0,str );
	if (hwnd == 0)
	{
		MessageBox(hDlg, TEXT("B 윈도우를 먼저 실행시켜 주세요!\n"), TEXT("알림"), MB_OK);
	}
	
	

}
void OnSendData(HWND hDlg)
{
	//보낼 문자열
	TCHAR buf[256];
	GetDlgItemText(hDlg, IDC_EDIT1, buf, sizeof(buf));
	// 원격지로 Pointer를 전달하기 위한 메세지 - WM_COPYDATA
	COPYDATASTRUCT cds;
	cds.cbData = _tcslen(buf)*2 + 2;  // 전달한 data 크기
	cds.dwData = 1;				// 식별자 
	cds.lpData = buf;			// 전달할 Pointer
	SendMessage(hwnd, WM_COPYDATA, 0, (LPARAM)&cds);

	HWND hEdit = GetDlgItem(hDlg, IDC_EDIT2);

	TCHAR Mebuf[300];
	wsprintf(Mebuf, TEXT("A :%s"),buf);
	SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)Mebuf);
	SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));

}
void OnCopyData(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	HWND hEdit = GetDlgItem(hDlg, IDC_EDIT2);
	COPYDATASTRUCT* p = (COPYDATASTRUCT*)lParam;
	if (p->dwData == 1) // 식별자 조사.
	{
		//상대 태그 추가 변조
		TCHAR Mebuf[300];
		wsprintf(Mebuf, TEXT("B :%s"), p->lpData);
		// Edit Box에 추가 한다.
		SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)Mebuf);
		SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
	}
}
BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	
	//데이타 전달 받기
	case WM_COPYDATA:
	{
		OnCopyData(hDlg, wParam, lParam);

		return 0;
	}
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

		case IDC_BUTTON3:
		{
			
			OnConnect(hDlg);
			return 0;
		}
		case IDC_BUTTON2:
		{
			OnSendData(hDlg);
			return 0;
		}
		case IDCANCEL:
		{
			EndDialog(hDlg, IDCANCEL);	return 0;
		}

		}
		return TRUE;
	}

	}
	return FALSE;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd)
{
	UINT	ret = DialogBox(hInst,// instance
		MAKEINTRESOURCE(IDD_DIALOG1),	// 다이얼로그 선택 
		0,			// 부모 윈도우
		DlgProc);			// Proc..
	return 0;
}
