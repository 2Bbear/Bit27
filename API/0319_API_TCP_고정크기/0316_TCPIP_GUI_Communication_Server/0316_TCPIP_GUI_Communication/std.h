#pragma once

#define WIN32_LEAN_AND_MEAN
// windows.h ���� ���� ������� ���� ���� �����Ͽ���
// ���� �Ѵ�. winsock2.h ���� �浹�� ���� �ش�.

#include <Windows.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<tchar.h>
#include<vector>
using namespace std;
//You must have make Resource-Dialog 
#include"resource.h"	

//
#include"wbnet.h"
#include"ui.h"
#include"handler.h"