#pragma once

typedef struct tagPROINFO
{
	TCHAR name[50];
	int id;
}PROINFO;
//���� ���μ������� ������ ������
void pro_getProcessList(vector<PROINFO> * datalist, int * size);


//���μ��� id���� �ָ� ���μ��� ������ �����Ѵ�.
PROINFO PrintProcessNameAndID(DWORD processID);