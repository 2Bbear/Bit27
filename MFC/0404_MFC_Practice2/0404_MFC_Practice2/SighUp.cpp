// SighUp.cpp : implementation file
//

#include "stdafx.h"
#include "0404_MFC_Practice2.h"
#include "SighUp.h"
#include "afxdialogex.h"


// SighUp dialog

IMPLEMENT_DYNAMIC(SighUp, CDialogEx)

SighUp::SighUp(vector<MEMBER> * _p,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODAL_SIGNUP, pParent)
{
	m_pMemberList = _p;

}

SighUp::~SighUp()
{
}



void SighUp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Text(pDX, IDC_EDIT1, m_tempName);
	DDX_Text(pDX, IDC_EDIT7, m_tempPhone);
	//DDX_CBString(pDX, IDC_EDIT7, m_tempPhone);
	DDX_Text(pDX, IDC_EDIT8, m_tempAge);
	DDX_Text(pDX, IDC_EDIT9, m_tempGender);
	DDX_Text(pDX, IDC_EDIT10, m_tempData);
}


BEGIN_MESSAGE_MAP(SighUp, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SIGNUP_OK, &SighUp::OnBnClickedButtonSignupOk)
	ON_BN_CLICKED(IDC_BUTTON_SIGNUP_CANCEL, &SighUp::OnBnClickedButtonSignupCancel)
END_MESSAGE_MAP()


// SighUp message handlers


void SighUp::OnBnClickedButtonSignupOk()
{
	// TODO: Add your control notification handler code here

	//Get Data in EditControll
	UpdateData();
	//temp MEMBER setting 
	MEMBER tempMember;
	//Name
	tempMember.name = m_tempName.GetString();
	//Phone
	tempMember.phone = m_tempPhone;
	//Age
	tempMember.age = m_tempAge;
	//Gender
	tempMember.gender =(char) m_tempGender.GetAt(0);
	//Data
	tempMember.data = m_tempData;
	
	//Save Member Struct
	m_pMemberList->push_back(tempMember);

	CDialogEx::OnOK();
}


void SighUp::OnBnClickedButtonSignupCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
