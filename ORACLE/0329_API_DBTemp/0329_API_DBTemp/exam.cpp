#include"std.h"

static HWND g_hExamList1;

void OnInitExam(HWND hDlg)
{
	//���� ���� Ǯ�� ������ ���
	int count;
	wbdb_GetExamPoolCount(&count);
	SetDlgItemInt(hDlg, IDC_EXAM_EDIT1,count,0);

	//list �ڵ�
	g_hExamList1 =GetDlgItem(hDlg, IDC_EXMA_LIST1);
}

void OnInsertExam(HWND hDlg)
{
	//���� ���� ���� ��������
	int poolcount; // �����κ��� ���� ����
	poolcount = GetDlgItemInt(hDlg, IDC_EXAM_EDIT1, 0, 0);

	int * exampoolidx=(int *)malloc(sizeof(int)*poolcount);//�����κ��� ���� ������ Ǯ ��ȣ
	
	wbdb_GetExamPoolIdx(exampoolidx);
	
	int examcount; 
	examcount = GetDlgItemInt(hDlg, IDC_EXAM_EDIT2, 0, 0);
	//���� ���� ����
	int * buf = (int*)malloc(sizeof(int)*examcount);

	randomexam(buf, examcount, exampoolidx, poolcount);
	//����Ʈ �ڽ��� ���
	TCHAR buf2[10];
	for (int i=0;i<poolcount;i++)
	{
	SendMessage(g_hExamList1, LB_DELETESTRING, 0, 0);
	}
	
	for (int i=0;i<examcount;i++)
	{
		wsprintf(buf2, TEXT("%d"), buf[i]);
		SendMessage(g_hExamList1, LB_ADDSTRING, 0, (LPARAM)buf2);
	}
	
	//����




	//������ ó��
	free(buf);
	free(exampoolidx);
}
void OnInsertExam2(HWND hDlg)
{
	//����Ʈ�ڽ��� ����� �������� ���� �ľ�
	int count;
	count =SendMessage(g_hExamList1, LB_GETCOUNT, 0, 0);
	//2,3 ������ ������ ������ŭ �ݺ�
	for (int i=0;i<count;i++)
	{
		//sendmessage�� ȣ��
		TCHAR buf[10];
		SendMessage(g_hExamList1, LB_GETTEXT, i, (LPARAM)buf);
		//db���� ��û
		wbdb_InsertExam(_wtoi(buf));
	}
}
void randomexam(int *_buf,int e_count,int* _exampool,int p_count)
{
	srand((unsigned int(time(0))));

	
	for (int i=0;i<1000;i++)
	{
		int value1 = rand() % p_count;
		int value2 = rand() % p_count;
		int temp = _exampool[value1];
		_exampool[value1] = _exampool[value2];
		_exampool[value2] = temp;
	}
	
	for (int i =0;i<e_count;i++)
	{
		_buf[i] = _exampool[i];
	}

}

//��ȭ ���� ���ν���
BOOL CALLBACK examDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
		// Dialog�� ó�� ��Ÿ���� �߻�. �� ��Ʈ���� �ʱ�ȭ �Ѵ�.
	case WM_INITDIALOG:
	{
		OnInitExam(hDlg);
		return TRUE;
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EXAM_BUTTON1:
		{
			OnInsertExam(hDlg);
			return TRUE;
		}
		case IDC_EXAM_BUTTON2:
		{
			OnInsertExam2(hDlg);
			return TRUE;
		}
		case IDOK:
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
	}
	return FALSE; // �޼��� ó���� ���Ѱ��..
}
