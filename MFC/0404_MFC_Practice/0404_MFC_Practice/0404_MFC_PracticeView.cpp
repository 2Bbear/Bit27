
// 0404_MFC_PracticeView.cpp : implementation of the CMy0404MFCPracticeView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "0404_MFC_Practice.h"
#endif

#include "0404_MFC_PracticeDoc.h"
#include "0404_MFC_PracticeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy0404MFCPracticeView

IMPLEMENT_DYNCREATE(CMy0404MFCPracticeView, CFormView)

BEGIN_MESSAGE_MAP(CMy0404MFCPracticeView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMy0404MFCPracticeView construction/destruction

CMy0404MFCPracticeView::CMy0404MFCPracticeView() : CFormView(CMy0404MFCPracticeView::IDD)
{
	// TODO: add construction code here

}

CMy0404MFCPracticeView::~CMy0404MFCPracticeView()
{
}

BOOL CMy0404MFCPracticeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

// CMy0404MFCPracticeView drawing

//void CMy0404MFCPracticeView::OnDraw(CDC* /*pDC*/)
//{
//	CMy0404MFCPracticeDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//
//	// TODO: add draw code for native data here
//}

void CMy0404MFCPracticeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy0404MFCPracticeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy0404MFCPracticeView diagnostics

#ifdef _DEBUG
void CMy0404MFCPracticeView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy0404MFCPracticeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy0404MFCPracticeDoc* CMy0404MFCPracticeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy0404MFCPracticeDoc)));
	return (CMy0404MFCPracticeDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy0404MFCPracticeView message handlers
