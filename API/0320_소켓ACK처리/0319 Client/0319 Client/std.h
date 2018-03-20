//std.h
#pragma once;
#include<stdio.h>
using namespace std;

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <tchar.h>


#include "resource.h"

#include "packet.h"
#include "wbnet.h"
#include "ui.h"
#include "handler.h"