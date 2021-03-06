
// 0405_MFC_TestView.cpp : implementation of the CMy0405MFCTestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "0405_MFC_Test.h"
#endif

#include "0405_MFC_TestDoc.h"
#include "0405_MFC_TestView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy0405MFCTestView

IMPLEMENT_DYNCREATE(CMy0405MFCTestView, CView)

BEGIN_MESSAGE_MAP(CMy0405MFCTestView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMy0405MFCTestView construction/destruction

CMy0405MFCTestView::CMy0405MFCTestView()
{
	// TODO: add construction code here

}

CMy0405MFCTestView::~CMy0405MFCTestView()
{
}

BOOL CMy0405MFCTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy0405MFCTestView drawing

void CMy0405MFCTestView::OnDraw(CDC* pDC)
{
	CMy0405MFCTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	for (int i =0;i<(int)GetDocument()->m_pointlist.size();i++)
	{
		CPoint pt = pDoc->m_pointlist[i];
		pDC->Rectangle(pt.x,pt.y,pt.x+50,pt.y+50);

	}
	
	//매개변수로 넘겨준 view만 제외하고 다른 모든 view를 갱신 시킨다.

}


// CMy0405MFCTestView diagnostics

#ifdef _DEBUG
void CMy0405MFCTestView::AssertValid() const
{
	CView::AssertValid();
}

void CMy0405MFCTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy0405MFCTestDoc* CMy0405MFCTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy0405MFCTestDoc)));
	return (CMy0405MFCTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy0405MFCTestView message handlers


void CMy0405MFCTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	GetDocument()->m_pointlist.push_back(point);
	Invalidate();
	GetDocument()->UpdateAllViews(NULL);

	CView::OnLButtonDown(nFlags, point);
}


void CMy0405MFCTestView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CString buf;
	buf.Format(TEXT("%04d:%04d"), point.x, point.y);

	CView::OnMouseMove(nFlags, point);
}
