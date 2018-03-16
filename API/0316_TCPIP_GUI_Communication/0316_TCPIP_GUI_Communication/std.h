#pragma once

#define WIN32_LEAN_AND_MEAN
// windows.h 에서 자주 사용하지 않은 것은 컴파일에서
// 제외 한다. winsock2.h 와의 충돌을 막아 준다.

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