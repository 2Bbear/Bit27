#include"std.h"

static HWND g_hExamList1;

void OnInitExam(HWND hDlg)
{
	//현재 문제 풀의 갯수를 출력
	int count;
	wbdb_GetExamPoolCount(&count);
	SetDlgItemInt(hDlg, IDC_EXAM_EDIT1,count,0);

	//list 핸들
	g_hExamList1 =GetDlgItem(hDlg, IDC_EXMA_LIST1);
}

void OnInsertExam(HWND hDlg)
{
	//만들 문제 개수 가져오기
	int poolcount; // 서버로부터 얻어올 정보
	poolcount = GetDlgItemInt(hDlg, IDC_EXAM_EDIT1, 0, 0);

	int * exampoolidx=(int *)malloc(sizeof(int)*poolcount);//서버로부터 얻어올 문제의 풀 번호
	
	wbdb_GetExamPoolIdx(exampoolidx);
	
	int examcount; 
	examcount = GetDlgItemInt(hDlg, IDC_EXAM_EDIT2, 0, 0);
	//문제 랜덤 생성
	int * buf = (int*)malloc(sizeof(int)*examcount);

	randomexam(buf, examcount, exampoolidx, poolcount);
	//리스트 박스에 출력
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
	
	//전송




	//마지막 처리
	free(buf);
	free(exampoolidx);
}
void OnInsertExam2(HWND hDlg)
{
	//리스트박스에 저장된 데이터의 개수 파악
	int count;
	count =SendMessage(g_hExamList1, LB_GETCOUNT, 0, 0);
	//2,3 과정을 데이터 개수만큼 반복
	for (int i=0;i<count;i++)
	{
		//sendmessage를 호출
		TCHAR buf[10];
		SendMessage(g_hExamList1, LB_GETTEXT, i, (LPARAM)buf);
		//db저장 요청
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

//대화 상자 프로시저
BOOL CALLBACK examDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
		// Dialog가 처음 나타날때 발생. 각 콘트롤을 초기화 한다.
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
	return FALSE; // 메세지 처리를 안한경우..
}
