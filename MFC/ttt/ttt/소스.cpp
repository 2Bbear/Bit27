// 가장 간단한 MFC Code : 

#include <afxwin.h>

class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		//Afx 접두어는 전역함수 , 안 붙으면 멤버함수
		AfxMessageBox(TEXT("Hello, MFC"));
		//API 코드를 쓸때는 :: 을 앞에 붙인다.
		::MessageBox(0, TEXT("asd"), TEXT(""), 0,);
		return FALSE;
	}
};

CHelloApp theApp;
