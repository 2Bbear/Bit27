// ���� ������ MFC Code : 

#include <afxwin.h>

class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		//Afx ���ξ�� �����Լ� , �� ������ ����Լ�
		AfxMessageBox(TEXT("Hello, MFC"));
		//API �ڵ带 ������ :: �� �տ� ���δ�.
		::MessageBox(0, TEXT("asd"), TEXT(""), 0,);
		return FALSE;
	}
};

CHelloApp theApp;
