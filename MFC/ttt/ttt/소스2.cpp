// CFrameWnd class �� ����ؼ� ������ �����.

#include <afxwin.h>

class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance()
	{
		CFrameWnd* pFrame = new CFrameWnd;

		// ���������� CreateWindowEx()�� ���� �ȴ�.
		pFrame->Create(0, TEXT("Hello, MFC"));

		// ������ ������ HWND�� ��� ������ ?
		pFrame->ShowWindow(SW_SHOW);
		pFrame->UpdateWindow();

		// �ݵ�� �����ؾ� �Ѵ�. CWnd* m_pMainWnd; �� ����Ǿ� �ִ�.//cWind�� ���� ���̴� ��ü���� �ֻ��� �θ��
		m_pMainWnd = pFrame;

		// �޼��� ������ �����϶�� �ǹ�
		return TRUE;
	}
};

CHelloApp theApp;
