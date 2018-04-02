//cal.h
#pragma once
#ifdef DLL_SOURCE
#define DLLFUNC	__declspec(dllexport)   //dll에 작성할때
#else
#define DLLFUNC __declspec(dllimport) //dll을 가져가서 사용 할때
#endif
#include <windows.h>

EXTERN_C DLLFUNC  int Add(int a, int b);

EXTERN_C DLLFUNC int Sub(int a, int b);

EXTERN_C int Mul(int a, int b);
