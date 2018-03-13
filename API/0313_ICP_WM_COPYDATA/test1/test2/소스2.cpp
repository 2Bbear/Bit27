#include <Windows.h>
#include<tchar.h>
//You must have make Resource-Dialog 
#include"resource.h"

void OnCopyData(HWND hDlg,WPARAM wParam, LPARAM lParam)
{
	HWND hEdit = GetDlgItem(hDlg, IDC_EDIT1);
	COPYDATASTRUCT* p = (COPYDATASTRUCT*)lParam;
	if (p->dwData == 1) // 식별자 조사.
	{
		//상대 태그 추가 변조
		TCHAR Mebuf[300];
		wsprintf(Mebuf, TEXT("A :%s"), p->lpData);
		// Edit Box에 추가 한다.
		SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)Mebuf);
		SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));
	}
}
HWND hwnd;
void OnConnect(HWND hDlg)
{

	
	hwnd = FindWindow(0, TEXT("A"));
	


}
void OnSendData(HWND hDlg)
{
	//보낼 문자열
	TCHAR buf[256];
	GetDlgItemText(hDlg, IDC_EDIT2, buf, sizeof(buf));
	// 원격지로 Pointer를 전달하기 위한 메세지 - WM_COPYDATA
	COPYDATASTRUCT cds;
	cds.cbData = _tcslen(buf) * 2 + 2;  // 전달한 data 크기
	cds.dwData = 1;				// 식별자 
	cds.lpData = buf;			// 전달할 Pointer
	SendMessage(hwnd, WM_COPYDATA, 0, (LPARAM)&cds);
	TCHAR Mebuf[300];
	wsprintf(Mebuf, TEXT("B :%s"), buf);
	HWND hEdit = GetDlgItem(hDlg, IDC_EDIT1);
	SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)Mebuf);
	SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)TEXT("\r\n"));

}

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//데이타 전달 받기
	case WM_COPYDATA:
	{
		OnCopyData(hDlg,wParam,lParam);
		
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
			//데이타 전달하기
		case IDC_BUTTON1:
		{
			OnConnect(hDlg);
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
