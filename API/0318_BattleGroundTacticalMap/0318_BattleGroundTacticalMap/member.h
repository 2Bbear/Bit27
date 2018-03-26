#pragma once
typedef struct tagMEMBER
{
	int ip;
	int port;
	int idx;
	vector<LINEDATA> lineList;
	vector<MARKERDATA> markerList;
	COLORREF color;

}MEMBER;