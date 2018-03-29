#pragma once

//
void OnInsertExam(HWND hDlg);
void OnInsertExam2(HWND hDlg);
//
void OnInitExam(HWND hDlg);

void randomexam(int *_buf, int _examcount, int* _exampoolidx, int _poolcount);

//=============================================
BOOL CALLBACK examDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);