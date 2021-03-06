
// 0405_MFC_TestView.h : interface of the CMy0405MFCTestView class
//

#pragma once

class CMy0405MFCTestDoc;

class CMy0405MFCTestView : public CView
{
protected: // create from serialization only
	CMy0405MFCTestView();
	DECLARE_DYNCREATE(CMy0405MFCTestView)

// Attributes
public:
	CMy0405MFCTestDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMy0405MFCTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in 0405_MFC_TestView.cpp
inline CMy0405MFCTestDoc* CMy0405MFCTestView::GetDocument() const
   { return reinterpret_cast<CMy0405MFCTestDoc*>(m_pDocument); }
#endif

