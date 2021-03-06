#pragma once


// SighUp dialog

class SighUp : public CDialogEx
{
	DECLARE_DYNAMIC(SighUp)

public:
	SighUp(vector<MEMBER> * _p,CWnd* pParent = nullptr);   // standard constructor
	virtual ~SighUp();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODAL_SIGNUP };
#endif

//Attribute
public:
	vector<MEMBER> * m_pMemberList;
//Methode
public:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//Get data in Edit
	afx_msg void OnBnClickedButtonSignupOk();
	//End of Dlg
	afx_msg void OnBnClickedButtonSignupCancel();
	//Edit Data
	CString m_tempName;
	CString m_tempPhone;
	int m_tempAge;
	CString m_tempGender;
	COleDateTime m_tempData;
	
};
