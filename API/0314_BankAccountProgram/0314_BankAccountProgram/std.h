#pragma once
#include <Windows.h>
#include<tchar.h>
#include<Commctrl.h>
#include<vector>
using namespace std;

//You must have make Resource-Dialog 
#include"resource.h"
//==================================
#include"Account.h"
#include"AccountDetail.h"
//===================================
#include"bank.h"
//===================================
#include"handler.h"
#include"ui.h"

//==================================
#include"createAccountWindowHandler.h"
#include"serchAccountWindowHandler.h"
//======================
//�׽�Ʈ�� �ٵ� �̰� �׽�Ʈ �ȵ��ݾ�.
#define MYTEST MessageBox(hDlg,TEXT(""),TEXT(""),0);