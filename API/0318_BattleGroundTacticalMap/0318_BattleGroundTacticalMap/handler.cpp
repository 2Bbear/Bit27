#include"std.h"

LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	//��� �޴�
		//���� - ���α׷� ����
	case ID_PROGRAMEND:
	{
		MessageBox(0, TEXT(""), TEXT(""), 0);
		return 0;

	}
		//�ʼ��� - ���ݰ�
	case ID_MAPSELEC_EVANGEL:
	{
		return 0;
	}
		//�ʼ��� - �縷
	case ID_MAPSELEC_DESERT:
	{
		return 0;
	}
		//������� - ���IP_PORT����
	case ID_SETTING_MEMBER:
	{
		return 0;
	}
		//��� - �� ���� ����
	case ID_FUNCTION_START:
	{
		return 0;
	}
		//��� - �� ���� �Ͻ����� - �ڽŸ� �Ͻ�����
	case ID_FUNCTION_PAUSEME:
	{
		return 0;
	}
		//��� - �� ���� �Ͻ����� - ��� �Ͻ�����
	case ID_FUNCTION_PAUSEALL:
	{
		return 0;
	}
		//��� - �� ���� �ߴ�
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
