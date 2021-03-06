
// 0404_MFC_PracticeView.h : interface of the CMy0404MFCPracticeView class
//

#pragma once


class CMy0404MFCPracticeView : public CFormView
{
protected: // create from serialization only
	CMy0404MFCPracticeView();
	DECLARE_DYNCREATE(CMy0404MFCPracticeView)

// Attributes
public:
	CMy0404MFCPracticeDoc* GetDocument() const;
	enum { IDD = IDD_DIALOG_MAIN};
// Operations
public:

// Overrides
public:
	//virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMy0404MFCPracticeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 0404_MFC_PracticeView.cpp
inline CMy0404MFCPracticeDoc* CMy0404MFCPracticeView::GetDocument() const
   { return reinterpret_cast<CMy0404MFCPracticeDoc*>(m_pDocument); }
#endif

