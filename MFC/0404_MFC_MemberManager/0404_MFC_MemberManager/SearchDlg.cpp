// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "0404_MFC_MemberManager.h"
#include "SearchDlg.h"
#include "afxdialogex.h"
#include "0404_MFC_MemberManagerView.h"

// SearchDlg dialog

IMPLEMENT_DYNAMIC(SearchDlg, CDialogEx)

SearchDlg::SearchDlg(CMy0404MFCMemberManagerView* _parents,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEARCH, pParent)
{
	parents = _parents;
	parentsMemberList = (parents->m_MemberList);
}

SearchDlg::~SearchDlg()
{
}

MEMBER* SearchDlg::findMemberName(const CString str)
{
	for (int i = 0; i<(int)parentsMemberList->size(); i++)
	{
		if ((*parentsMemberList)[i].name.Compare(str) == 0)
		{

			return &((*parentsMemberList)[i]);

		}
	}
	return NULL;
}

void SearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, findname);
}


BEGIN_MESSAGE_MAP(SearchDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &SearchDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &SearchDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// SearchDlg message handlers


void SearchDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (parentsMemberList!=NULL)
	{
		UpdateData();
		MEMBER * temp= findMemberName(findname);
		if (temp != NULL)
		{
			parents->printMemberInformation(temp);
		}
		
	
	}
	else
	{
		//parents->m_SearchModaless = NULL;
		delete this;
	}
	

	//CDialogEx::OnOK();
}


void SearchDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here

	
	DestroyWindow();

	//CDialogEx::OnCancel();
}
void SearchDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	//delete parents->m_SearchModaless;
	parents->m_SearchModaless = NULL;
	
	CDialogEx::PostNcDestroy();

}
