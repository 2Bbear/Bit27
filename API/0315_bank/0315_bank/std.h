#pragma once


#include <windows.h>
#include <tchar.h>


#include<vector>
using namespace std;
#include<CommCtrl.h>
#include"resource.h"
//
#define MY_ACCOUNTDETAILPRINT WM_USER+100
//
#include"Account.h"
#include"AccountDetail.h"

//
#include"bank.h"
#include"ui.h"
#include"handle.h"

//
#include"subWindow_CreateAccount.h"
#include"subWindow_SearchAccount.h"

/*
개발 교훈
1. 요구제안서를 받으면 꼭 Data부와 함수부를 미리 검토하자, 제안서 안에서 최대한 data와 기능을 추출해야 뒤가 탈이 없다.
2. 함수의 연산은 함수 내부에서만, 밖에서 까지 연산해서 가져오지 말자. 출력 함수 아직도 못고침...하..미친 어디서 문제가 턷진거야
3. 

*/