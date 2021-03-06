// ModalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "0406_Test.h"
#include "ModalDlg.h"
#include "afxdialogex.h"


#include"0406_TestView.h"

#include"0406_TestDoc.h"

// ModalDlg dialog

IMPLEMENT_DYNAMIC(ModalDlg, CDialogEx)

ModalDlg::ModalDlg(CMy0406TestView * p,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	parent = p;
}

ModalDlg::~ModalDlg()
{
}


void ModalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
	DDX_Control(pDX, IDC_EDIT1, xPosition);
	DDX_Control(pDX, IDC_EDIT2, yPosition);
	//Init ComboBox
	m_ComboBox.AddString(TEXT("빨간색"));
	m_ComboBox.AddString(TEXT("녹  색"));
	m_ComboBox.AddString(TEXT("파란색"));
	if (((CMy0406TestDoc*)parent->GetDocument())->m_CurDate.color==RGB(255,0,0))
	{
		m_ComboBox.SetCurSel(0);
	}
	else if (((CMy0406TestDoc*)parent->GetDocument())->m_CurDate.color == RGB(0, 255, 0))
	{
		m_ComboBox.SetCurSel(1);
	}
	else if (((CMy0406TestDoc*)parent->GetDocument())->m_CurDate.color == RGB(0, 0, 255))
	{
		m_ComboBox.SetCurSel(2);
	}
	
	//Init EditControl
	int x=((CMy0406TestDoc*)parent->GetDocument())->m_CurDate.pt.x;
	int y = ((CMy0406TestDoc*)parent->GetDocument())->m_CurDate.pt.y;
	TCHAR buf[10];
	TCHAR buf2[10];
	wsprintf(buf,TEXT("%d"),x);
	wsprintf(buf2, TEXT("%d"), y);
	xPosition.SetWindowTextW(buf);
	yPosition.SetWindowTextW(buf2);

	
}


BEGIN_MESSAGE_MAP(ModalDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ModalDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ModalDlg message handlers


void ModalDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	//((CMy0406TestDoc*)parent->GetDocument())->m_CurDate
	//Change Color
	int n = m_ComboBox.GetCurSel();
	switch (n)
	{
	case 0:
	{
		((CMy0406TestDoc*)parent->GetDocument())->m_CurDate.color = RGB(255,0,0);
		break;
	}
	case 1:
	{
		((CMy0406TestDoc*)parent->GetDocument())->m_CurDate.color = RGB(0, 255, 0);
		break;
	}
	case 2:
	{
		((CMy0406TestDoc*)parent->GetDocument())->m_CurDate.color = RGB(0, 0, 255);
		break;
	}
	
	default:
		break;
	}

	//Cange Position
	CString xPosit, yPosit;
	xPosition.GetWindowTextW(xPosit);
	yPosition.GetWindowTextW(yPosit);

	((CMy0406TestDoc*)parent->GetDocument())->m_CurDate.pt.x = _wtoi(xPosit);
	((CMy0406TestDoc*)parent->GetDocument())->m_CurDate.pt.y = _wtoi(yPosit);



	parent->Invalidate();


	CDialogEx::OnOK();
}
