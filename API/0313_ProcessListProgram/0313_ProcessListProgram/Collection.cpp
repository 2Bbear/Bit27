#include"std.h"

static vector<PROINFO*>g_pList;

void coll_proListSave(vector<PROINFO>* datalist,int size)
{
	g_pList.clear();
	for (int i =0;i<size;i++)
	{
		PROINFO info = (*datalist)[i];
		//
		//======================================
		PROINFO *pInfo = (PROINFO *)malloc(sizeof(PROINFO));
		_tcscpy_s(pInfo->name, info.name);
		pInfo->id = info.id;

		g_pList.push_back(pInfo);
		//======================================
	}
}
