//cal.h
#pragma once
#ifdef DLL_SOURCE
#define DLLFUNC	__declspec(dllexport)   //dll�� �ۼ��Ҷ�
#else
#define DLLFUNC __declspec(dllimport) //dll�� �������� ��� �Ҷ�
#endif
#include <windows.h>

EXTERN_C DLLFUNC  int Add(int a, int b);

EXTERN_C DLLFUNC int Sub(int a, int b);

EXTERN_C int Mul(int a, int b);
