#pragma once
//control�� �ڵ� ���� ��� �Լ�
void ui_GetHandle(HWND hDlg);

//����Ʈ �信 �÷� �߰�
void ui_SetListViewColumnHeader(HWND hDlg);

//����Ʈ ȭ�鿡 ���
void ui_processListPrint(vector<PROINFO> * datalist, int size);

void ListPrint(PROINFO _info, int _idx);