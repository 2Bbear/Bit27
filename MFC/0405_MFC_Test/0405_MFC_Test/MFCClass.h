#pragma once


// MFCClass view
class SelectDlg;
class MFCClass : public CFormView
{
	DECLARE_DYNCREATE(MFCClass)

	//Attribute
public:
	//Operations
public:
	SelectDlg * m_modaless;


protected:
	MFCClass();           // protected constructor used by dynamic creation
	virtual ~MFCClass();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	enum {IDD= IDD_FORMVIEW};
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};


