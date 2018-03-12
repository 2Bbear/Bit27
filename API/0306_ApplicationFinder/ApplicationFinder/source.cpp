#include <windows.h>
#include <tchar.h> 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case 0:
		return 0;
	}
}
//�ڵ鰪�� ���� ������ ������Ʈ ��Ÿ�� ���ڸ� �����ϴ� �Լ�
BOOL fun_ModifyStylpe(HWND hwnd, LONG_PTR Add, LONG_PTR Remove, BOOL bRedraw)
{
	BOOL  bFlag = FALSE;
	LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE); // ��Ÿ�� ���� ������
	style |= Add;
	style &= ~Remove;
	bFlag = (BOOL)SetWindowLongPtr(hwnd, GWL_STYLE, style); // ��Ÿ�� ���� �����ϰ� �� �ƴ��� �Ұ����� Ȯ��
	if (bFlag && bRedraw)
	{
		SetWindowPos(hwnd, 0, 500, 0, 500, 500, SWP_NOMOVE); // �ٸ� ���� �� �𸣰ڴµ�, ���� ���� �� �ٲ����
		MessageBox(0, _TEXT("������"), TEXT("������"), MB_OK);
	}
		

	
	return bFlag;
}
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	HWND hwnd = FindWindow(0,_TEXT("����")); // (class�̸�,������ �̸�)�ڵ� ã�Ƴ���
	//���� Ŭ���� �̸� �� Rect ��� 
	TCHAR name[60];
	RECT rcCalc;
	GetClassName(hwnd, name, sizeof(name));
	GetWindowRect(hwnd, &rcCalc);

	//���� ���  
	TCHAR info[256];
	wsprintf(info, _TEXT("Ŭ���� �� : %s\n��ġ : %d,%d ~ %d,%d"), name,
		rcCalc.left, rcCalc.top, rcCalc.right, rcCalc.bottom);
	MessageBox(0, info, TEXT("����"), MB_OK);

	// �̵��ϱ� 
	MoveWindow(hwnd, 10, 10, rcCalc.right - rcCalc.left, rcCalc.bottom - rcCalc.top, TRUE);
	
	// ����� 
	MessageBox(0, _TEXT("�����"), TEXT("�����"), MB_OK);
	ShowWindow(hwnd, SW_HIDE);

	// ���̱� 
	MessageBox(0, _TEXT("���̱�"), TEXT("���̱�"), MB_OK);
	ShowWindow(hwnd, SW_SHOW);

	//�����ϱ�
	MessageBox(0, _TEXT("�����ϱ�"), TEXT("�����ϱ�"), MB_OK);
	
	fun_ModifyStylpe(hwnd, WS_THICKFRAME, WS_SYSMENU, TRUE);
	
	
	// �����ϱ� 
	MessageBox(0, _TEXT("�����ϱ�"), TEXT("�����ϱ�"), MB_OK); 
	SendMessage(hwnd, WM_CLOSE, 0, 0);


	return 0;
}