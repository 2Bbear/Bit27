
// 0402_MFC_sooView.cpp : CMy0402_MFC_sooView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CMy0402_MFC_sooView ����/�Ҹ�

CMy0402_MFC_sooView::CMy0402_MFC_sooView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMy0402_MFC_sooView::~CMy0402_MFC_sooView()
{
}

BOOL CMy0402_MFC_sooView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy0402_MFC_sooView �׸���

void CMy0402_MFC_sooView::OnDraw(CDC* pDC)
{
	CMy0402_MFC_sooDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
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


// CMy0402_MFC_sooView ����

#ifdef _DEBUG
void CMy0402_MFC_sooView::AssertValid() const
{
	CView::AssertValid();
}

void CMy0402_MFC_sooView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy0402_MFC_sooDoc* CMy0402_MFC_sooView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy0402_MFC_sooDoc)));
	return (CMy0402_MFC_sooDoc*)m_pDocument;
}
#endif //_DEBUG


 //CMy0402_MFC_sooView �޽��� ó����
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	wsprintf(buf, TEXT("���尳��:%d��\n "), GetDocument()->m_ShapeList.size());
	AfxGetMainWnd()->SetWindowTextW(buf);
	CView::OnLButtonDown(nFlags, point);



	CView::OnLButtonDown(nFlags, point);
}


void CMy0402_MFC_sooView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
