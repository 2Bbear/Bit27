#pragma once
#define PACK_RECTPRINT	1
#define PACK_ELLIPSEPRINT 2
#define PACK_STRINGPRINT  3

typedef struct tagRECTPRINT
{
	int flag;
	int x;
	int y;
	int width;

}RECTPRINT;

typedef struct tagELLIPSEPRINT
{
	int flag;
	int x;
	int y;
	int width;
}ELLIPSEPRINT;

typedef struct tagSTRINGEPRINT
{
	int flag;
	int x;
	int y;
	TCHAR str[20];
}STRINGEPRINT;