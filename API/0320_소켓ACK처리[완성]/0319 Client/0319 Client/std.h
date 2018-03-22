//std.h

//#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")
#include <tchar.h>

#include<Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")

#include "resource.h"

#include "packet.h"
#include "wbnet.h"
#include"wbFile.h"

#include "ui.h"
#include "handler.h"
