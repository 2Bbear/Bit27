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
//핸들값을 통해 윈도우 오브젝트 스타일 인자를 변경하는 함수
BOOL fun_ModifyStylpe(HWND hwnd, LONG_PTR Add, LONG_PTR Remove, BOOL bRedraw)
{
	BOOL  bFlag = FALSE;
	LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE); // 스타일 값을 가져옴
	style |= Add;
	style &= ~Remove;
	bFlag = (BOOL)SetWindowLongPtr(hwnd, GWL_STYLE, style); // 스타일 값을 변경하고 잘 됐는지 불값으로 확인
	if (bFlag && bRedraw)
	{
		SetWindowPos(hwnd, 0, 500, 0, 500, 500, SWP_NOMOVE); // 다른 값은 다 모르겠는데, 넓이 값만 잘 바뀌어짐
		MessageBox(0, _TEXT("ㅇㅁㅇ"), TEXT("ㅁㅇㅁ"), MB_OK);
	}
		

	
	return bFlag;
}
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	HWND hwnd = FindWindow(0,_TEXT("계산기")); // (class이름,윈도우 이름)핸들 찾아내기
	//계산기 클래스 이름 및 Rect 얻기 
	TCHAR name[60];
	RECT rcCalc;
	GetClassName(hwnd, name, sizeof(name));
	GetWindowRect(hwnd, &rcCalc);

	//정보 출력  
	TCHAR info[256];
	wsprintf(info, _TEXT("클래스 명 : %s\n위치 : %d,%d ~ %d,%d"), name,
		rcCalc.left, rcCalc.top, rcCalc.right, rcCalc.bottom);
	MessageBox(0, info, TEXT("정보"), MB_OK);

	// 이동하기 
	MoveWindow(hwnd, 10, 10, rcCalc.right - rcCalc.left, rcCalc.bottom - rcCalc.top, TRUE);
	
	// 숨기기 
	MessageBox(0, _TEXT("숨기기"), TEXT("숨기기"), MB_OK);
	ShowWindow(hwnd, SW_HIDE);

	// 보이기 
	MessageBox(0, _TEXT("보이기"), TEXT("보이기"), MB_OK);
	ShowWindow(hwnd, SW_SHOW);

	//변경하기
	MessageBox(0, _TEXT("변경하기"), TEXT("변경하기"), MB_OK);
	
	fun_ModifyStylpe(hwnd, WS_THICKFRAME, WS_SYSMENU, TRUE);
	
	
	// 종료하기 
	MessageBox(0, _TEXT("종료하기"), TEXT("종료하기"), MB_OK); 
	SendMessage(hwnd, WM_CLOSE, 0, 0);


	return 0;
}