#pragma once


//��� �ʱ�ȭ
void DC_InitMember();
//��� �߰�
void DC_AddMember(int ip, int port,COLORREF  color);
//��� ����
void DC_DeleteMember(int idx);
//��� ���
MEMBER * DC_GetMember(int idx);
//��� ����
void SetMemberColor(int idx,COLORREF color);
void SetMemberIPPort(int idx,int ip, int port);

//���� �߰��ϱ�
void addDrawLine();
//���� �����ϱ�
void deleteDrawLine();
//��Ŀ �߰��ϱ�
void addDrawMarker();
//��Ŀ �����ϱ�
void deleteDrawMarker();
 