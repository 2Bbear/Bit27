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
���� ����
1. �䱸���ȼ��� ������ �� Data�ο� �Լ��θ� �̸� ��������, ���ȼ� �ȿ��� �ִ��� data�� ����� �����ؾ� �ڰ� Ż�� ����.
2. �Լ��� ������ �Լ� ���ο�����, �ۿ��� ���� �����ؼ� �������� ����. ��� �Լ� ������ ����ħ...��..��ģ ��� ������ �u���ž�
3. 

*/