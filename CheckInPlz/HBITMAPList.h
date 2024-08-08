#pragma once
#pragma once
#include "define.h"




typedef struct HBITMAPList
{
	HBITMAP* Content; //����
	int count; //��Ʈ�� ����Ʈ�� ����
	void (*Add)(struct HBITMAPList*, HBITMAP);
	//	void (*Add)(��Ʈ�� ����Ʈ ������, �߰��Ϸ��� �̹��� ���̵�);

	HBITMAP(*Remove)(struct HBITMAPList*, HBITMAP);
	//	char (*Remove)(��Ʈ�� ����Ʈ ������, �߰��Ϸ��� �̹��� ���̵�);

	void (*Clear)(struct HBITMAPList*);
	//	void (*Clear)(������ Ŭ������ ��Ʈ�� ����Ʈ ������);

	int (*isEmpty)(struct HBITMAPList* sPtr);
	//	int (*isEmpty)(������ ��������� Ȯ���� ��Ʈ�� ����Ʈ ������);

	Bool(*Exist)(struct HBITMAPList* list, int obj);
	//	Bool(*Exist)(Ȯ���� ��Ʈ�� ����Ʈ ������, �߰��Ϸ��� �̹��� ���̵�);

}HBITMAPList;

//�ܺ� ���, ������ ��
extern HBITMAPList* CreateHBITMAPList();

//1��1 ����
void AddHBITMAP(HBITMAPList*, HBITMAP);
HBITMAP RemoveHBITMAP(HBITMAPList*, HBITMAP);
Bool HBITMAPisEmpty(HBITMAPList*);
void ClearHBITMAP(HBITMAPList*);
Bool HBITMAPExist(HBITMAPList* list, HBITMAP obj);



