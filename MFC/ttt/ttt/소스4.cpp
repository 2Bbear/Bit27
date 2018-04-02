// AfxRegisterWndClass() 를 사용해서 윈도우 class 변경하기...
// MFC가 내부적으로 윈도우클래스를 등록하지만, 
// 사용자가 다시 등록해서 사용할수도 있다.

#include <afxwin.h>

class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		CFrameWnd* pFrame = new CFrameWnd;

		CString str = AfxRegisterWndClass(0, LoadStandardCursor(IDC_IBEAM),
			(HBRUSH)GetStockObject(BLACK_BRUSH),
			LoadStandardIcon(IDI_WINLOGO));

		pFrame->Create(str,  // 윈도우 클래스..
			TEXT("Hello, MFC"),
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