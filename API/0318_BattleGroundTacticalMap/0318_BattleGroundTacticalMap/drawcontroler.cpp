#include"std.h"

vector<MEMBER> member; // MAX 3
static int currentIdx=0;
//vector<MAP> map;

void DC_InitMember()
{
}

void DC_AddMember(int ip, int port, COLORREF  color)
{
	MEMBER temp;
	temp.ip = ip;
	temp.port = port;
	temp.idx = currentIdx;
	currentIdx++;
	temp.color = color;
	
}

void DC_DeleteMember(int idx)
{
	if (idx>currentIdx)
	{
		return;
	}
	else if (idx<0)
	{
		return;
	}
	else
	{
		vector<MEMBER> ::iterator itor;
		itor = member.begin();

		itor += idx;

		member.erase(itor);
	}
}

MEMBER * DC_GetMember(int idx)
{
	return &member.at(idx);
}

void SetMemberColor(int idx, COLORREF color)
{
	member.at(idx).color = color;
}

void SetMemberIPPort(int idx,int ip, int port)
{
	member.at(idx).ip = ip;
	member.at(idx).port = port;
}


