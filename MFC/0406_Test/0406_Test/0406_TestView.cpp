
// 0406_TestView.cpp : implementation of the CMy0406TestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "0406_Test.h"
#endif

#include "0406_TestDoc.h"
#include "0406_TestView.h"

#include"MainFrm.h"
#include"ModalDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy0406TestView

IMPLEMENT_DYNCREATE(CMy0406TestView, CView)

BEGIN_MESSAGE_MAP(CMy0406TestView, CView)
	ON_COMMAND(ID_32777, &CMy0406TestView::On32777)
	ON_COMMAND(ID_32778, &CMy0406TestView::On32778)
	ON_COMMAND(ID_32779, &CMy0406TestView::On32779)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_32780, &CMy0406TestView::On32780)
	ON_COMMAND(ID_32776, &CMy0406TestView::On32776)
END_MESSAGE_MAP()

// CMy0406TestView construction/destruction

CMy0406TestView::CMy0406TestView()
{
	// TODO: add construction code here

	
}

CMy0406TestView::~CMy0406TestView()
{
}

BOOL CMy0406TestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy0406TestView drawing

void CMy0406TestView::OnDraw(CDC* pDC)
{
	CMy0406TestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	POINT mpt = GetDocument()->m_CurDate.pt;
	CBrush newBrush;
	CPen newPen;
	newPen.CreatePen(PS_SOLID, 2, GetDocument()->m_CurDate.color);
	newBrush.CreateSolidBrush(GetDocument()->m_CurDate.color);
	CPen * pOldPen = pDC->SelectObject(&newPen);
	CBrush *pOldBrush = pDC->SelectObject(&newBrush);

	pDC->Rectangle(mpt.x, mpt.y, mpt.x + 50, mpt.y + 50);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);




	

}


// CMy0406TestView diagnostics

#ifdef _DEBUG
void CMy0406TestView::AssertValid() const
{
	CView::AssertValid();
}

void CMy0406TestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy0406TestDoc* CMy0406TestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy0406TestDoc)));
	return (CMy0406TestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy0406TestView message handlers


void CMy0406TestView::On32777()
{
	// TODO: Add your command handler code here
	GetDocument()->m_CurDate.color = RGB(255,0,0);
	Invalidate();
	CString temp;
	temp.SetString(TEXT("빨강"));
	((CMainFrame*)AFXGetParentFrame(this))->PrintCurrentColor(temp);
	

}


void CMy0406TestView::On32778()
{
	// TODO: Add your command handler code here
	GetDocument()->m_CurDate.color = RGB(0, 255, 0);
	Invalidate();
	CString temp;
	temp.SetString(TEXT("녹 색"));
	((CMainFrame*)AFXGetParentFrame(this))->PrintCurrentColor(temp);
}


void CMy0406TestView::On32779()
{
	// TODO: Add your command handler code here
	GetDocument()->m_CurDate.color = RGB(0, 0, 255);
	Invalidate();
	CString temp;
	temp.SetString(TEXT("파랑"));
	((CMainFrame*)AFXGetParentFrame(this))->PrintCurrentColor(temp);
}


void CMy0406TestView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default




	CView::OnMouseMove(nFlags, point);
}


void CMy0406TestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	GetDocument()->m_CurDate.pt = point;
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CMy0406TestView::On32780()
{
	// TODO: Add your command handler code here
	ModalDlg subWindow(this);
	subWindow.DoModal();

}


void CMy0406TestView::On32776()
{
	// TODO: Add your command handler code here
	
}
