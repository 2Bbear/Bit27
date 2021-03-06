
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "0405_MFC_Test.h"

#include "MainFrm.h"
#include"0405_MFC_TestView.h"
#include"MFCClass.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_INDICATOR_TIME,
	IDS_MYSTRING1,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_wndStatusBar.SetPaneStyle(4, SBPS_NOBORDERS);// 평면.
	// Timer 를 설정한다.
	SetTimer(1, 1000, 0); // ID, 주기, 함수.
						  // 처음에 1번 강제로 WM_TIMER를 보낸다.
	SendMessage(WM_TIMER, 1); // wParam = ID


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

	return TRUE;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext * pContext)
{
	//return m_wndSplitter.Create(this, 2, 2, CSize(100, 100), pContext);
	//// 동적 Splitter은 같은 종류의 view( CSampleView)만 가지고
	//// 있기 때문에 사용자가 splitter만 만들면 View는 MFC가 자동으로
	//// 만들어 준다.
	//return CFrameWnd::OnCreateClient(lpcs, pContext);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 정적 Splitter 만들기.
	// 1. splitter 를 먼저 만든다.
	m_wndSplitter.CreateStatic(this, 1, 2);
	m_wndSplitter2.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter.IdFromRowCol(0, 0));
	//=================================================
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMy0405MFCTestView),CSize(100, 100), pContext);
	//m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMy0405MFCTestView), CSize(100, 100), pContext);
	m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(MFCClass), CSize(100, 100), pContext);
	m_wndSplitter2.CreateView(1, 0, RUNTIME_CLASS(CMy0405MFCTestView), CSize(100, 100), pContext);

	m_wndSplitter.SetColumnInfo(0, 700, 20);
	m_wndSplitter2.SetRowInfo(0,300, 20);
	return TRUE;


}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{

	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers



void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{
		CTime t = CTime::GetCurrentTime(); // 현재 시간 얻기
		CString buf;
		buf.Format(TEXT("%02d:%02d:%02d"),
			t.GetHour(), t.GetMinute(), t.GetSecond());
		m_wndStatusBar.SetPaneText(4, buf);
		m_wndStatusBar.SetPaneText(5, buf);
	}

	CFrameWnd::OnTimer(nIDEvent);
}
