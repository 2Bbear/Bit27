#include"std.h"

extern vector<Account> g_AccountList;
extern vector<AccountDetail> g_AccountDetailList;

//왼쪽 리스트컨트롤 핸들
HWND g_hListView;
//오른쪽 리스트컨트롤 핸들
HWND g_hListView2;
//오른쪽 계좌번호edit 핸들
HWND g_hEditAccountNum;
//오른족 이름 edit 핸들
HWND g_hEditName;
//오른쪽 잔액 edit 핸들
HWND g_hEditBalance;

void ui_PopUpCreateAccountWindow(HWND hDlg)
{
	//모달 윈도우 생성
	CAWH_CreateDialogWindow(&g_AccountList,hDlg);
	
	//계좌 내역 생성
	B_CreateAccountDetail(g_AccountList[g_AccountList.size() - 1].accountNum, 0, 0,TEXT("0원"));
	//리스트에 출력하기
	ui_processListPrint(&g_AccountList, g_AccountList.size());
}

void ui_PopUpSerchAccountWindow(HWND hDlg)
{
	TCHAR tempID[50];
	//모달 리스 윈도우 생성
	SAWH_CreateDialogWindow(tempID,hDlg);
}

void ListPrint(Account acc,int _idx)
{
	LVITEM LI;

	LI.mask = LVIF_TEXT;


	//계좌번호
	LI.iItem = _idx;// 행

	LI.iSubItem = 0;//열
	TCHAR buf[50];
	wsprintf(buf,TEXT("%d"),acc.accountNum);
	LI.pszText = buf;			// 첫 번째 아이템
	SendMessage(g_hListView, LVM_INSERTITEM, 0, (LPARAM)&LI);
	//이름
	LI.iSubItem = 1;//열
	LI.pszText = acc.name;			// 첫 번째 아이템
	SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);
	//잔액
	LI.iSubItem = 2;//열
	LI.pszText = TEXT("0원");			// 첫 번째 아이템
	SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);
	//아이디
	LI.iSubItem = 3;//열
	LI.pszText = acc.id;			// 첫 번째 아이템
	SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);
	//패스워드
	LI.iSubItem = 4;//열
	LI.pszText = acc.password;			// 첫 번째 아이템
	SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);



	//LI.iItem = _idx;// 행

	//LI.iSubItem = 0;//열
	//LI.pszText = acc.name;			// 첫 번째 아이템
	//SendMessage(g_hListView, LVM_INSERTITEM, 0, (LPARAM)&LI);

	//TCHAR buf[50];
	//wsprintf(buf, TEXT("%d"), acc.accountNum);

	//LI.iSubItem = 1;
	//LI.pszText = buf;
	//SendMessage(g_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

	//===========================================================
}

void AccountDetailListPrint(AccountDetail accDetail, int _idx)
{
	LVITEM LI;

	LI.mask = LVIF_TEXT;


	//일자
	LI.iItem = _idx;// 행

	LI.iSubItem = 0;//열
	//TCHAR buf[50];
	//wsprintf(buf, TEXT("%d"), accDetail.day);
	LI.pszText = accDetail.day;			// 첫 번째 아이템
	SendMessage(g_hListView2, LVM_INSERTITEM, 0, (LPARAM)&LI);
	//시간
	LI.iSubItem = 1;//열
	LI.pszText = accDetail.time;			// 첫 번째 아이템
	SendMessage(g_hListView2, LVM_SETITEM, 1, (LPARAM)&LI);
	//입금액
	LI.iSubItem = 2;//열
	TCHAR buf[50];
	wsprintf(buf, TEXT("%d"), accDetail.deposit);
	LI.pszText = buf;			// 첫 번째 아이템
	SendMessage(g_hListView2, LVM_SETITEM, 2, (LPARAM)&LI);
	//출금액
	LI.iSubItem = 3;//열
	TCHAR buf2[50];
	wsprintf(buf2, TEXT("%d"), accDetail.withdraw);
	LI.pszText = buf2;			// 첫 번째 아이템
	SendMessage(g_hListView2, LVM_SETITEM, 3, (LPARAM)&LI);
	//잔액
	LI.iSubItem = 4;//열
	LI.pszText = accDetail.balance;			// 첫 번째 아이템
	SendMessage(g_hListView2, LVM_SETITEM, 4, (LPARAM)&LI);
}

void ui_processAccountDetailListPrint(vector<AccountDetail>* datalist, int size)
{
	//List 초기화
	ListView_DeleteAllItems(g_hListView2);
	//하나의 list 아이템 삭제
	//ListView_DeleteItem(hList,idx)
	//정보 추출
	for (int i = 0; i<size; i++)
	{
		AccountDetail info = (*datalist)[i];
		//
		//======================================
		AccountDetailListPrint(info, i);
		//======================================
	}
}



void ui_GetHandle(HWND hDlg)
{
	g_hListView = GetDlgItem(hDlg, IDC_LIST1);
	g_hListView2 = GetDlgItem(hDlg, IDC_LIST2);

	g_hEditAccountNum=GetDlgItem(hDlg, IDC_EDIT1);

	g_hEditName = GetDlgItem(hDlg, IDC_EDIT2);
	
	g_hEditBalance = GetDlgItem(hDlg, IDC_EDIT3);
}

void ui_SetListViewColumnHeader(HWND hDlg)
{
	
	LVCOLUMN COL;
	// 헤더를 추가한다.
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 75;
	COL.pszText = TEXT("계좌번호");				// 첫 번째 헤더
	COL.iSubItem = 0;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.cx = 50;
	COL.pszText = TEXT("이름");			// 두 번째 헤더
	COL.iSubItem = 1;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.cx = 50;
	COL.pszText = TEXT("잔액");			// 3 헤더
	COL.iSubItem = 2;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.cx = 50;
	COL.pszText = TEXT("아이디");			// 4 헤더
	COL.iSubItem = 3;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

	COL.cx = 75;
	COL.pszText = TEXT("패스워드");			// 5 헤더
	COL.iSubItem = 4;
	SendMessage(g_hListView, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);

	//============================================================
	//오른쪽 list control
	LVCOLUMN COL2;
	// 헤더를 추가한다.
	COL2.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL2.fmt = LVCFMT_LEFT;
	COL2.cx = 100;
	COL2.pszText = TEXT("일자");				// 첫 번째 헤더
	COL2.iSubItem = 0;
	SendMessage(g_hListView2, LVM_INSERTCOLUMN, 0, (LPARAM)&COL2);

	COL2.cx = 120;
	COL2.pszText = TEXT("시간");			// 두 번째 헤더
	COL2.iSubItem = 1;
	SendMessage(g_hListView2, LVM_INSERTCOLUMN, 1, (LPARAM)&COL2);

	COL2.cx = 50;
	COL2.pszText = TEXT("입금액");			// 3 헤더
	COL2.iSubItem = 2;
	SendMessage(g_hListView2, LVM_INSERTCOLUMN, 2, (LPARAM)&COL2);

	COL2.cx = 50;
	COL2.pszText = TEXT("출금액");			// 4 헤더
	COL2.iSubItem = 3;
	SendMessage(g_hListView2, LVM_INSERTCOLUMN, 3, (LPARAM)&COL2);

	COL2.cx = 75;
	COL2.pszText = TEXT("잔액");			// 5 헤더
	COL2.iSubItem = 4;
	SendMessage(g_hListView2, LVM_INSERTCOLUMN, 4, (LPARAM)&COL2);
}

void ui_processListPrint(vector<Account>* datalist, int size)
{
	//List 초기화
	ListView_DeleteAllItems(g_hListView);
	//하나의 list 아이템 삭제
	//ListView_DeleteItem(hList,idx)
	//정보 추출
	for (int i = 0; i<size; i++)
	{
		Account info = (*datalist)[i];
		//
		//======================================
		ListPrint(info, i);
		//======================================
	}
}

void setEditControls(int _accountNum,TCHAR * _name,TCHAR * _balance)
{
	TCHAR buf[50];
	wsprintf(buf, TEXT("%d"), _accountNum);
	SetWindowText(g_hEditAccountNum, buf);

	SetWindowText(g_hEditName, _name);

	SetWindowText(g_hEditBalance, _balance);
}
