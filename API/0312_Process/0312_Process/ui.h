#pragma once

void ui_GetHandle(HWND hDlg);

void ui_GetProcessName(TCHAR * buf);

void ui_SetComboBoxAddProcessName(TCHAR * buf);

int ui_ComboBoxSelChange(HWND hDlg);

void ui_ProInfoPrint(HWND hDlg, PROINFO* p);

HANDLE  ui_GetProcessHandle(HWND hDlg);

void ui_ExitCodePrint(HWND hDlg,int code);

void ui_FindName(HWND hDlg,TCHAR *name);

void ui_ComboBoxPrint(HWND hDlg,TCHAR * name);