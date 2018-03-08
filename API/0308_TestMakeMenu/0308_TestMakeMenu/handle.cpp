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
	//GetModuleHandle�� ���� ������ ���ҽ����� �޴��� �ڵ��� �ҷ���
	HMENU hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
	//�޴����� ���� �޴��� �����Ѵ� ,2��° ���ڴ� 0���� �����ϸ� ���� �޴��� �迭ó�� �ν��ϰ� 0,1...�ش� �ε��� ���� ���� �޴��� �����´�
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
	// �޴��� �߰�... ��� �߰��Ǵ°�??
	AppendMenu(h, MF_POPUP, 5000, TEXT("�߰��޴�"));	// 5000 ==> ID��..
	DrawMenuBar(hwnd);
	HMENU h1 = GetSubMenu(h, 2);
	AppendMenu(h1, MF_STRING, 5001, TEXT("BBB"));
	AppendMenu(h1, MF_STRING, 5002, TEXT("232"));
	// �޴��ٿ� ���� �߰��� ��쿡�� �ݵ�� �޴��ٸ� �ٽ� �׷��� �Ѵ�.
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
