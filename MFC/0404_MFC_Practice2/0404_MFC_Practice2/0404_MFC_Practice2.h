
// 0404_MFC_Practice2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy0404MFCPractice2App:
// See 0404_MFC_Practice2.cpp for the implementation of this class
//

class CMy0404MFCPractice2App : public CWinApp
{
public:
	CMy0404MFCPractice2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy0404MFCPractice2App theApp;
