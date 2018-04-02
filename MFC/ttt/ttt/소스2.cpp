// CFrameWnd class 를 사용해서 윈도우 만들기.

#include <afxwin.h>

class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		CFrameWnd* pFrame = new CFrameWnd;

		// 내부적으로 CreateWindowEx()가 수행 된다.
		pFrame->Create(0, TEXT("Hello, MFC"));

		// 생성된 윈도우 HWND은 어디 있을까 ?
		pFrame->ShowWindow(SW_SHOW);
		pFrame->UpdateWindow();

		// 반드시 보관해야 한다. CWnd* m_pMainWnd; 로 선언되어 있다.//cWind는 눈에 보이는 객체들의 최상위 부모다
		m_pMainWnd = pFrame;

		// 메세지 루프를 수행하라는 의미
		return TRUE;
	}
};

CHelloApp theApp;
