#pragma once

//
typedef struct tagRECTANGLE
{
	int flag;
	POINT pt;
	COLORREF color;
}RECTANGLE;
typedef struct tagELLIPSE
{
	int flag;
	POINT pt;
	COLORREF color;
}ELLIPSE;
typedef struct tagLINE
{
	int flag;
	POINT startPt;
	POINT endPt;
	COLORREF color;
}LINE;



//==
//C => S
#define SEND_RECTANGLE 1;
#define SEND_ELLIPSE 2;
#define SEND_LINE 3;

//S=>C
#define RE_RECTANGLE_S 100;
#define RE_RECTANGLE_F 101;
#define RE_ELLIPSE_S 102;
#define RE_ELLIPSE_F 103;
#define RE_LINE_S 104;
#define RE_LINE_F 105;

//==
//Packising Function

RECTANGLE Pack_Rectangle(POINT _pt, COLORREF _color);
ELLIPSE Pack_Ellipse(POINT _pt, COLORREF _color);
LINE Pack_Line(POINT _start, POINT _end, COLORREF _color);