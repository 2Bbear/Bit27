#pragma once
BOOL OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);

BOOL OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam);

BOOL OnPrint(HWND hDlg);

//버튼 핸들======================================
void OnUpdateList(HWND hDlg);
void OnSelect(HWND hDlg);
void OnCancel(HWND hDlg);
void OnDelete(HWND hDlg);
void OnStartQuest(HWND hDlg);
void OnSendAnswer(HWND hDlg);
void OnAllScorePrint(HWND hDlg);
void OnSearchMemberQuests(HWND hDlg);
//=========================
void GetProcessList(HWND hDlg);

void OnDBConnect(HWND hdlg);
void OnDBDConnect(HWND hdlg);
//DDL====================================================
void OnCreateTeamTable(HWND hdlg);
void OnDropTeamTable(HWND hdlg);

void OnCreateMemberTable(HWND hdlg);
void OnDropMemberTable(HWND hdlg);

void OnCreateSequence(HWND hdlg);

void OnDropSequence(HWND hdlg);
//======================================================

void OnInsertTeam(HWND hdlg);
void OnInsertMember(HWND hDlg);















