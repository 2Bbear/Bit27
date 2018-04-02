#include <windows.h>
#include <conio.h>
#include <stdio.h>
// DLL의 명시적 연결은 헤더와 라이브러리 파일이 필요 없다.
// DLL 자체만 있으면 사용 가능 하다. - 단 함수의 signature를 미리 알고 있어야 한다.
/*
런타임시 메모리 관리가 필요할 경우 사용한다
*/
typedef int(*FUNC)(int, int);
typedef void(*FUNC1)(int*);
void main()
{
	//getch();
	HMODULE hDll = LoadLibrary(TEXT("0330_DLL_Real.dll"));
	if (hDll == 0)
	{
		printf("dll 을 찾을수가 없습니다.\n");
		return;
	}
	printf("DLL이 Load된 주소 : %p\n", hDll);//==Hinstance
	//----------------------------------------------
	FUNC Add = (FUNC)GetProcAddress(hDll, "Add");
	FUNC Sub = (FUNC)GetProcAddress(hDll, "Sub");
//	FUNC1 GetResult = (FUNC1)GetProcAddress(hDll, "GetResult");

	if (Add == 0 || Sub == 0 )
		printf("DLL 안에서 해당 함수를 찾을수가 없습니다.\n");
	else
	{
		printf("%d",Add(10,20));
	}

	FreeLibrary(hDll); // DLL 해지
}
