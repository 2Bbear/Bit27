// View : View Class Ãß°¡ÇÏ±â.

#include <afxwin.h>

class CChildView : public CWnd
{
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point)
	{
		MessageBox(TEXT("LButton"));
	}
	DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CChildView, CWnd)

	ON_WM_LBUTTONDOWN()

END_MESSAGE_MAP()


////////////////////////////////////////////////
class CMainFrame : public CFrameWnd
{
public:
	CChildView m_wndView;		// view °´Ã¼ ¸É¹ö 

	afx_msg void OnSetFocus(CWnd* pOldWnd)
	{
		m_wndView.SetFocus();
	}
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
			return -1;

		// Create View 
		m_wndView.CreateEx(0, 0, 0, AFX_WS_DEFAULT_VIEW,
			CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST);

		return 0;
	}
	DECLARE_MESSAGE_MAP()
};


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)

	ON_WM_CREATE()
	ON_WM_SETFOCUS()

END_MESSAGE_MAP()



//////////////////////////////////////////////

class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		CMainFrame* pFrame = new CMainFrame;

		pFrame->Create(0, TEXT("View"));
		pFrame->ShowWindow(SW_SHOW);
		pFrame->UpdateWindow();

		m_pMainWnd = pFrame;

		return TRUE;
	}
};

CMyApp theApp;
