#pragma once


// signup dialog

class signup : public CDialogEx
{
	DECLARE_DYNAMIC(signup)

public:
	signup(vector<MEMBER> * _target,CWnd* pParent = nullptr);   // standard constructor
	virtual ~signup();
// Attributes
public:
	vector<MEMBER> * target;
//Operator
public:

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SIGNUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_tempName;
	int m_tempAge;
	CString m_tempPhone;
	CString m_tempGender;
	COleDateTime m_tempDate;
};
