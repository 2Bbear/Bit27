
// 0405_MFC_Test.h : main header file for the 0405_MFC_Test application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy0405MFCTestApp:
// See 0405_MFC_Test.cpp for the implementation of this class
//

class CMy0405MFCTestApp : public CWinApp
{
public:
	CMy0405MFCTestApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy0405MFCTestApp theApp;
