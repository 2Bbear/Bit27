// CLeftBottomView.cpp : implementation file
//

#include "stdafx.h"
#include "0405_MFC_Test.h"
#include "CLeftBottomView.h"


// CLeftBottomView

IMPLEMENT_DYNCREATE(CLeftBottomView, CListView)

CLeftBottomView::CLeftBottomView()
{

}

CLeftBottomView::~CLeftBottomView()
{
}

BEGIN_MESSAGE_MAP(CLeftBottomView, CListView)
END_MESSAGE_MAP()


// CLeftBottomView diagnostics

#ifdef _DEBUG
void CLeftBottomView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftBottomView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftBottomView message handlers
