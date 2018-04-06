#pragma once


// ModalDlg dialog

class CMy0406TestView;

class ModalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ModalDlg)

public:
	ModalDlg(CMy0406TestView * p,CWnd* pParent = nullptr);   // standard constructor
	virtual ~ModalDlg();

//Attribute
public:
	//Dlg
	CComboBox m_ComboBox;
	CEdit xPosition;
	CEdit yPosition;
	CMy0406TestView * parent;
	//Value

	//Override
public:

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnBnClickedOk();
};
