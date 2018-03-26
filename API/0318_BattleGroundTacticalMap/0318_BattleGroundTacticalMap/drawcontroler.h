#pragma once


//멤버 초기화
void DC_InitMember();
//멤버 추가
void DC_AddMember(int ip, int port,COLORREF  color);
//멤버 삭제
void DC_DeleteMember(int idx);
//멤버 얻기
MEMBER * DC_GetMember(int idx);
//멤버 수정
void SetMemberColor(int idx,COLORREF color);
void SetMemberIPPort(int idx,int ip, int port);

//라인 추가하기
void addDrawLine();
//라인 삭제하기
void deleteDrawLine();
//마커 추가하기
void addDrawMarker();
//마커 삭제하기
void deleteDrawMarker();
 