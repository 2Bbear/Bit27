#include"std.h"

BOOL OnInitDialog(HWND hDlg)
{
	//db����
	if (wbdb_DBConnect()==FALSE)
	{
		MessageBox(0, TEXT("���ӽ���"), TEXT(""), 0);
	}
	else
	{
		MessageBox(0, TEXT("���Ӽ���"), TEXT(""), 0);
	}

	return TRUE;
}

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//��ư �Է��� �޴� event�� ó���ϱ� ���� ����
	switch (LOWORD(wParam))
	{
	//��ư
		//������¹�ư
	case IDC_MAIN_EXAMPOOL:
	{
		UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
			MAKEINTRESOURCE(IDD_EXAMPOOLDLG),
			hDlg,		// �θ�
			exampoolDlgProc, // �޼��� �Լ�.
			0); // WM_INITDIALOG�� lParam�� ���޵ȴ�.
		if (ret == IDOK) {

		}
		return 0;
	}
	//���� ���ù�ư
	case IDC_MAIN_EXAM:
	{
		UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
			MAKEINTRESOURCE(IDD_EXMADLG),
			hDlg,		// �θ�
			examDlgProc, // �޼��� �Լ�.
			0); // WM_INITDIALOG�� lParam�� ���޵ȴ�.
		if (ret == IDOK) {

		}
		return 0;
	}
	//���۹�ư
	case IDC_MAIN_SENDQUEST:
	{
		return 0;
	}
	case IDCANCEL:
	{
		EndDialog(hDlg, IDCANCEL);	return 0;
	}

	}
	return TRUE;
}
