// signup.cpp : implementation file
//

#include "stdafx.h"
#include "0404_MFC_MemberManager.h"
#include "signup.h"
#include "afxdialogex.h"



// signup dialog

IMPLEMENT_DYNAMIC(signup, CDialogEx)

signup::signup(vector<MEMBER> * _target, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SIGNUP, pParent)
{
	target = _target;
}

signup::~signup()
{
}

void signup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_tempName);
	DDX_Text(pDX, IDC_EDIT2, m_tempAge);
	DDX_Text(pDX, IDC_EDIT3, m_tempPhone);
	DDX_Text(pDX, IDC_EDIT4, m_tempGender);
	DDX_Text(pDX, IDC_EDIT5, m_tempDate);
}


BEGIN_MESSAGE_MAP(signup, CDialogEx)
	ON_BN_CLICKED(IDOK, &signup::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &signup::OnBnClickedCancel)
END_MESSAGE_MAP()


// signup message handlers


void signup::OnBnClickedOk()
{
	
	// TODO: Add your control notification handler code here
	if (target!=NULL)
	{
		MEMBER temp;
		UpdateData();

		temp.name = m_tempName;
		temp.age = m_tempAge;
		temp.phone = m_tempPhone;
		temp.gender = m_tempGender;
		temp.date = m_tempDate;

		target->push_back(temp);
	}
	
	CDialogEx::OnOK();
}


void signup::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
