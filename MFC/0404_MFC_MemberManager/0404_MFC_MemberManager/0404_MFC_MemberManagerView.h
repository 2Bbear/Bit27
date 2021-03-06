
// 0404_MFC_MemberManagerView.h : interface of the CMy0404MFCMemberManagerView class
//

#pragma once
class SearchDlg;
class CMy0404MFCMemberManagerDoc;
class CMy0404MFCMemberManagerView : public CFormView
{
protected: // create from serialization only
	CMy0404MFCMemberManagerView();
	DECLARE_DYNCREATE(CMy0404MFCMemberManagerView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MY0404_MFC_MEMBERMANAGER_FORM };
#endif


// Attributes
public:
	CMy0404MFCMemberManagerDoc * GetDocument() const;
	vector<MEMBER> *m_MemberList;
	//Search Modaless Window pointer
	SearchDlg * m_SearchModaless;
// Operations
public:
	//Print vector m_MemberList;
	void printMemberList();
	//Setting ListControlColum;
	void settingListColum(CListCtrl *pList, int n = 0);

	//Print MemberInformation in Edit
	void printMemberInformation(MEMBER* _p);
	//Delete Member in MemberList -1 error , 0 success
	int deleteMember(MEMBER* _p);
	//Modify Member
	int modifyMember(MEMBER * _p);

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CMy0404MFCMemberManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMainSignup();
	afx_msg void OnBnClickedButtonMainSearch();
	afx_msg void OnBnClickedButtonMainModify();
	afx_msg void OnBnClickedButtonMainDelete();

	CListCtrl m_MemberListControl;

	CString m_tempName;
	CString m_tempPhone;
	int m_tempAge;
	CString m_tempGender;
	COleDateTime m_tempData;

	CStatic m_ctlPic1;
};

#ifndef _DEBUG  // debug version in 0404_MFC_MemberManagerView.cpp
inline CMy0404MFCMemberManagerDoc* CMy0404MFCMemberManagerView::GetDocument() const
   { return reinterpret_cast<CMy0404MFCMemberManagerDoc*>(m_pDocument); }
#endif

