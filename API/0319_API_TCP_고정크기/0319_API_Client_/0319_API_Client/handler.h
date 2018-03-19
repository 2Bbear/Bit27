#pragma once
#pragma once

//Init Event
//Create Event
LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam);
//InitDialog Event
LRESULT OnInitDialog(HWND hwnd, WPARAM wParam, LPARAM lParam);
//================================================================
//Destroy Event
LRESULT OnDestroy();

//================================================================
//Paint Event
LRESULT OnPaInt(HWND hwnd, WPARAM wParam, LPARAM lParam);
//================================================================
//Command Event
//Selecting Commend Menu, Notifing Controll message send to Parats, Translate Accellerator Key value Event
LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);

//================================================================
//Menu Event
//Select DropDown Menu
LRESULT OnInitMenuPopUp(HWND hwnd, WPARAM wParam, LPARAM lParam);
//Right click Window Menu
LRESULT OnContextMenu(HWND hwnd, WPARAM wParam, LPARAM lParam);


//================================================================
//Key Event
//Mouse
LRESULT OnLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnLButtonUp(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnRButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnRButtonUp(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam);

//KeyBoard
//virtual Key function
LRESULT OnKeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
//if you push the Alt key so this function will activate
LRESULT OnSystemKeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnSystemKeyUp(HWND hwnd, WPARAM wParam, LPARAM lParam);
//Ascii code key function
LRESULT OnChar(HWND hwnd, WPARAM wParam, LPARAM lParam);

//================================================================
//Timer Event
LRESULT OnTimer(HWND hwnd, WPARAM wParam, LPARAM lParam);
//Timer CallBack Function Form
void CALLBACK MyTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

//================================================================
//InerHandleFunction

void OnConnect(HWND hDlg);
void OnSend(HWND hDlg);
void OnLogMessage(TCHAR * msg);
void OnMessage(char * _buf, int _nRead);

void OnAddMember(HWND hDlg);
void OnLogin(HWND hDlg);
void OnShortMessage(HWND hDlg);