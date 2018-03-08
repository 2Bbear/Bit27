//draw.h

#ifndef MYDRAW
#define MYDRAW
//���� �׸� ���� �ʱ�ȭ �ϴ� �Լ�
void draw_curDataInit(SHAPE * curData);

//ȭ���� �ʱ�ȭ �ϴ� �Լ�
void draw_NewDocument(HWND hwnd, vector<SHAPE*> *datalist);
/////////////////////////////////////////////////////////////
//���� �����̳ʿ��� ��ü�� �ϳ��� ������� �Լ�
void draw_Print(HDC hdc, vector<SHAPE*> *datalist);
//� ������ �׸� ������ �����ϴ� �Լ�
void draw_ShapePrint(HDC hdc,SHAPE *pt);
//�簢�� ���
void draw_RectanglewPrint(HDC hdc, SHAPE * pt);
//Ÿ�� ���
void draw_EllipsePrint(HDC hdc, SHAPE * pt);
//���� ��� �Լ�
void draw_TiltePrint(HWND hwnd, int size);
//���� ������ ��� �Լ�
void draw_ChangeIcon(HWND hwnd);
//���ʿ� �������� UI�� ����ϴ� �Լ�
void draw_CurPrint(HDC hdc,SHAPE g_drawCurrent, int size);

#endif