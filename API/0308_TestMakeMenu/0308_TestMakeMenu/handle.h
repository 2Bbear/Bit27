#pragma once

//Create Event
LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam);
//================================================================
//Menu Event
	//Select DropDown Menu
LRESULT OnInitMenuPopUp(HWND hwnd, WPARAM wParam, LPARAM lParam);
	//Right click Window Menu
LRESULT OnContextMenu(HWND hwnd, WPARAM wParam, LPARAM lParam);
	//Select Commend Menu Event
LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);

//================================================================
//Mouse
	//left button
LRESULT OnLButtonDwon(HWND hwnd, WPARAM wParam, LPARAM lParam);
	//right button
LRESULT OnRButtonDwon(HWND hwnd, WPARAM wParam, LPARAM lParam);

//================================================================
//Destroy Event
LRESULT OnDestroy();