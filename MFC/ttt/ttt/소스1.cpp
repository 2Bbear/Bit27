// App�� ExitInstance() ������ �ϱ� 

// �ݵ�� �θ��� ExitInstance()�� ȣ���ؾ� �� ??


#include <afxwin.h>

class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		AfxMessageBox(TEXT("Hello, MFC"));
		return FALSE;
	}
	virtual int ExitInstance()
	{
		AfxMessageBox(TEXT("ExitInstance"));
		return CWinApp::ExitInstance();
	}
};

CHelloApp theApp;