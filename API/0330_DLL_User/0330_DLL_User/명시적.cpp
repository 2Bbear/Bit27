#include <windows.h>
#include <conio.h>
#include <stdio.h>
// DLL�� ����� ������ ����� ���̺귯�� ������ �ʿ� ����.
// DLL ��ü�� ������ ��� ���� �ϴ�. - �� �Լ��� signature�� �̸� �˰� �־�� �Ѵ�.
/*
��Ÿ�ӽ� �޸� ������ �ʿ��� ��� ����Ѵ�
*/
typedef int(*FUNC)(int, int);
typedef void(*FUNC1)(int*);
void main()
{
	//getch();
	HMODULE hDll = LoadLibrary(TEXT("0330_DLL_Real.dll"));
	if (hDll == 0)
	{
		printf("dll �� ã������ �����ϴ�.\n");
		return;
	}
	printf("DLL�� Load�� �ּ� : %p\n", hDll);//==Hinstance
	//----------------------------------------------
	FUNC Add = (FUNC)GetProcAddress(hDll, "Add");
	FUNC Sub = (FUNC)GetProcAddress(hDll, "Sub");
//	FUNC1 GetResult = (FUNC1)GetProcAddress(hDll, "GetResult");

	if (Add == 0 || Sub == 0 )
		printf("DLL �ȿ��� �ش� �Լ��� ã������ �����ϴ�.\n");
	else
	{
		printf("%d",Add(10,20));
	}

	FreeLibrary(hDll); // DLL ����
}
