
// 0406_TestView.h : interface of the CMy0406TestView class
//

#pragma once

class CMy0406TestDoc;

class CMy0406TestView : public CView
{
protected: // create from serialization only
	CMy0406TestView();
	DECLARE_DYNCREATE(CMy0406TestView)

// Attributes
public:
	CMy0406TestDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMy0406TestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On32777();
	afx_msg void On32778();
	afx_msg void On32779();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void On32780();
	afx_msg void On32776();
};

#ifndef _DEBUG  // debug version in 0406_TestView.cpp
inline CMy0406TestDoc* CMy0406TestView::GetDocument() const
   { return reinterpret_cast<CMy0406TestDoc*>(m_pDocument); }
#endif

