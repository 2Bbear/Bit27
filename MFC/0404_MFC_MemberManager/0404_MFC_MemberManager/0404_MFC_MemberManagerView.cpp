
// 0404_MFC_MemberManagerView.cpp : implementation of the CMy0404MFCMemberManagerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "0404_MFC_MemberManager.h"
#endif

#include "0404_MFC_MemberManagerDoc.h"
#include "0404_MFC_MemberManagerView.h"

#include "signup.h"
#include "SearchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy0404MFCMemberManagerView

IMPLEMENT_DYNCREATE(CMy0404MFCMemberManagerView, CFormView)

BEGIN_MESSAGE_MAP(CMy0404MFCMemberManagerView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_SIGNUP, &CMy0404MFCMemberManagerView::OnBnClickedButtonMainSignup)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_SEARCH, &CMy0404MFCMemberManagerView::OnBnClickedButtonMainSearch)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_MODIFY, &CMy0404MFCMemberManagerView::OnBnClickedButtonMainModify)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_DELETE, &CMy0404MFCMemberManagerView::OnBnClickedButtonMainDelete)
END_MESSAGE_MAP()

// CMy0404MFCMemberManagerView construction/destruction

CMy0404MFCMemberManagerView::CMy0404MFCMemberManagerView()
	: CFormView(IDD_MY0404_MFC_MEMBERMANAGER_FORM)
{
	// TODO: add construction code here

	
}

CMy0404MFCMemberManagerView::~CMy0404MFCMemberManagerView()
{
}

void CMy0404MFCMemberManagerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAIN_MEMBERLIST, m_MemberListControl);

	DDX_Text(pDX, IDC_EDIT1, m_tempName);
	DDX_Text(pDX, IDC_EDIT2, m_tempPhone);
	DDX_Text(pDX, IDC_EDIT4, m_tempAge);
	DDX_Text(pDX, IDC_EDIT3, m_tempGender);
	DDX_Text(pDX, IDC_EDIT5, m_tempData);
	DDX_Control(pDX, IDC_STATIC_MAIN_IMAGE, m_ctlPic1);
	//DDX_Text(pDX, IDC_STATIC_MAIN_IMAGE, m_ctlPic1);

}

void CMy0404MFCMemberManagerView::printMemberList()
{
	//Initailize list page
	m_MemberListControl.DeleteAllItems();

	//Print list page
	for (int i = 0; i<(int)(*m_MemberList).size(); i++)
	{
		//이름
		m_MemberListControl.InsertItem(i, (*m_MemberList)[i].name);
		//성별
		m_MemberListControl.SetItem(i, 1, LVIF_TEXT, (*m_MemberList)[i].gender, 0, 0, 0, NULL);
		//전화번호
		m_MemberListControl.SetItem(i, 2, LVIF_TEXT, (*m_MemberList)[i].phone, 0, 0, 0, NULL);
	}
	UpdateData();
}

void CMy0404MFCMemberManagerView::settingListColum(CListCtrl * pList, int n)
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

void CMy0404MFCMemberManagerView::printMemberInformation(MEMBER * _p)
{
	GetDlgItem(IDC_EDIT1)->SetWindowTextW(_p->name);
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(_p->phone);
	TCHAR buf[20];
	wsprintf(buf,TEXT("%d"), _p->age);
	GetDlgItem(IDC_EDIT4)->SetWindowTextW(buf);
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(_p->gender);
	GetDlgItem(IDC_EDIT5)->SetWindowTextW(_p->date.Format("%Y-%m-%d %H:%M:%S"));
}

int CMy0404MFCMemberManagerView::deleteMember(MEMBER * _p)
{
	int idx=-1 ;
	for (int i = 0; i<(int)(*m_MemberList).size(); i++)
	{
		if ((*m_MemberList)[i].name.Compare(_p->name) == 0)
		{
			idx = i;
			break;
		}
		else
		{

		}
		
	}
	if (idx!=-1)
	{
		vector<MEMBER> ::iterator itor;
		itor = (*m_MemberList).begin();
		itor += idx;

		(*m_MemberList).erase(itor);
		MEMBER clear;
		clear.name = TEXT("");
		clear.age = 0;
		clear.date = NULL;
		clear.gender = TEXT("");
		clear.phone = TEXT("");
			
		printMemberInformation(&clear);
		return 0;
	}
	return -1;

}

int CMy0404MFCMemberManagerView::modifyMember(MEMBER * _p)
{
	return 0;
}

BOOL CMy0404MFCMemberManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMy0404MFCMemberManagerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	//ToDo
	settingListColum(&m_MemberListControl, 0);
	m_SearchModaless = NULL;
	m_MemberList = &(GetDocument()->m_MemberList);
	GetDocument()->m_mainDlg = this;
}


// CMy0404MFCMemberManagerView diagnostics

#ifdef _DEBUG
void CMy0404MFCMemberManagerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy0404MFCMemberManagerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy0404MFCMemberManagerDoc* CMy0404MFCMemberManagerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy0404MFCMemberManagerDoc)));
	return (CMy0404MFCMemberManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy0404MFCMemberManagerView message handlers


void CMy0404MFCMemberManagerView::OnBnClickedButtonMainSignup()
{
	// TODO: Add your control notification handler code here
	signup modal(m_MemberList);
	if (modal.DoModal()==IDOK)
	{
		printMemberList();
	}
}


void CMy0404MFCMemberManagerView::OnBnClickedButtonMainSearch()
{
	// TODO: Add your control notification handler code here
	//Image print code
	HBITMAP hbit;
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2));
	m_ctlPic1.SetBitmap(hbit);
	
	
	//여기 OK나올때 메모리 누수 발생한다

	if (m_SearchModaless==NULL)
	{
		m_SearchModaless = new SearchDlg(this);
		m_SearchModaless->Create(IDD_DIALOG_SEARCH);
		m_SearchModaless->ShowWindow(SW_SHOW);
	}
	else
	{
		m_SearchModaless->SetFocus();
	}
}


void CMy0404MFCMemberManagerView::OnBnClickedButtonMainModify()
{
	// TODO: Add your control notification handler code here

}


void CMy0404MFCMemberManagerView::OnBnClickedButtonMainDelete()
{
	// TODO: Add your control notification handler code here

	UpdateData();
	
	MEMBER target;
	target.name = m_tempName;
	if (deleteMember(&target)==-1)
	{
		AfxMessageBox(TEXT("해당 멤버와 같은 정보가 없어 삭제에 실패했습니다."));
	}
	else
	{
		printMemberList();
	}
	


}
