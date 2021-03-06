#pragma once


// SearchDlg dialog
class CMy0404MFCMemberManagerView;

class SearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SearchDlg)

public:
	SearchDlg(CMy0404MFCMemberManagerView* _parents,CWnd* pParent = nullptr);   // standard constructor
	virtual ~SearchDlg();

//Attribute
public:
	CMy0404MFCMemberManagerView * parents;
	vector<MEMBER> * parentsMemberList;

//Operations
public:
	//Finding member in Member List
	MEMBER* findMemberName(const CString str);
//Override
public:
	virtual void PostNcDestroy();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEARCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();


	CString findname;

	afx_msg void OnBnClickedCancel();
};
