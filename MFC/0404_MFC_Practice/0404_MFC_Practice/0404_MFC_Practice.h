
// 0404_MFC_Practice.h : main header file for the 0404_MFC_Practice application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy0404MFCPracticeApp:
// See 0404_MFC_Practice.cpp for the implementation of this class
//

class CMy0404MFCPracticeApp : public CWinAppEx
{
public:
	CMy0404MFCPracticeApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy0404MFCPracticeApp theApp;
