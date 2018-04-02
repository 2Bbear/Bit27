// 가장 간단한 MFC Code : 

#include <afxwin.h>

class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		AfxMessageBox(TEXT("Hello, MFC"));
		return FALSE;
	}
};

CHelloApp theApp;
