// SelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "0405_MFC_Test.h"
#include "SelectDlg.h"
#include "afxdialogex.h"


// SelectDlg dialog

IMPLEMENT_DYNAMIC(SelectDlg, CDialogEx)

SelectDlg::SelectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

SelectDlg::~SelectDlg()
{
}

void SelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SelectDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &SelectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// SelectDlg message handlers


void SelectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}
