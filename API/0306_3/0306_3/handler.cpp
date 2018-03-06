//handler.cpp

#include"std.h"

extern vector<POINT> g_drawList;// ���� ����

LRESULT OnDestroy()
{
	PostQuitMessage(0);
	return 0;
}

LRESULT OnLButtonDown(HWND hwnd, LPARAM lParam)
{
	
	//=========================================
	//POINTS pt = MAKEPOINTS(lParam);
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	POINT pt1 = { LOWORD(lParam), HIWORD(lParam) };

	g_drawList.push_back(pt1);// ������� �簢���� ��ġ ���� ����
	
	RECT rc = { x - 25, y - 25, x + 25, y + 25 };
	InvalidateRect(hwnd, &rc, FALSE);
	
	draw_TiltePrint(hwnd, g_drawList.size());
	//=========================================
	return 0;
}

LRESULT OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);// �� �Լ��� �̿��ؾ��� ��ȿȭ ������ �����Ǽ� ���̻� WM_PAINT �޼����� �ȳ������ �ȴ�
	//===========================================
	draw_Print(hdc, &g_drawList);//����ؼ� ��� �簢���� �׸�, ��ȿȭ ������ ���ֱ� ���� ä������ ���¸� ����� ����
	//===========================================
	EndPaint(hwnd, &ps);
	return 0;
}
LRESULT  OnRButtonDown(HWND hwnd)
{
	//���Ͱ� ���� �ִ��� Ȯ��
	if (g_drawList.size()<=0)
	{
		return 0;
	}
	//������ �� ���� ���� ����
	g_drawList.pop_back();
	//������ �ٽ� �׸���
	InvalidateRect(hwnd, 0, TRUE);//ȭ���� �ٽ� �׸��� �Լ�
	//����ó��
	draw_TiltePrint(hwnd, g_drawList.size());
	return 0;
}
LRESULT OnCreate(HWND hwnd)
{
	//���� �ʱ�ȭ
	draw_TiltePrint(hwnd, g_drawList.size());
	return 0;
}