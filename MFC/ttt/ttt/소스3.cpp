// CFrameWnd::Create()의 나머지 파라미터를 바꾸면 생성되는 
// 윈도우의 모양도 바꿀수 있다.

#include <afxwin.h>

class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		CFrameWnd* pFrame = new CFrameWnd;


		pFrame->Create(0, TEXT("Hello, MFC"),
			WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
			CRect(100, 100, 200, 200), 0, 0,
			WS_EX_TOPMOST); // 확장 윈도우 style

		pFrame->ShowWindow(SW_SHOW);
		pFrame->UpdateWindow();

		m_pMainWnd = pFrame;

		return TRUE;
	}
};

CHelloApp theApp;