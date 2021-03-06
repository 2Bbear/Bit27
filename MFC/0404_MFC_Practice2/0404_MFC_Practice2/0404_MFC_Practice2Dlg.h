
// 0404_MFC_Practice2Dlg.h : header file
//

#pragma once

class SerchMember;

// CMy0404MFCPractice2Dlg dialog
class CMy0404MFCPractice2Dlg : public CDialog 
{
// Construction
public:
	CMy0404MFCPractice2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY0404_MFC_PRACTICE2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
//Attribute
public:
	vector <MEMBER> m_MemberList;
	SerchMember * pModaless;
	int sssss;
	
//Methode
public:
	//Print vector m_MemberList;
	void printMemberList();
	//Setting ListControlColum;
	void settingListColum(CListCtrl *pList,int n=0);
	
	//Print MemberInformation in Edit
	void printMemberInformation(MEMBER* _p);

	virtual void Serialize(CArchive& ar);
// Implementation

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButtonMainSignup();
	afx_msg void OnBnClickedButtonMainModify();
	afx_msg void OnBnClickedButtonMainDelete();
	afx_msg void OnBnClickedButtonMainSerchmember();

	CListCtrl m_MemberListControl;

	CString m_tempName;
	CString m_tempPhone;
	int m_tempAge;
	CString m_tempGender;
	COleDateTime m_tempData;



	
};
