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
		printf("B �����츦 ���� ������ �ּ���\n");	return;
	}
	while (1)
	{
		printf("B���� ������ �޼����� �Է��ϼ��� >> ");
		
		
		_tcscanf_s(TEXT("%s"),buf,_countof(buf)+2);
		
		
					// 1���Է� ?
				   // �������� Pointer�� �����ϱ� ���� �޼��� - WM_COPYDATA
		COPYDATASTRUCT cds;
		cds.cbData = _tcslen(buf)*2 + 2;  // ������ data ũ��
		cds.dwData = 1;				// �ĺ��� 
		cds.lpData = buf;			// ������ Pointer
		SendMessage(hwnd, WM_COPYDATA, 0, (LPARAM)&cds);
	}

}
