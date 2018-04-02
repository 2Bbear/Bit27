
// 0402_MFC_sooView.h : CMy0402_MFC_sooView 클래스의 인터페이스
//

#pragma once


class CMy0402_MFC_sooView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy0402_MFC_sooView();
	DECLARE_DYNCREATE(CMy0402_MFC_sooView)

// 특성입니다.
public:
	CMy0402_MFC_sooDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMy0402_MFC_sooView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // 0402_MFC_sooView.cpp의 디버그 버전
inline CMy0402_MFC_sooDoc* CMy0402_MFC_sooView::GetDocument() const
   { return reinterpret_cast<CMy0402_MFC_sooDoc*>(m_pDocument); }
#endif

