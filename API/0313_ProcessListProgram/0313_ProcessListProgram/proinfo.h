#pragma once

typedef struct tagPROINFO
{
	TCHAR name[50];
	int id;
}PROINFO;
//현재 프로세스들의 정보를 얻어오기
void pro_getProcessList(vector<PROINFO> * datalist, int * size);


//프로세스 id값을 주면 프로세스 정보를 리턴한다.
PROINFO PrintProcessNameAndID(DWORD processID);