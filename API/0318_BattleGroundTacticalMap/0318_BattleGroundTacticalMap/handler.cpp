#include"std.h"

LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	//상단 메뉴
		//파일 - 프로그램 종료
	case ID_PROGRAMEND:
	{
		MessageBox(0, TEXT(""), TEXT(""), 0);
		return 0;

	}
		//맵선택 - 에반겔
	case ID_MAPSELEC_EVANGEL:
	{
		return 0;
	}
		//맵선택 - 사막
	case ID_MAPSELEC_DESERT:
	{
		return 0;
	}
		//멤버설정 - 멤버IP_PORT설정
	case ID_SETTING_MEMBER:
	{
		return 0;
	}
		//기능 - 맵 전술 시작
	case ID_FUNCTION_START:
	{
		return 0;
	}
		//기능 - 맵 전술 일시정지 - 자신만 일시정지
	case ID_FUNCTION_PAUSEME:
	{
		return 0;
	}
		//기능 - 맵 전술 일시정지 - 모두 일시정지
	case ID_FUNCTION_PAUSEALL:
	{
		return 0;
	}
		//기능 - 맵 전술 중단
	case ID_FUNCTION_STOP:
	{
		return 0;
	}

	}
	return 0;
}

LRESULT OnDestroy()
{
	PostQuitMessage(0);
	return 0;
}

LRESULT OnLbuttonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{

	return 0;
}
