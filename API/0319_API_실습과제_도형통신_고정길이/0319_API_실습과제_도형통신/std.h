#pragma once
//std.h
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include <vector>
using namespace std;
#include "resource.h"
//
#define PORT 9000
//
#include "packet.h"
#include "handle.h"
#include "ui.h"
#include "wbnet.h"