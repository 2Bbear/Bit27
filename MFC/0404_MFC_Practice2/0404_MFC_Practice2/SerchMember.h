#pragma once


// SerchMember dialog
class CMy0404MFCPractice2Dlg;

class SerchMember : public CDialogEx
{
	DECLARE_DYNAMIC(SerchMember)

public:
	SerchMember(CMy0404MFCPractice2Dlg* mainMenu,MEMBER * result,vector<MEMBER> * _p,CWnd* pParent = nullptr);   // standard constructor
	virtual ~SerchMember();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODALESS_MEMBERSEARCH };
#endif

//Attribute
public:
	vector<MEMBER> * m_pMemberList;
	MEMBER * m_result;
	CMy0404MFCPractice2Dlg * m_mainMenu;
//Methode
public:
	//Finding member in Member List
	void findMemberName(const CString str);

	//printMember in MainDlg
	void printMemberInformation(CMy0404MFCPractice2Dlg * target,MEMBER * _p);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CString m_cluename;
	afx_msg void OnBnClickedButtonSearchmeberSerch();
	afx_msg void OnBnClickedButton2();
	virtual void PostNcDestroy();





};
