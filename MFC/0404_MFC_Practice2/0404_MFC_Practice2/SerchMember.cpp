// SerchMember.cpp : implementation file
//

#include "stdafx.h"
#include "0404_MFC_Practice2.h"
#include "SerchMember.h"
#include "afxdialogex.h"
#include "0404_MFC_Practice2Dlg.h"


// SerchMember dialog

IMPLEMENT_DYNAMIC(SerchMember, CDialogEx)

SerchMember::SerchMember(CMy0404MFCPractice2Dlg* mainMenu, MEMBER * result,vector<MEMBER> * _p,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODALESS_MEMBERSEARCH, pParent)
{
	m_pMemberList = _p;
	
	m_result = result;
	m_mainMenu = mainMenu;
}

SerchMember::~SerchMember()
{
}

void SerchMember::findMemberName(const CString str)
{
	
	for (int i =0;i<(int)m_pMemberList->size();i++)
	{
		if ((*m_pMemberList)[i].name.Compare(str) == 0)
		{
			
			m_result = &((*m_pMemberList)[i]);
		
			break;
		}
	}
}

void SerchMember::printMemberInformation(CMy0404MFCPractice2Dlg * target, MEMBER * _p)
{
	target->printMemberInformation(_p);
}



void SerchMember::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERCHMEMBER, m_cluename);
}


BEGIN_MESSAGE_MAP(SerchMember, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_SERCHMEMBER, &SerchMember::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON_SEARCHMEBER_SERCH, &SerchMember::OnBnClickedButtonSearchmeberSerch)
	ON_BN_CLICKED(IDC_BUTTON2, &SerchMember::OnBnClickedButton2)
END_MESSAGE_MAP()


// SerchMember message handlers


void SerchMember::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here


}


void SerchMember::OnBnClickedButtonSearchmeberSerch()
{
	// TODO: Add your control notification handler code here

	//Getting Data in EditControl
	UpdateData();
	//Finding member
	findMemberName(m_cluename);

	//Printing MemberInformation in MainDlg's EditControl
	printMemberInformation(m_mainMenu,m_result);

	
	
}


void SerchMember::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	
	CDialogEx::OnCancel();
}


void SerchMember::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();
	
}
