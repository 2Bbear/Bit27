#pragma once
//control의 핸들 값을 얻는 함수
void ui_GetHandle(HWND hDlg);

//리스트 뷰에 컬럼 추가
void ui_SetListViewColumnHeader(HWND hDlg);

//리스트 화면에 출력
void ui_processListPrint(vector<PROINFO> * datalist, int size);

void ListPrint(PROINFO _info, int _idx);