//draw.h

#ifndef MYDRAW
#define MYDRAW
//현재 그릴 값을 초기화 하는 함수
void draw_curDataInit(SHAPE * curData);

//화면을 초기화 하는 함수
void draw_NewDocument(HWND hwnd, vector<SHAPE*> *datalist);
/////////////////////////////////////////////////////////////
//벡터 컨테이너에서 객체를 하나씩 끄집어내는 함수
void draw_Print(HDC hdc, vector<SHAPE*> *datalist);
//어떤 도형을 그릴 것인지 선택하는 함수
void draw_ShapePrint(HDC hdc,SHAPE *pt);
//사각형 출력
void draw_RectanglewPrint(HDC hdc, SHAPE * pt);
//타원 출력
void draw_EllipsePrint(HDC hdc, SHAPE * pt);
//제목 출력 함수
void draw_TiltePrint(HWND hwnd, int size);
//제목 아이콘 출력 함수
void draw_ChangeIcon(HWND hwnd);
//왼쪽에 보여지는 UI를 출력하는 함수
void draw_CurPrint(HDC hdc,SHAPE g_drawCurrent, int size);

#endif