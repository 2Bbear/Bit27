//std.h

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <tchar.h>
#include <commctrl.h>
#include <vector>
#include "resource.h"
using namespace std;

#include "packet.h"
#include "wbnet.h"
#include "ui.h"
#include "handler.h"
#include "modal.h"
#include "modal_ui.h"
#include "container.h"