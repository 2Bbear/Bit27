#pragma once
//control�� �ڵ� ���� ��� �Լ�
//void ui_GetHandle(HWND hDlg);

//����Ʈ �信 �÷� �߰�
//void ui_SetListViewColumnHeader(HWND hDlg);

//����Ʈ ȭ�鿡 ���
//void ui_processListPrint(vector<PROINFO> * datalist, int size);

//void ListPrint(PROINFO _info, int _idx);



void ui_GetTeamCreateInfo(HWND hDlg,int *team_id, TCHAR * team_name);
void ui_GetMemberCreateInfo(HWND hDlg, int* member_id, TCHAR * member_name, TCHAR *  member_gender, TCHAR *  member_phone , int * team_id);

//list ���
void ui_TeamListPrint(vector<TEAM>* datalist, int size);
void ui_MemberListPrint(vector<MEMBER>* datalist, int size);
//ComboBox
void ui_InitComboBox(HWND hDlg);
void ui_GetComboBoxText(HWND hDlg,TCHAR * _target);
//Select Edit Box
void ui_GetSelectEditBoxText(HWND hDlg,TCHAR * _id);
//
void ListTeamPrint(TEAM _info, int _idx);
void ListMemberPrint(MEMBER _info, int _idx);

void ui_InitTeamListView(HWND hDlg);
void ui_InitMemberListView(HWND hDlg);