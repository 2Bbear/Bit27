#include"std.h"
//전역변수
extern vector<Account> g_AccountList;
extern vector<AccountDetail> g_AccountDetailList;
HWND mainhwnd;

int bankStatement;//1이면 출금, 2면 입금
BOOL OnInitDialog(HWND hDlg)
{
	//ui 초기화
	ui_initControl(hDlg);
	//주 메인 핸들 저장
	mainhwnd = hDlg;
	return 0;
}

BOOL OnCreateAccountWindow(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//서브 윈도우의 정보에서 작성한 정보를 저장한 구조체
	Account temp;
	
	//모달 띄우기
	UINT ret = DialogBoxParam(GetModuleHandle(0),// hinstance
		MAKEINTRESOURCE(IDD_DIALOG2),
		hDlg,		// 부모
		SW_CreateAccountProc, // 메세지 함수.
		(LPARAM)&temp); // WM_INITDIALOG의 lParam로 전달된다. //이 함수가 끝날 때까지 메인 윈도우는 아무것도 못한다

	if (ret==IDOK)
	{
		//계좌저장
		createAccount(temp);
		//계좌내역 생성
		createAccountDetail(temp.accountNum, 0, 0,0);
		//총 계좌 출력
		ui_printAllAccount(hDlg, &g_AccountList);
		//생성계좌 수 출력
		ui_printCurrentAccountCount(hDlg);
	}
	else if (ret == IDCANCEL)
	{

	}
	else
	{
		MessageBox(hDlg, TEXT("저장실패"), TEXT(""), MB_OK);
	}
	return 0;
}

BOOL OnSearchAccountWindow(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//이 코드 자체가 새로운 창을 띄우게 함
	UINT ret = DialogBox(GetModuleHandle(0),// instance 
		MAKEINTRESOURCE(IDD_DIALOG3), // 다이얼로그 선택 
		0,   // 부모 윈도우 
		SW_SearchAccountProc);   // Proc..
	return 0;
}

BOOL OnAccountDetailPrint(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//계좌 내역 리스트 출력
	ui_printAccountDetailList((TCHAR * )wParam, &g_AccountDetailList);
	//계좌 정보 출력
	Account temp = g_AccountList[findeIdxAccount((TCHAR *)wParam)];

	ui_printAccountInfo(temp.accountNum,temp.name,temp.balance);
	return 0;
}

BOOL OnDeleteAccountButton(HWND hDlg)
{

	//edit에서 계좌 번호 읽어 오기
	TCHAR buf[50];
	GetDlgItemText(hDlg, IDC_EDIT1, buf, _tcslen(buf));
	//계좌 번호로 해당 계좌 인덱스 찾기
	
	int tempAccountNum= _wtoi(buf);
	Account * temp = findAccount(-1, tempAccountNum);
	//해당 계좌 삭제
	deleteAccount(findeIdxAccount(temp->id));
	//계좌 리스트 재 출력
	ui_printAllAccount(hDlg, &g_AccountList);
	//계좌 정보 edit 초기화
	ui_InitAccountInfoEdit(hDlg);
	//계좌 내역 리스트 초기화
	ui_initAccountDetailListControl(hDlg);
	return 0;
}

BOOL OnBankStatement(HWND hDlg)
{
	//계좌번호 읽어오기
	//계좌 번호 edit에서 계좌 번호 읽어 오기
	TCHAR buf[50];
	GetDlgItemText(hDlg, IDC_EDIT1, buf, _tcslen(buf));
	int tempAccountNum = _wtoi(buf);
	//입금액 edit에서 금액 가져오기
	TCHAR buf2[50];
	GetDlgItemText(hDlg, IDC_EDIT4, buf2, _tcslen(buf2));
	int userMoney = _wtoi(buf2);

	//출금
	if (bankStatement == 1)
	{
		//출금하기
		withdrawAccount(userMoney, tempAccountNum);
	}
	//입금
	else if (bankStatement == 2)
	{
		depositAccount(userMoney, tempAccountNum);
	}
	//그외. 이상한 짓좀 하지마라 좀
	else
	{

	}

	//계좌 list control 초기화
	ui_printAllAccount(hDlg, &g_AccountList);
	//계좌 정보, 계좌 내역 리스트 초기화
	OnAccountDetailPrint(hDlg,(WPARAM)(findAccount(-1, tempAccountNum)->id),0);
	return 0;
}

BOOL OnDeposit()
{
	bankStatement = 2;
	return 0;
}

BOOL OnWithdraw()
{
	bankStatement = 1;
	return 0;
}
