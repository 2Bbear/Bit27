
// 0404_MFC_MemberManager.h : main header file for the 0404_MFC_MemberManager application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy0404MFCMemberManagerApp:
// See 0404_MFC_MemberManager.cpp for the implementation of this class
//

class CMy0404MFCMemberManagerApp : public CWinApp
{
public:
	CMy0404MFCMemberManagerApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy0404MFCMemberManagerApp theApp;
