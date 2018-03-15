#include"std.h"
#include<Commctrl.h>
extern HWND mainhwnd;

//전역 Control Handle 선언
HWND g_hAccountListControl;
HWND g_hAccountDetailListControl;
HWND g_hAccountNameEditControl;
HWND g_hAccountNumEditControl;
HWND g_hAccountBalanceEditControl; 
HWND g_hCurrentAccountCountStaticText;
//=======================================

void ui_initControl(HWND hDlg)
{
	//Control Handle Setting
	g_hAccountListControl = GetDlgItem(hDlg, IDC_LIST1);
	g_hAccountDetailListControl = GetDlgItem(hDlg, IDC_LIST2);
	g_hAccountNameEditControl = GetDlgItem(hDlg, IDC_EDIT2);
	g_hAccountNumEditControl = GetDlgItem(hDlg, IDC_EDIT1);
	g_hAccountBalanceEditControl = GetDlgItem(hDlg, IDC_EDIT3);
	g_hCurrentAccountCountStaticText= GetDlgItem(hDlg, IDC_STATIC_AC_COUNT);
	//List Colum Setting
	initListControlColum();
	//Print AccountCount 
	ui_printCurrentAccountCount(hDlg);

}

void ui_printAllAccount(HWND hDlg, vector<Account>* pAccountList)
{
	//List 초기화
	ListView_DeleteAllItems(g_hAccountListControl);
	//하나의 list 아이템 삭제
	//ListView_DeleteItem(hList,idx)
	//정보 추출
	for (int i = 0; i<(int)pAccountList->size(); i++)
	{
		Account info = (*pAccountList)[i];
		//
		//======================================
		AccountListControlPrint(info, i);
		//======================================
	}
}

void ui_printAccountDetailList(TCHAR * _id, vector<AccountDetail> * pAccountDetailList)
{
	//List 초기화
	ListView_DeleteAllItems(g_hAccountDetailListControl);
	//하나의 list 아이템 삭제
	//ListView_DeleteItem(hList,idx)
	//정보 추출
	int listlicount = 0;
	
	for (int i = 0; i<(int)pAccountDetailList->size(); i++)
	{
		//accountDetail에서 하나씩 요소를 추출하는 부분
		AccountDetail info = (*pAccountDetailList)[i];
		//추출한 요소가 _id와 맞는지 검사
		Account * accinfo = findAccount(-1, info.accountNum);
		//
		//검사
		
		if (_tcscmp(accinfo->id, _id)==0)
		{
			//======================================
			AccountDetailListcontrolPrint(info, listlicount);
			//======================================
			listlicount++;
		}
		
	}

}

void ui_printCurrentAccountCount(HWND hDlg)
{
	TCHAR buf[50];
	wsprintf(buf,TEXT("생성 계좌 수 : %d개"),getCurrentAccountCount());
	SetWindowText(g_hCurrentAccountCountStaticText, buf);
}

void ui_printAccountInfo(int _accountNum, TCHAR * _name, int _balance)
{
	//계좌번호
	TCHAR buf[50];
	wsprintf(buf, TEXT("%d"), _accountNum);
	SetWindowText(g_hAccountNumEditControl, buf);
	//이름
	SetWindowText(g_hAccountNameEditControl, _name);

	//잔액
	TCHAR buf2[50];
	wsprintf(buf2, TEXT("%d"), _balance);
	SetWindowText(g_hAccountBalanceEditControl, buf2);
}

void ui_InitAccountInfoEdit(HWND hwnd)
{
	//계좌 editcontrol
	SetWindowText(g_hAccountNumEditControl, TEXT(""));
	//이름 editcontrol
	SetWindowText(g_hAccountNameEditControl, TEXT(""));
	//잔액 editcontrol
	SetWindowText(g_hAccountBalanceEditControl, TEXT(""));
}

void ui_initAccountDetailListControl(HWND hwnd)
{
	for (int _idx=0;_idx<100;_idx++)
	{
		LVITEM LI;

		LI.mask = LVIF_TEXT;


		//일자
		LI.iItem = _idx;// 행

		LI.iSubItem = 0;//열
						//TCHAR buf[50];
						//wsprintf(buf, TEXT("%d"), accDetail.day);
		LI.pszText = TEXT("");		// 첫 번째 아이템
		SendMessage(g_hAccountDetailListControl, LVM_INSERTITEM, 0, (LPARAM)&LI);
		//시간
		LI.iSubItem = 1;//열
		LI.pszText = TEXT("");			// 첫 번째 아이템
		SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 1, (LPARAM)&LI);
		//입금액
		LI.iSubItem = 2;//열
		LI.pszText = TEXT("");			// 첫 번째 아이템
		SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 2, (LPARAM)&LI);
		//출금액
		LI.iSubItem = 3;//열
		LI.pszText = TEXT("");		// 첫 번째 아이템
		SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 3, (LPARAM)&LI);
		//잔액
		LI.iSubItem = 4;//열
		LI.pszText = TEXT("");	// 첫 번째 아이템
		SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 4, (LPARAM)&LI);
	}
}



void initListControlColum()
{
	LVCOLUMN COL;
	// Account ListControl setting
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 75;
	COL.pszText = TEXT("계좌번호");				// 첫 번째 헤더
	COL.iSubItem = 0;
	SendMessage(g_hAccountListControl, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.cx = 50;
	COL.pszText = TEXT("이름");			// 두 번째 헤더
	COL.iSubItem = 1;
	SendMessage(g_hAccountListControl, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.cx = 50;
	COL.pszText = TEXT("잔액");			// 3 헤더
	COL.iSubItem = 2;
	SendMessage(g_hAccountListControl, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.cx = 50;
	COL.pszText = TEXT("아이디");			// 4 헤더
	COL.iSubItem = 3;
	SendMessage(g_hAccountListControl, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

	COL.cx = 130;
	COL.pszText = TEXT("패스워드");			// 5 헤더
	COL.iSubItem = 4;
	SendMessage(g_hAccountListControl, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);

	//============================================================
	//AccountDetail ListControl Setting
	LVCOLUMN COL2;
	// 헤더를 추가한다.
	COL2.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL2.fmt = LVCFMT_LEFT;
	COL2.cx = 100;
	COL2.pszText = TEXT("일자");				// 첫 번째 헤더
	COL2.iSubItem = 0;
	SendMessage(g_hAccountDetailListControl, LVM_INSERTCOLUMN, 0, (LPARAM)&COL2);

	COL2.cx = 120;
	COL2.pszText = TEXT("시간");			// 두 번째 헤더
	COL2.iSubItem = 1;
	SendMessage(g_hAccountDetailListControl, LVM_INSERTCOLUMN, 1, (LPARAM)&COL2);

	COL2.cx = 50;
	COL2.pszText = TEXT("입금액");			// 3 헤더
	COL2.iSubItem = 2;
	SendMessage(g_hAccountDetailListControl, LVM_INSERTCOLUMN, 2, (LPARAM)&COL2);

	COL2.cx = 50;
	COL2.pszText = TEXT("출금액");			// 4 헤더
	COL2.iSubItem = 3;
	SendMessage(g_hAccountDetailListControl, LVM_INSERTCOLUMN, 3, (LPARAM)&COL2);

	COL2.cx = 95;
	COL2.pszText = TEXT("잔액");			// 5 헤더
	COL2.iSubItem = 4;
	SendMessage(g_hAccountDetailListControl, LVM_INSERTCOLUMN, 4, (LPARAM)&COL2);
}

void AccountListControlPrint(Account acc, int _idx)
{
	LVITEM LI;

	LI.mask = LVIF_TEXT;


	//계좌번호
	LI.iItem = _idx;// 행

	LI.iSubItem = 0;//열
	TCHAR buf[50];
	wsprintf(buf, TEXT("%d"), acc.accountNum);
	LI.pszText = buf;			// 첫 번째 아이템
	SendMessage(g_hAccountListControl, LVM_INSERTITEM, 0, (LPARAM)&LI);
	//이름
	LI.iSubItem = 1;//열
	LI.pszText = acc.name;			// 첫 번째 아이템
	SendMessage(g_hAccountListControl, LVM_SETITEM, 1, (LPARAM)&LI);
	//잔액
	LI.iSubItem = 2;//열
	TCHAR buf2[50];
	wsprintf(buf2, TEXT("%d"), acc.balance);
	LI.pszText = buf2;			// 첫 번째 아이템
	SendMessage(g_hAccountListControl, LVM_SETITEM, 2, (LPARAM)&LI);
	//아이디
	LI.iSubItem = 3;//열
	LI.pszText = acc.id;			// 첫 번째 아이템
	SendMessage(g_hAccountListControl, LVM_SETITEM, 3, (LPARAM)&LI);
	//패스워드
	LI.iSubItem = 4;//열
	LI.pszText = acc.password;			// 첫 번째 아이템
	SendMessage(g_hAccountListControl, LVM_SETITEM, 4, (LPARAM)&LI);
}

void AccountDetailListcontrolPrint(AccountDetail accDetail, int _idx)
{
	LVITEM LI;

	LI.mask = LVIF_TEXT;


	//일자
	LI.iItem = _idx;// 행

	LI.iSubItem = 0;//열
					//TCHAR buf[50];
					//wsprintf(buf, TEXT("%d"), accDetail.day);
	LI.pszText = accDetail.day;			// 첫 번째 아이템
	SendMessage(g_hAccountDetailListControl, LVM_INSERTITEM, 0, (LPARAM)&LI);
	//시간
	LI.iSubItem = 1;//열
	LI.pszText = accDetail.time;			// 첫 번째 아이템
	SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 1, (LPARAM)&LI);
	//입금액
	LI.iSubItem = 2;//열
	TCHAR buf[50];
	wsprintf(buf, TEXT("%d"), accDetail.deposit);
	LI.pszText = buf;			// 첫 번째 아이템
	SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 2, (LPARAM)&LI);
	//출금액
	LI.iSubItem = 3;//열
	TCHAR buf2[50];
	wsprintf(buf2, TEXT("%d"), accDetail.withraw);
	LI.pszText = buf2;			// 첫 번째 아이템
	SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 3, (LPARAM)&LI);
	//잔액
	LI.iSubItem = 4;//열
	TCHAR buf3[50];
	wsprintf(buf3, TEXT("%d"), accDetail.balance);
	LI.pszText = buf3;		// 첫 번째 아이템
	SendMessage(g_hAccountDetailListControl, LVM_SETITEM, 4, (LPARAM)&LI);
}

