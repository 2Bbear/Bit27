#include<stdio.h>
#include"cal.h"
#pragma comment(lib,"0330_DLL_Real.lib")


void main()
{
	printf("%d",Add(10, 20));
	//printf("%d", Mul(10, 20));//요건 export 처리 안해서 못씀
}