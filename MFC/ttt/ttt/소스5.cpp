// 일반적으로 CFrameWnd를 직접 사용하지 않고 거기서 
// 계승된 class 만들어 사용한다.

// 또한 PreCreateWindow()를 재정의 하면 생성되는 윈도우의 클래스,
// 및 style 등을 변경할수 있다.
// AfxGetApp()가 하는일은 ?
// 현재 메모리에는 사용자가 만든 객체가 몇개 있을까?, 
// 각각 어디 있을까 ?

//각 객체들의 성질들을 이해하자

#include <afxwin.h>

class CMainFrame : public CFrameWnd
{
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs)
	{
		if (!CFrameWnd::PreCreateWindow(cs))
			return FALSE;

		cs.style = cs.style & ~WS_MAXIMIZEBOX;

		cs.lpszClass = AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW),
			(HBRUSH)GetStockObject(LTGRAY_BRUSH),
			AfxGetApp()->LoadStandardIcon(IDI_WINLOGO));

		return TRUE;
	}
};

class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		CMainFrame* pFrame = new CMainFrame;

		pFrame->Create(0, TEXT("Hello, MFC"));
		pFrame->ShowWindow(SW_SHOW);
		pFrame->UpdateWindow();

		m_pMainWnd = pFrame;

		return TRUE;
	}
};

CHelloApp theApp;