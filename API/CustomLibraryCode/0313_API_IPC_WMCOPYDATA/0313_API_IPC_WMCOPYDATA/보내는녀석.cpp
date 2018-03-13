#include <windows.h>
#include<tchar.h>

#include <atlconv.h>
#include <string>



#include <stdio.h>
void main()
{

	TCHAR buf[256] = { 0 };
	HWND hwnd = FindWindow(0, TEXT("B"));
	if (hwnd == 0)
	{
		printf("B 윈도우를 먼저 실행해 주세요\n");	return;
	}
	while (1)
	{
		printf("B에게 전달한 메세지를 입력하세요 >> ");
		
		
		_tcscanf_s(TEXT("%s"),buf,_countof(buf)+2);
		
		
					// 1줄입력 ?
				   // 원격지로 Pointer를 전달하기 위한 메세지 - WM_COPYDATA
		COPYDATASTRUCT cds;
		cds.cbData = _tcslen(buf)*2 + 2;  // 전달한 data 크기
		cds.dwData = 1;				// 식별자 
		cds.lpData = buf;			// 전달할 Pointer
		SendMessage(hwnd, WM_COPYDATA, 0, (LPARAM)&cds);
	}

}
