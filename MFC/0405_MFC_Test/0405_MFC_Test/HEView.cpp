// HEView.cpp : implementation file
//

#include "stdafx.h"
#include "0405_MFC_Test.h"
#include "HEView.h"


// HEView

IMPLEMENT_DYNCREATE(HEView, CHtmlEditView)

HEView::HEView()
{

}

HEView::~HEView()
{
}

BEGIN_MESSAGE_MAP(HEView, CHtmlEditView)
END_MESSAGE_MAP()


// HEView diagnostics

#ifdef _DEBUG
void HEView::AssertValid() const
{
	CHtmlEditView::AssertValid();
}

#ifndef _WIN32_WCE
void HEView::Dump(CDumpContext& dc) const
{
	CHtmlEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// HEView message handlers
