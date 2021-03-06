#pragma once


// CLeftBottomView view

class CLeftBottomView : public CListView
{
	DECLARE_DYNCREATE(CLeftBottomView)

protected:
	CLeftBottomView();           // protected constructor used by dynamic creation
	virtual ~CLeftBottomView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


