#include"std.h"

HINSTANCE g_hInst;

//��������Ʈ��  ������
vector<Account> * pAcc;

BOOL CALLBACK DlgProc2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	//�ʱ�ȭ event
	case WM_INITDIALOG:
	{
		
		return TRUE;
	}
	//�޼��� �޴� event�� ó���ϱ� ���� ����
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		//Ȯ�� ��ư�� ������ ��
		case IDOK:
		{
		
			//���� =====================================
			Account temp;
			//�̸�
			GetDlgItemText(hDlg, IDC_EDIT11, temp.name, _tcslen(temp.name));
			//�н�����
			GetDlgItemText(hDlg, IDC_EDIT22, temp.password, _tcslen(temp.password));
			//���¹�ȣ
			temp.accountNum=GetDlgItemInt(hDlg, IDC_EDIT33,0,0);
			//���̵�
			GetDlgItemText(hDlg, IDC_EDIT55, temp.id, _tcslen(temp.id));
			//�ܾ�
			_tcscpy(temp.balance,TEXT("0��"));
			//���� ����Ʈ�� ����
			pAcc->push_back(temp);

			//
			//������ â ����
			EndDialog(hDlg, IDCANCEL);
			return 0;
		}
		case IDCANCEL:
		{
			EndDialog(hDlg, IDCANCEL);
			return 0;
		}
		}

		return 0;
	}

	}
	return FALSE;

}

void CAWH_CreateDialogWindow(vector<Account> * _pAcc, HWND hDlg)
{
	pAcc = _pAcc;
	g_hInst = GetModuleHandle(0);
	////�� �ڵ� ��ü�� ���ο� â�� ���� ��
	//UINT ret = DialogBox(g_hInst,// instance 
	//	MAKEINTRESOURCE(IDD_DIALOG2), // ���̾�α� ���� 
	//	0,   // �θ� ������ 
	//	DlgProc2);   // Proc..
	UINT ret = DialogBoxParam(g_hInst,// hinstance
		MAKEINTRESOURCE(IDD_DIALOG2),
		hDlg,		// �θ�
		DlgProc2, // �޼��� �Լ�.
		(LPARAM)11); // WM_INITDIALOG�� lParam�� ���޵ȴ�. //�� �Լ��� ���� ������ ���� ������� �ƹ��͵� ���Ѵ�



}
