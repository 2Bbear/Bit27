
// 0402_MFC_sooView.h : CMy0402_MFC_sooView Ŭ������ �������̽�
//

#pragma once


class CMy0402_MFC_sooView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy0402_MFC_sooView();
	DECLARE_DYNCREATE(CMy0402_MFC_sooView)

// Ư���Դϴ�.
public:
	CMy0402_MFC_sooDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CMy0402_MFC_sooView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // 0402_MFC_sooView.cpp�� ����� ����
inline CMy0402_MFC_sooDoc* CMy0402_MFC_sooView::GetDocument() const
   { return reinterpret_cast<CMy0402_MFC_sooDoc*>(m_pDocument); }
#endif

