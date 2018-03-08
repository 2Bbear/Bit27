#include"std.h"


static int check1=1;


LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT OnInitMenuPopUp(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//		HMENU hMenu = GetMenu(hwnd);
	HMENU hMenu = (HMENU)wParam;
	EnableMenuItem(hMenu, ID_FILE_RESETWINDOW, check1 == 0 ? MF_GRAYED : MF_ENABLED);
	

	return 0;
}

LRESULT OnContextMenu(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//GetModuleHandle로 현재 윈도우 리소스에서 메뉴의 핸들을 불러옴
	HMENU hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
	//메뉴에서 서브 메뉴만 추출한다 ,2번째 인자는 0부터 시작하며 서브 메뉴를 배열처럼 인식하고 0,1...해당 인덱스 값의 서브 메뉴를 가져온다
	HMENU hSubMenu = GetSubMenu(hMenu, 1);

	POINT  pt = { LOWORD(lParam), HIWORD(lParam) };
	TrackPopupMenu(hSubMenu, TPM_RIGHTALIGN, pt.x, pt.y, 0, hwnd, 0);
	
	return 0;
}

LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case ID_FILE_RESETWINDOW:
	{
		
		check1 = 0;
		break;
	}
	}

	return 0;
}

LRESULT OnLButtonDwon(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	HMENU	h = GetMenu(hwnd);
	// 메뉴를 추가... 어디에 추가되는가??
	AppendMenu(h, MF_POPUP, 5000, TEXT("추가메뉴"));	// 5000 ==> ID값..
	DrawMenuBar(hwnd);
	HMENU h1 = GetSubMenu(h, 2);
	AppendMenu(h1, MF_STRING, 5001, TEXT("BBB"));
	AppendMenu(h1, MF_STRING, 5002, TEXT("232"));
	// 메뉴바에 직접 추가한 경우에는 반드시 메뉴바를 다시 그려야 한다.
	DrawMenuBar(hwnd);


	return 0 ;
}

LRESULT OnRButtonDwon(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	

	return 0;
}

LRESULT OnDestroy()
{
	return 0;
}
