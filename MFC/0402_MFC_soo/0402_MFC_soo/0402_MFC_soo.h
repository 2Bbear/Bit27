
// 0402_MFC_soo.h : 0402_MFC_soo ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMy0402_MFC_sooApp:
// �� Ŭ������ ������ ���ؼ��� 0402_MFC_soo.cpp�� �����Ͻʽÿ�.
//

class CMy0402_MFC_sooApp : public CWinApp
{
public:
	CMy0402_MFC_sooApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy0402_MFC_sooApp theApp;
