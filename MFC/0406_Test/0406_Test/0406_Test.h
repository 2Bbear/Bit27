
// 0406_Test.h : main header file for the 0406_Test application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy0406TestApp:
// See 0406_Test.cpp for the implementation of this class
//

class CMy0406TestApp : public CWinApp
{
public:
	CMy0406TestApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy0406TestApp theApp;
