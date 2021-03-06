
// 0404_MFC_Practice2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "0404_MFC_Practice2.h"
#include "0404_MFC_Practice2Dlg.h"
#include "afxdialogex.h"

#include "SighUp.h"
#include"SerchMember.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy0404MFCPractice2Dlg dialog



CMy0404MFCPractice2Dlg::CMy0404MFCPractice2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MY0404_MFC_PRACTICE2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy0404MFCPractice2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAIN_PRINTMEMBER, m_MemberListControl);
	DDX_Text(pDX, IDC_EDIT2, m_tempName);
	DDX_Text(pDX, IDC_EDIT5, m_tempPhone);
	DDX_Text(pDX, IDC_EDIT4, m_tempAge);
	DDX_Text(pDX, IDC_EDIT3, m_tempGender);
	DDX_Text(pDX, IDC_EDIT6, m_tempData);
}

BEGIN_MESSAGE_MAP(CMy0404MFCPractice2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON_MAIN_SIGNUP, &CMy0404MFCPractice2Dlg::OnBnClickedButtonMainSignup)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_MODIFY, &CMy0404MFCPractice2Dlg::OnBnClickedButtonMainModify)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_DELETE, &CMy0404MFCPractice2Dlg::OnBnClickedButtonMainDelete)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_SERCHMEMBER, &CMy0404MFCPractice2Dlg::OnBnClickedButtonMainSerchmember)
END_MESSAGE_MAP()




void CMy0404MFCPractice2Dlg::printMemberList()
{
	//Initailize list page
	m_MemberListControl.DeleteAllItems();
	
	//Print list page
	for (int i=0;i<(int)m_MemberList.size();i++)
	{
		//이름
		m_MemberListControl.InsertItem(i, m_MemberList[i].name);
		
		//성별
		TCHAR buf2[20];
		wsprintf(buf2,TEXT("%c"), m_MemberList[i].gender);
		m_MemberListControl.SetItem(i,1,LVIF_TEXT,buf2,0,0,0,NULL);
		//전화번호
		m_MemberListControl.SetItem(i, 2, LVIF_TEXT, m_MemberList[i].phone, 0, 0, 0, NULL);
	}


}
void  CMy0404MFCPractice2Dlg::settingListColum(CListCtrl *pList, int n)
{
	if (n==0)
	{
		//Setting Colum
		LVCOLUMNW col;
		col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		col.fmt = LVCFMT_LEFT;
		//0번
		col.cx = 60;
		col.pszText = TEXT("이름");
		col.iSubItem = 0;
		m_MemberListControl.InsertColumn(0, &col);
		//1번
		col.cx = 60;
		col.pszText = TEXT("성별");
		m_MemberListControl.InsertColumn(1, &col);
		//2번
		col.cx = 150;
		col.pszText = TEXT("전화번호");
		m_MemberListControl.InsertColumn(2, &col);
	}
	
}
void CMy0404MFCPractice2Dlg::printMemberInformation(MEMBER * _p)
{
	
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(_p->name);
	GetDlgItem(IDC_EDIT5)->SetWindowTextW(_p->phone);
	TCHAR buf[10];
	wsprintf(buf, TEXT("%d"), _p->age);
	GetDlgItem(IDC_EDIT4)->SetWindowTextW(buf);
	TCHAR buf2[10];
	wsprintf(buf2, TEXT("%c"), _p->gender);
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(buf2);
	GetDlgItem(IDC_EDIT6)->SetWindowTextW(_p->data.Format("%Y-%m-%d %H:%M:%S"));
	//????시간이 뭔지 몰라도 출력은 됨

	
	UpdateData();


}
void CMy0404MFCPractice2Dlg::Serialize(CArchive & ar)
{
	ar.SetStoreParams();
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		int size = (int)m_MemberList.size();
		ar << size;
		
	}
	else
	{
		// TODO: add loading code here
		int size;
		ar >> size;
		AfxMessageBox(size);
	}

}
// CMy0404MFCPractice2Dlg message handlers
BOOL CMy0404MFCPractice2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//Setting Colum
	settingListColum(&m_MemberListControl, 0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy0404MFCPractice2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy0404MFCPractice2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy0404MFCPractice2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CMy0404MFCPractice2Dlg::OnBnClickedButtonMainSignup()
{
	// TODO: Add your control notification handler code here

	SighUp temp(&m_MemberList);
	if (temp.DoModal() == IDOK)
	{
		
		printMemberList();
	}
	else
	{
		
	}

}


void CMy0404MFCPractice2Dlg::OnBnClickedButtonMainModify()
{
	// TODO: Add your control notification handler code here
	
}


void CMy0404MFCPractice2Dlg::OnBnClickedButtonMainDelete()
{
	// TODO: Add your control notification handler code here
}


void CMy0404MFCPractice2Dlg::OnBnClickedButtonMainSerchmember()
{


	// TODO: Add your control notification handler code here

		MEMBER resultTemp;
		pModaless = new SerchMember(this,&resultTemp, &m_MemberList);
		pModaless->Create(IDD_MODALESS_MEMBERSEARCH);
		pModaless->ShowWindow(SW_SHOW);
	

		

		

	

	//if (bcheck)
	//{
	//	//End routine==========================================================
	//	AfxMessageBox(TEXT("같은 창을 두번 띄우지 마세요"));
	//	bcheck = false;
	//	delete(pModaless);
	//	return;
	//}
	//else
	//{
	//	MEMBER resultTemp;
	//	pModaless = new SerchMember(&resultTemp, &m_MemberList);
	//	pModaless->Create(IDD_MODALESS_MEMBERSEARCH);
	//	pModaless->ShowWindow(SW_SHOW);
	//	pModaless->setState(&bcheck);

	//	//Printing MemberInformation in MainDlg's EditControl
	//	printMemberInformation(&resultTemp);




	//	if (bcheck)
	//	{
	//		bcheck = true;
	//	}
	//	
	//	
	//}
	

	


}
