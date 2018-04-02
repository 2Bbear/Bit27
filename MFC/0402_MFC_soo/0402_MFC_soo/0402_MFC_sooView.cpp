
// 0402_MFC_sooView.cpp : CMy0402_MFC_sooView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "0402_MFC_soo.h"
#endif

#include "0402_MFC_sooDoc.h"
#include "0402_MFC_sooView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy0402_MFC_sooView

IMPLEMENT_DYNCREATE(CMy0402_MFC_sooView, CView)

BEGIN_MESSAGE_MAP(CMy0402_MFC_sooView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMy0402_MFC_sooView 생성/소멸

CMy0402_MFC_sooView::CMy0402_MFC_sooView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy0402_MFC_sooView::~CMy0402_MFC_sooView()
{
}

BOOL CMy0402_MFC_sooView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy0402_MFC_sooView 그리기

void CMy0402_MFC_sooView::OnDraw(CDC* pDC)
{
	CMy0402_MFC_sooDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	pDC->Rectangle(5,5,5,5);

	for (int i = 0; i<(int)pDoc->m_ShapeList.size(); i++)
	{

		CBrush * pNewBrush = new CBrush(pDoc->m_BrushColor);

		CBrush * pOldBrush = NULL;
		pOldBrush = pDC->SelectObject(pNewBrush);

		CPoint pt = pDoc->m_ShapeList[i];
		pDC->Rectangle(pt.x, pt.y, pt.x + 50, pt.y + 50);

		pDC->SelectObject(pOldBrush);
		delete(pNewBrush);
	}
}


// CMy0402_MFC_sooView 진단

#ifdef _DEBUG
void CMy0402_MFC_sooView::AssertValid() const
{
	CView::AssertValid();
}

void CMy0402_MFC_sooView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy0402_MFC_sooDoc* CMy0402_MFC_sooView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy0402_MFC_sooDoc)));
	return (CMy0402_MFC_sooDoc*)m_pDocument;
}
#endif //_DEBUG


 //CMy0402_MFC_sooView 메시지 처리기
/*
class CClientDC : CDC
{
	HDC hdc;
	public CClientDC(CWnd *p)
	{
		hdc = ::GetDC(p->m_hWnd);
	}
	public ~CClientDC()
	{
		::ReleaseDC(p->m_hWnd,hdc);
	}
	public void Rectangle(int x, int y , int w, int h)
	{
		::Rectangle(hdc,x,y,w,h);
	}
};

*/

void CMy0402_MFC_sooView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*CClientDC dc(this);
	dc.Rectangle(point.x, point.y, point.x+50, point.y + 50);*/
	if (nFlags & MK_CONTROL)
	{
		if (GetDocument()->m_ShapeList.size() <= 0)
			return;
		GetDocument()->m_ShapeList.pop_back();
	}
	else
	{
		GetDocument()->m_ShapeList.push_back(point);
	}
	Invalidate();
	TCHAR buf[20];
	wsprintf(buf, TEXT("저장개수:%d개\n "), GetDocument()->m_ShapeList.size());
	AfxGetMainWnd()->SetWindowTextW(buf);
	CView::OnLButtonDown(nFlags, point);



	CView::OnLButtonDown(nFlags, point);
}


void CMy0402_MFC_sooView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMy0402_MFC_sooDoc * pDoc = GetDocument();

	if (nChar == 'R')
		pDoc->m_BrushColor = RGB(255, 0, 0);
	else if (nChar == 'G')
		pDoc->m_BrushColor = RGB(0, 255, 0);
	else if (nChar == 'B')
		pDoc->m_BrushColor = RGB(0, 0, 255);
	else if (nChar >= 'A'&&nChar >= 'Z')
	{
		COLORREF color = pDoc->m_BrushColor;
		CColorDialog dlg(color);
		if (dlg.DoModal() == IDOK)
		{
			pDoc->m_BrushColor = dlg.GetColor();
		}
	}
	
	

	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
