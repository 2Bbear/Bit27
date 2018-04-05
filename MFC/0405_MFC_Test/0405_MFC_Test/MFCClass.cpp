// MFCClass.cpp : implementation file
//

#include "stdafx.h"
#include "0405_MFC_Test.h"
#include "MFCClass.h"
#include"SelectDlg.h"

// MFCClass

IMPLEMENT_DYNCREATE(MFCClass, CFormView)

MFCClass::MFCClass():CFormView(IDD)
{
	m_modaless = NULL;
}

MFCClass::~MFCClass()
{
}

BEGIN_MESSAGE_MAP(MFCClass, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &MFCClass::OnBnClickedButton1)
END_MESSAGE_MAP()


// MFCClass drawing

void MFCClass::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// MFCClass diagnostics

#ifdef _DEBUG
void MFCClass::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void MFCClass::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// MFCClass message handlers


void MFCClass::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	
	if (m_modaless->GetSafeHwnd())
	{
		m_modaless = new SelectDlg;
		m_modaless->Create(IDD_DIALOG1);
		m_modaless->ShowWindow(SW_SHOW);

	}
	else
	{
		m_modaless->Create(IDD_DIALOG1);
		m_modaless->ShowWindow(SW_SHOW);
	}

}
